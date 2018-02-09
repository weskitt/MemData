#include<stdexcept>
#include "MyDLL.h"

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
	
	for (; AddrOffset < FormatSampleSize; AddrOffset++) {

		short t = BeginSample[AddrOffset];
		vSample.push_back( BeginSample[AddrOffset] );
	}
		
	delete(FormatSamples);
}


short* AUDIO_METHOD::SetBeginSample()
{
	int i=0;
	while (FormatSamples[i] < StartSampleGate)
	{
		++i;
	}
	BeginSample= FormatSamples + i;
	FormatSampleSize = FormatSampleSize - i;

	samB = BeginSample[AddrOffset];
	samA = BeginSample[++AddrOffset];

	if (samB < samA) WaveStateRise = true;//预测波峰
	else			 WaveStateDown = true;//预测波谷

	return BeginSample;

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


