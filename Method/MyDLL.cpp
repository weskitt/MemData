#include<stdexcept>
#include "MyDLL.h"
// nnntest �������
int AUDIO_METHOD::SampleGetFromFile(char * url)
{
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//���ݳ���
	FormatSampleSize = srcSize / 2;

									//����ת���ռ�

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
			vSampleInPos.push_back(rSample); //�������������
		}
		else if (rSample.data < 0)
		{
			vSampleInNeg.push_back(rSample); //�������������
		}
		//vSample.push_back( BeginSample[AddrOffset] ); //�������Ϊ�������
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
		//start ����������ʼ����
		OnOnePart = true;//������ʼ
		OnWavePart = true;
		samChunkF0.AddrBegin = rSample.addr;
		samChunkF1.AddrBegin = rSample.addr;
	}
	else if ( rSample.offset == OFFSET_DIFF_1 )  //��ʱ������������һ������
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
	else if (rSample.offset <= OFFSET_DIFF_4 )  //ͬ�����������ֲ��ܶȣ�
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



		if (OnOnePart) { //c�����·���
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
	//if (samB < samA) WaveStateRise = true;//Ԥ�Ⲩ��
	//else			 WaveStateDown = true;//Ԥ�Ⲩ��
	//return BeginSample;
}


VshortIter AUDIO_METHOD::SampleFindKey(VshortIter &iter, VshortIter SampleEnd, Vpair &PeakSamples, Vpair &TroughSamples)
{
	while (WaveStateRise && iter!=SampleEnd) {
		if (samB <= samA) {  //Ѱ����
			++WaveRiseCount;
			samB = samA;
			samA = *iter;
			++iter;
			++offset;
		}
		else {	//̽������samB,��ʱsamB > samA
			if (WAVE_COUNT < WaveRiseCount) //����������������
				PeakSamples.push_back(make_pair(samB, offset));//��¼����
															   //��ʼ̽������
			WaveStateRise = false;
			WaveStateDown = true;
			WaveDownCount = 0;
		}

	}
	while (WaveStateDown && iter != SampleEnd) {
		if (samB >= samA) {  //Ѱ����
			++WaveDownCount;
			samB = samA;
			samA = *iter;
			++iter;
			++offset;
		}
		else {	//̽������samB,��ʱsamB < samA
			if (WAVE_COUNT < WaveDownCount) //�½�������������
				TroughSamples.push_back(make_pair(samB, offset));//��¼����
																 //��ʼ̽������
			WaveStateRise = true;
			WaveStateDown = false;
			WaveRiseCount = 0;
		}

	}

	return iter;
}

