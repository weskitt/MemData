#pragma once




struct AWAVE
{
	short *dataTop;
	short *dataLow;
	int period;		//周期
	int freq;		//频率
	int energy;		//振幅能量
	int ways;		//能量方法
	int spread;		//时域分布(F2，F4，C6，B4，B2)
};

struct ALL_KEY_CHUNKS
{
	vector< pair<short, int> > PeakSamples;   //波峰集合，第1个参数为相对第一个采样的位置偏移
	vector< pair<short, int> > TroughSamples; //波谷集合，第1个参数为相对第一个采样的位置偏移
};

class READWAVE
{
	METHOD method;
	//WAVE_HEAD wave_tag;
	//ifstream fin;
	//list<short> vSamples;
	vector<short> vSamples;
public:
	int GetData(char *); //返回采集到vSamples中的样本数量
	void split(vector<AWAVE> &splitWave);

	READWAVE();
	~READWAVE();
};

