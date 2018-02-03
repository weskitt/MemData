#pragma once
#include<vector>
#include<fstream>
using namespace std;

typedef vector<short> Vshort;
typedef vector<short>::iterator VshortIter;

struct WAVE_HEAD
{
	char	riff_id[4];			//4byte,资源交换文件标志:RIFF 
	int		chunkSize;			//4byte,从下个地址到文件结尾的总字节数(不含前8个字节)  
	char	wave_fmt[8];		//4byte,wav文件标志:WAVE + 4byte,波形文件标志:FMT(最后一位空格符)
	int		formatSize;			//4byte,格式块的大小  
	short	fmttag;				//2byte,格式种类波形编码格式  
	short	channels;			//2byte,波形文件数据中的通道数  
	int		sampleRate;			//4byte,波形文件的采样率  
	int		bytePerSecond;		//4byte,传输速率平均每秒波形音频所需要的记录的字节数  
	short	blockAlign;			//2byte,数据块的对齐一个采样所需要的字节数  
	short	bitPerSample;		//2byte,采样精度声音文件数据的每个采样的位数  
	short	NullChunk;			//2byte,附加信息
	char	dataType[4];		//4byte,"data"  
	short	dataSize;			//2byte,数据块大小  
};

class METHOD
{
	WAVE_HEAD wave_tag;
	ifstream fin;
	static const short PositiveApproximateZERO = 2;  //正向近似零点
	static const short NegativeApproximateZERO = -2; //负向近似零点
public:
	_declspec(dllexport) int AudioSampleGetFromFile(char * url, short **FormatSamples);
	_declspec(dllexport) VshortIter AudioSampleFindZero(VshortIter iter, short *samA, short *samB);
	_declspec(dllexport) VshortIter AudioSampleFindKey(VshortIter iter, short *samA, short *samB, int *offset, bool *WaveStateRise)
};