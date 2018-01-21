#include "stdafx.h"
#include "READWAVE.h"


int READWAVE::GetData(char * url)
{   //在外部更新文件地址
	//打开wav文件并获取wav头信息
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//数据长度

	//分配转换空间
	char *samples=new char[srcSize];
	short * samnums = new short[srcSize/2];

	//复原采样数据到ListSamples
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
	ALL_KEY_CHUNKS keyChunks;
	short samUp(0), samDown(0);
	short diff; //相邻采样点振幅偏差，用于检查修正异常关键采样点
	bool start(true);//默认起步开关
	bool waveState; bool waveRise(true), waveDown(false); //关键波形上升下降开关
	
	short StartSampleGate(10);  //起步采样阀门,起步时过滤低于该值以下的采样
	short samA, samB;
	const short PositiveApproximateZERO(2);  //正向近似零点
	const short NegativeApproximateZERO(-2); //负向近似零点
	const short WAVE_COUNT(5);  //识别形成波的最低样本数
	short waveCount(0);          //样本计数器

	for (auto iter = ListSamples.begin(); iter != ListSamples.end(); ++iter)
	{
		if (start) {
			if (*iter > StartSampleGate) {
				while ( (*iter)>PositiveApproximateZERO && (*iter)<NegativeApproximateZERO ){ //找最接近零点样本samA
					++iter;
				}
				samA = *iter;      //最接近零点样本samA
				samB = *(++iter);  //最接近零点样本samA的下一个样本samB
				start = false;	   //结束启动
				//iter的值等于samB;
			}
		}
		//以上启动结束，下面开始寻找关键样本
		else
		{	//寻找波峰或波谷
			keyChunks.startPoint = iter;
			pair<short, int> pt;
			if (samA > samB) {		//预测波谷

			}
			else if(samA < samB){	//预测波峰

			}
			else   //相等，跳过当前样本
			{

			}
			{
					
			}
			{

			}
		}
	}
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
