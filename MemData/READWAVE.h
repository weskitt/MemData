#pragma once






struct ALL_KEY_CHUNKS
{

	vector< pair<short, int> > PeakSamples;   //波峰集合，第1个参数为相对第一个采样的位置偏移
	vector< pair<short, int> > TroughSamples; //波谷集合，第1个参数为相对第一个采样的位置偏移
};

class READWAVE
{
	AUDIO_METHOD AudioMethod;
	vAwave splitWave;
	Vshort vSamples;
public:
	int GetData(char *); //返回采集到vSamples中的样本数量
	void split();

	READWAVE();
	~READWAVE();
};

