#pragma once
#include<vector>
#include<fstream>
using namespace std;

enum SampleAttribute
{
	OFFSET_DIFF_0,
	OFFSET_DIFF_1,  //
	OFFSET_DIFF_2,
	OFFSET_DIFF_3,
	OFFSET_DIFF_4,
	OFFSET_DIFF_5,
	OFFSET_DIFF_6
};
enum SamplePartition
{
	F0_Positive,
	F0_Negative,
	F1_Head
};

const int RELATIVE_OFFSET = 0;

typedef vector<int> Vint;
typedef vector<int>::iterator VintIter;

typedef vector<short> Vshort;
typedef vector<short>::iterator VshortIter;

typedef vector< pair<short, int> > Vpair;
typedef vector< pair<short, int> >::iterator VpairIter;

struct RichSample
{
	short data;
	int	  addr;
	int	  offset;

	int attr[1];

	void Set(int addr, short data) {
		this->data = data;
		this->addr = addr;
	}
	void CountOffset(int preAddr) {
		this->offset = this->addr - preAddr;
	}
};
typedef vector<RichSample> VrichSample;
typedef vector<RichSample>::iterator VrichSampleIter;

struct SampleChunk
{
	int part;
	int Limit=0;//振幅
	int AddrBegin;
	int AddrEnd;
	int count=0;

	void init() {
		part = 0;
		Limit = 0;
		AddrBegin = 0;
		AddrEnd = 0;
		count = 0;
	}
};
typedef vector<SampleChunk> VsampleChunk;
typedef vector<SampleChunk>::iterator VsampleChunkIter;

class PART
{
public:
	static const int MinChunkCount = 5;
	int diffOffset = 0;
	bool  OnOnePart = true;
	bool  OnWavePart = true;
	short	    maxSample = 0;
	short	    minSample = 0;
	RichSample  rSample;
	SampleChunk samChunkF0;
	SampleChunk samChunkF1;
	enum  SamplePartition partType;
public:
	void setRsample(int addr, int data) {
		rSample.addr = addr;
		rSample.data = data;
	}
	void countSamMax() {
		if (rSample.data > maxSample)
			maxSample = rSample.data;
	}
	void countSamMin() {
		if (rSample.data < minSample)
			maxSample = rSample.data;
	}
	void countRelativeOffset(int addr2) {
		rSample.attr[RELATIVE_OFFSET] = rSample.addr - addr2;
	}
	void SamplePart(VsampleChunk &vSampleChunk, RichSample &rSample);
	PART();
	~PART();


};

PART::PART()
{
}
PART::~PART()
{
}


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
typedef vector<AWAVE> Vawave;
typedef vector<AWAVE>::iterator VawaveIter;

class AUDIO_METHOD
{

	WAVE_HEAD	wave_tag;
	ifstream	fin;
public:
	bool		start = true;//默认起步开关
	short		StartSampleGate = 400;  //起步采样阀门,起步时过滤低于该值以下的采样

private:
	short	  * FormatSamples;
	int			FormatSampleSize = 0;
	short	  * BeginSample;
	bool		WaveStateRise = false, WaveStateDown = false;//关键波形上升下降开关
														   //bool		IsValidRise, IsValidDown;
	short		samA, samB;
	const short WAVE_COUNT = 3;  //识别形成波的最低样本数
	int			WaveRiseCount = 0, WaveDownCount = 0;//上升下降样本计数器
	short		waveCount = 0;          //样本计数器
	int			AddrOffset = 0;
	int			offset = 0;

	VrichSample vSampleInPos;// 调试用
	VrichSample vSampleInNeg;//调试用
	VsampleChunk vSampleChunkPos;
	VsampleChunk vSampleChunkNeg;
	
public:
	_declspec(dllexport) int SampleGetFromFile(char * url);
	//_declspec(dllexport) 
	_declspec(dllexport) void LoopAnalyseSample(Vshort &vSample, bool ver);
	_declspec(dllexport) VshortIter SampleFindKey(VshortIter &iter, VshortIter SampleEnd, Vpair &PeakSamples, Vpair &TroughSamples);

private:

	void SetBeginSample();
	//void SamplePart(PART &part);
};