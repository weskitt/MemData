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
	bool start(true);//Ĭ���𲽿���
	bool waveState; bool waveRise(true), waveDown(false); //���������½�����
	
	short StartSample(10);  //����С��ʶ������ż�,���˵��ڸ�ֵ���µĲ���
	short samA, samB;
	short sWave(0),StartWave(10);  //ʶ���γɲ������������

	for (auto iter = ListSamples.begin(); iter != ListSamples.end(); ++iter)
	{
		if (start) {
			if (*iter > StartSample) {
				samA = *iter;
				samB = *(++iter);
				start = false; //�������������
				//��������iter��ֵ����samB;
			}
		}
		else
		{
			if()
		}
	}
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
