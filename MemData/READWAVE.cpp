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

	//��ԭ�������ݵ�vSample
	fin.read(samples, srcSize);
	memcpy(samnums, samples, srcSize);
	for (size_t i = 0; i < srcSize/2; i++)
		vSample.push_back(samnums[i]);

	delete(samples);
	delete(samnums);
	return vSample.size();
}

void READWAVE::split(vector<AWAVE>& splitWave)
{
	short samF(0),samC(0),samB(0);
	AWAVE Awave;
	for each (short var in vSample)
	{

	}
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
