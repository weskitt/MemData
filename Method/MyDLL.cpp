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

	PART part;

	int PosPreOffset = 0;
	int NegPreOffset = 0;
	for (; AddrOffset < FormatSampleSize; AddrOffset++) 
	{
		part.setRsample(AddrOffset, BeginSample[AddrOffset]);

		if (part.rSample.data > 0)
		{
			part.countSamMax();
			part.countRelativeOffset(PosPreOffset);
			part.SamplePart(vSampleChunk);

			vSampleInPos.push_back(part.rSample);
			PosPreOffset = AddrOffset;
		}
		else if (part.rSample.data < 0)
		{
			part.countSamMin();
			part.countRelativeOffset(NegPreOffset);
			part.SamplePart(vSampleChunk);

			vSampleInNeg.push_back(part.rSample);
			NegPreOffset = AddrOffset;
		}
		//NegPreOffset = AddrOffset;
		vSample.push_back( BeginSample[AddrOffset] );
	}
		
	delete(FormatSamples);
}

void PART::SamplePart(VsampleChunk &vSampleChunk)
{

	if ( rSample.attr[RELATIVE_OFFSET] == OFFSET_DIFF_0 )
	{
		if (partStart) {
			samChunkF0.AddrBegin = rSample.addr;
			partStart = false;
		}
		else if()
		{
			vSampleChunk.push_back(samChunkF1);
		}
		samChunkF0.AddrEnd = rSample.addr;
		samChunkF0.count += 1;


		//rsam.attr[SAMPLE_PARTITION] = F0_Positive;
	}
	else if (rSample.attr[RELATIVE_OFFSET] <= OFFSET_DIFF_3 )
	{
		if (partStart) {
			samChunkF1.AddrBegin = rSample.addr;
			partStart = false;
		}
		else if ()
		{
			vSampleChunk.push_back(samChunkF0);
		}
		samChunkF1.AddrEnd = rSample.addr;
		samChunkF1.count += 1;


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

