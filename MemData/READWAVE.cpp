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

	//复原采样数据到vSample
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
