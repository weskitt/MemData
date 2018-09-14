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
	int Limit=0;//���
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

struct AWAVE
{
	short *dataTop;
	short *dataLow;
	int period;		//����
	int freq;		//Ƶ��
	int energy;		//�������
	int ways;		//��������
	int spread;		//ʱ��ֲ�(F2��F4��C6��B4��B2)
};
typedef vector<AWAVE> Vawave;
typedef vector<AWAVE>::iterator VawaveIter;

class AUDIO_METHOD
{

	WAVE_HEAD	wave_tag;
	ifstream	fin;
public:
	bool		start = true;//Ĭ���𲽿���
	short		StartSampleGate = 400;  //�𲽲�������,��ʱ���˵��ڸ�ֵ���µĲ���

private:
	short	  * FormatSamples;
	int			FormatSampleSize = 0;
	short	  * BeginSample;
	bool		WaveStateRise = false, WaveStateDown = false;//�ؼ����������½�����
														   //bool		IsValidRise, IsValidDown;
	short		samA, samB;
	const short WAVE_COUNT = 3;  //ʶ���γɲ������������
	int			WaveRiseCount = 0, WaveDownCount = 0;//�����½�����������
	short		waveCount = 0;          //����������
	int			AddrOffset = 0;
	int			offset = 0;

	VrichSample vSampleInPos;// ������
	VrichSample vSampleInNeg;//������
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