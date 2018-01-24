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

	//��ԭ�������ݵ�vSamples
	fin.read(samples, srcSize);
	memcpy(samnums, samples, srcSize);
	for (size_t i = 0; i < srcSize/2; i++)
		vSamples.push_back(samnums[i]);

	delete(samples);
	delete(samnums);
	return vSamples.size();
}

void READWAVE::split(vector<AWAVE>& splitWave)
{
	AWAVE Awave;
	ALL_KEY_CHUNKS keyChunks;
	//short samUp(0), samDown(0);
	short		diff; //���ڲ��������ƫ����ڼ�������쳣�ؼ�������
	bool		start(true);//Ĭ���𲽿���
	bool		WaveStateRise(false), WaveStateDown(false);//�ؼ����������½�����
	//bool		IsValidRise, IsValidDown;
	short		samA, samB;	
	const short WAVE_COUNT(3);  //ʶ���γɲ������������
	short		WaveRiseCount(0), WaveDownCount(0);//�����½�����������
	short		waveCount(0);          //����������
	int			offset = 0;
	vector< pair<short, int> > PeakSamples;   //���弯�ϣ���1������Ϊ��Ե�һ��������λ��ƫ��
	vector< pair<short, int> > TroughSamples; //���ȼ��ϣ���1������Ϊ��Ե�һ��������λ��ƫ��

	short		StartSampleGate(400);  //�𲽲�������,��ʱ���˵��ڸ�ֵ���µĲ���
	const short PositiveApproximateZERO(2);  //����������
	const short NegativeApproximateZERO(-2); //����������

	for (auto iter = vSamples.begin(); iter != vSamples.end(); ++iter)
	{
		if (start) {
			if (*iter > StartSampleGate) {
				while ( (*iter)>PositiveApproximateZERO && (*iter)<NegativeApproximateZERO ){ //����ӽ��������samA
					++iter;
				}
				samA = *iter;      //��ӽ��������samA
				samB = *(++iter);  //��ӽ��������samA����һ������samB
				if (samB < samA) WaveStateRise = true;//Ԥ�Ⲩ��
				else			 WaveStateDown = true;//Ԥ�Ⲩ��
				++offset;
				start = false;	   //��������
				
				//iter��ֵ����samB;
			}
		}
		//�����������������濪ʼѰ�ҹؼ�����
		else
		{
			while (iter != vSamples.end())
			{
				while (WaveStateRise) {	
					if (samB < samA) {  //Ѱ����
						samB = samA;
						samA = *(++iter);
						++offset;
					}
					else {	//̽������samB,��ʱsamB > samA
						if (WAVE_COUNT < WaveRiseCount) //����������������
							PeakSamples.push_back(make_pair(samB, offset));//��¼����
						//��ʼ̽������
						WaveStateRise = false;
						WaveStateDown = true;
						WaveDownCount = 1;
					}

				}
				while (WaveStateDown) {
					if (samB > samA) {  //Ѱ����
						samB = samA;
						samA = *(++iter);
						++offset;
					}
					else {	//̽������samB,��ʱsamB < samA
						if (WAVE_COUNT < WaveDownCount) //�½�������������
							TroughSamples.push_back(make_pair(samB, offset));//��¼����
						//��ʼ̽������
						WaveStateRise = true;
						WaveStateDown = false;
						WaveRiseCount = 1;
					}

				}
			}
		}
	}
	//---------------------------------------------------------------------------------------
	//Scheme A �𲨷���
	short CheckLine = SHRT_MAX;

	while (CheckLine)
	{


		--CheckLine;
	}

}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
