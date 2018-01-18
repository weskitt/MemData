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
	short samUp(0), samDown(0);
	short diff; //相邻采样点振幅偏差，用于检查修正异常采样点
	bool start(true);//默认起步开关
	bool waveState; bool waveRise(true), waveDown(false); //波形上升下降开关
	
	short StartSample(10);  //起步最小可识别采样门槛,过滤低于该值以下的采样
	short samA, samB;
	short sWave(0),StartWave(10);  //识别形成波的最低样本数

	for (auto iter = ListSamples.begin(); iter != ListSamples.end(); ++iter)
	{
		if (start) {
			if (*iter > StartSample) {
				samA = *iter;
				samB = *(++iter);
				start = false; //检测启动迭代器
				//启动结束iter的值等于samB;
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
