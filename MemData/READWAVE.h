#pragma once




struct AWAVE
{
	short *dataTop;
	short *dataLow;
	int period;		//����
	int freq;		//Ƶ��
	int energy;		//�������
	int ways;		//��������
	int spread;		//ʱ��ֲ�(F2��F4��C6��B4��B2)
};

struct ALL_KEY_CHUNKS
{
	vector< pair<short, int> > PeakSamples;   //���弯�ϣ���1������Ϊ��Ե�һ��������λ��ƫ��
	vector< pair<short, int> > TroughSamples; //���ȼ��ϣ���1������Ϊ��Ե�һ��������λ��ƫ��
};

class READWAVE
{
	METHOD method;
	//WAVE_HEAD wave_tag;
	//ifstream fin;
	//list<short> vSamples;
	vector<short> vSamples;
public:
	int GetData(char *); //���زɼ���vSamples�е���������
	void split(vector<AWAVE> &splitWave);

	READWAVE();
	~READWAVE();
};

