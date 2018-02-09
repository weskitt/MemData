#include<stdexcept>
#include "MyDLL.h"

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

	if (samB < samA) WaveStateRise = true;//Ԥ�Ⲩ��
	else			 WaveStateDown = true;//Ԥ�Ⲩ��

	return BeginSample;

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


