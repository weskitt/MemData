#include<stdexcept>
#include "MyDLL.h"

int METHOD::AudioSampleGetFromFile(char * url, short ** FormatSamples)
{
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//数据长度

									//分配转换空间
	*FormatSamples = new short[srcSize / 2];
	char *OriginSamples = new char[srcSize];
	
	fin.read(OriginSamples, srcSize);
	memcpy(*FormatSamples, OriginSamples, srcSize);

	fin.close();
	delete(OriginSamples);

	return srcSize / 2;
}

VshortIter METHOD::AudioSampleFindZero(VshortIter iter, short * samA, short * samB)
{
	while ((*iter)>PositiveApproximateZERO && (*iter)<NegativeApproximateZERO) { //找最接近零点样本samA
		++iter;
	}
	*samA = *iter;      //最接近零点样本samA
	*samB = *(++iter);  //最接近零点样本samA的下一个样本samB

	return iter;
}
