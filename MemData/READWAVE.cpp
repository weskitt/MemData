#include "stdafx.h"
#include "READWAVE.h"


int READWAVE::GetData(char * url)
{   //���ⲿ�����ļ���ַ
	//��wav�ļ�����ȡwavͷ��Ϣ
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//���ݳ���

	//����ת���ռ�
	char *samples=new char[srcSize];
	short * samnums = new short[srcSize/2];

	//��ԭ�������ݵ�ListSamples
	fin.read(samples, srcSize);
	memcpy(samnums, samples, srcSize);
	for (size_t i = 0; i < srcSize/2; i++)
		ListSamples.push_back(samnums[i]);

	delete(samples);
	delete(samnums);
	return ListSamples.size();
}

void READWAVE::split(vector<AWAVE>& splitWave)
{
	AWAVE Awave;
	short samUp(0), samDown(0);
	short diff; //���ڲ��������ƫ����ڼ�������쳣������

	for (auto iter = ListSamples.begin(); iter != ListSamples.end(); ++iter)
	{

	}
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
