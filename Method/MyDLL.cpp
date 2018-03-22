#include<stdexcept>
#include "MyDLL.h"
// nnntest 编码测试
int AUDIO_METHOD::SampleGetFromFile(char * url)
{
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//数据长度
	FormatSampleSize = srcSize / 2;

									//分配转换空间

	FormatSamples = new short[FormatSampleSize];
	char *OriginSamples = new char[srcSize];
	
	fin.read(OriginSamples, srcSize);
	memcpy(FormatSamples, OriginSamples, srcSize);

	fin.close();
	delete(OriginSamples);

	return FormatSampleSize;
}

void AUDIO_METHOD::LoopAnalyseSample(Vshort &vSample)
{
	SetBeginSample();
	RichSample rSample;
	PART part;

	int PosPreOffset = 0;
	int NegPreOffset = 0;

	int PosSampleCount = 0;
	int NegSampleCount = 0;

	for (; AddrOffset < FormatSampleSize; AddrOffset++) 
	{
		//part.setRsample(AddrOffset, BeginSample[AddrOffset]);
		rSample.Set(AddrOffset, BeginSample[AddrOffset]);

		if (rSample.data > 0)//if (PosSampleCount == 0){
			//	PosPreOffset = AddrOffset;
			//	NegSampleCount = 0;}
			//++PosSampleCount;
			//part.countSamMax();
			//part.countRelativeOffset(PosPreOffset);
			//part.SamplePart(vSampleChunkPos);//PosPreOffset = AddrOffset;
		{
			vSampleInPos.push_back(rSample); //样本正区间分组
		}
		else if (rSample.data < 0)
		{
			vSampleInNeg.push_back(rSample); //样本负区间分组
		}
		//vSample.push_back( BeginSample[AddrOffset] ); //跳过振幅为零的样本
	}
	delete(FormatSamples);

	PosPreOffset = vSampleInPos[0].addr;
	NegPreOffset = vSampleInNeg[0].addr;

	for (RichSample &var : vSampleInPos)
	{
		var.CountOffset(PosPreOffset);
		part.SamplePart(vSampleChunkPos, var);
		PosPreOffset = var.addr;
	}
	for (RichSample &var : vSampleInNeg)
	{
		var.CountOffset(NegPreOffset);
		NegPreOffset = var.addr;
	}
}


void PART::SamplePart(VsampleChunk &vSampleChunk, RichSample &rSample)
{
	
	if (rSample.offset == OFFSET_DIFF_0)
	{
		//start 用于跳过起始样本
		OnOnePart = true;//分区开始
		OnWavePart = true;
		samChunkF0.AddrBegin = rSample.addr;
		samChunkF1.AddrBegin = rSample.addr;
	}
	else if ( rSample.offset == OFFSET_DIFF_1 )  //此时相邻样本都在一分区内
	{
		OnOnePart = true;
		OnWavePart = false;

		if(samChunkF1.count > MinChunkCount)
		{
			vSampleChunk.push_back(samChunkF1);
			samChunkF1.init();
			OnOnePart = true;
		}

		samChunkF0.AddrEnd = rSample.addr;
		samChunkF0.count += 1;


	}
	else if (rSample.offset <= OFFSET_DIFF_4 )  //同分区样本最大分布密度，
	{
		
		if (samChunkF0.count > MinChunkCount)
		{
			samChunkF0.part = OFFSET_DIFF_1;
			vSampleChunk.push_back(samChunkF0);
			samChunkF0.init();
			OnOnePart = true;
		}
		else
		{
			samChunkF0.init();
			OnOnePart = true;
		}



		if (OnOnePart) { //c创建新分区
			if (samChunkF0.count > MinChunkCount) {
				samChunkF0.part = OFFSET_DIFF_1;
				vSampleChunk.push_back(samChunkF0);
				samChunkF0.init();
			}
			samChunkF1.AddrBegin = rSample.addr;
			OnOnePart = false;
		}
		else
		{
			samChunkF1.AddrEnd = rSample.addr;
			samChunkF1.count += 1;
		}
		


	}

}


void AUDIO_METHOD::SetBeginSample()
{
	int i=0;
	while (FormatSamples[i] < StartSampleGate)
	{
		++i;
	}
	BeginSample= FormatSamples + i;
	FormatSampleSize = FormatSampleSize - i;

	//samB = BeginSample[AddrOffset];
	//samA = BeginSample[++AddrOffset];
	//if (samB < samA) WaveStateRise = true;//预测波峰
	//else			 WaveStateDown = true;//预测波谷
	//return BeginSample;
}


VshortIter AUDIO_METHOD::SampleFindKey(VshortIter &iter, VshortIter SampleEnd, Vpair &PeakSamples, Vpair &TroughSamples)
{
	while (WaveStateRise && iter!=SampleEnd) {
		if (samB <= samA) {  //寻波峰
			++WaveRiseCount;
			samB = samA;
			samA = *iter;
			++iter;
			++offset;
		}
		else {	//探到波峰samB,此时samB > samA
			if (WAVE_COUNT < WaveRiseCount) //上升样本数量充足
				PeakSamples.push_back(make_pair(samB, offset));//记录样本
															   //开始探索波谷
			WaveStateRise = false;
			WaveStateDown = true;
			WaveDownCount = 0;
		}

	}
	while (WaveStateDown && iter != SampleEnd) {
		if (samB >= samA) {  //寻波谷
			++WaveDownCount;
			samB = samA;
			samA = *iter;
			++iter;
			++offset;
		}
		else {	//探到波谷samB,此时samB < samA
			if (WAVE_COUNT < WaveDownCount) //下降样本数量充足
				TroughSamples.push_back(make_pair(samB, offset));//记录样本
																 //开始探索波峰
			WaveStateRise = true;
			WaveStateDown = false;
			WaveRiseCount = 0;
		}

	}

	return iter;
}

