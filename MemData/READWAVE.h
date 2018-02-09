#pragma once






struct ALL_KEY_CHUNKS
{

	vector< pair<short, int> > PeakSamples;   //���弯�ϣ���1������Ϊ��Ե�һ��������λ��ƫ��
	vector< pair<short, int> > TroughSamples; //���ȼ��ϣ���1������Ϊ��Ե�һ��������λ��ƫ��
};

class READWAVE
{
	AUDIO_METHOD AudioMethod;
	vAwave splitWave;
	Vshort vSamples;
public:
	int GetData(char *); //���زɼ���vSamples�е���������
	void split();

	READWAVE();
	~READWAVE();
};

