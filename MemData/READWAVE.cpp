#include "stdafx.h"
#include "READWAVE.h"


int READWAVE::GetPCMData(char * url)
{
	AudioMethod.SampleGetFromFile(url);
	AudioMethod.LoopAnalyseSample(vSamples, 0); //0ȡ��ԭʼ����
	return vSamples.size();
}



READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
