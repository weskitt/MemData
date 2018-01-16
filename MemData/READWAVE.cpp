#include "stdafx.h"
#include "READWAVE.h"


void READWAVE::GetData(char * url)
{   //在外部更新文件地址
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;

	char *samples=new char[srcSize];
	short * samnums = new short[srcSize/2];

	fin.read(samples, srcSize);
	memcpy(samnums, samples, srcSize);
	for (size_t i = 0; i < srcSize/2; i++)
		vSample.push_back(samnums[i]);
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
