#include<stdexcept>
#include "MyDLL.h"

int METHOD::AudioSampleGetFromFile(char * url, short ** FormatSamples)
{
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//���ݳ���

									//����ת���ռ�
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
	while ((*iter)>PositiveApproximateZERO && (*iter)<NegativeApproximateZERO) { //����ӽ��������samA
		++iter;
	}
	*samA = *iter;      //��ӽ��������samA
	*samB = *(++iter);  //��ӽ��������samA����һ������samB

	return iter;
}
