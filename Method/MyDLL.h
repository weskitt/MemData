#pragma once
#include<vector>
#include<fstream>
using namespace std;

typedef vector<short> Vshort;
typedef vector<short>::iterator VshortIter;

struct WAVE_HEAD
{
	char	riff_id[4];			//4byte,��Դ�����ļ���־:RIFF 
	int		chunkSize;			//4byte,���¸���ַ���ļ���β�����ֽ���(����ǰ8���ֽ�)  
	char	wave_fmt[8];		//4byte,wav�ļ���־:WAVE + 4byte,�����ļ���־:FMT(���һλ�ո��)
	int		formatSize;			//4byte,��ʽ��Ĵ�С  
	short	fmttag;				//2byte,��ʽ���ನ�α����ʽ  
	short	channels;			//2byte,�����ļ������е�ͨ����  
	int		sampleRate;			//4byte,�����ļ��Ĳ�����  
	int		bytePerSecond;		//4byte,��������ƽ��ÿ�벨����Ƶ����Ҫ�ļ�¼���ֽ���  
	short	blockAlign;			//2byte,���ݿ�Ķ���һ����������Ҫ���ֽ���  
	short	bitPerSample;		//2byte,�������������ļ����ݵ�ÿ��������λ��  
	short	NullChunk;			//2byte,������Ϣ
	char	dataType[4];		//4byte,"data"  
	short	dataSize;			//2byte,���ݿ��С  
};

class METHOD
{
	WAVE_HEAD wave_tag;
	ifstream fin;
	static const short PositiveApproximateZERO = 2;  //����������
	static const short NegativeApproximateZERO = -2; //����������
public:
	_declspec(dllexport) int AudioSampleGetFromFile(char * url, short **FormatSamples);
	_declspec(dllexport) VshortIter AudioSampleFindZero(VshortIter iter, short *samA, short *samB);
	_declspec(dllexport) VshortIter AudioSampleFindKey(VshortIter iter, short *samA, short *samB, int *offset, bool *WaveStateRise)
};