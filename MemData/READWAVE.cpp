#include "stdafx.h"
#include "READWAVE.h"


int READWAVE::GetData(char * url)
{
	//���ⲿ�����ļ���ַ
	//��wav�ļ�����ȡwavͷ��Ϣ
	//fin.open(url, ios::binary);
	//fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	//int srcSize = wave_tag.dataSize;//���ݳ���
	//
	//����ת���ռ�
	//char *samples=new char[srcSize];
	//short * samnums = new short[srcSize/2];
	//
	//��ԭ�������ݵ�vSamples
	//fin.read(samples, srcSize);
	//memcpy(samnums, samples, srcSize);
	
	AudioMethod.SampleGetFromFile(url);
	AudioMethod.LoopAnalyseSample(vSamples);
	return vSamples.size();
}



READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
