#pragma once
#include<vector>
#include<fstream>
using namespace std;



typedef vector<short> Vshort;
typedef vector<short>::iterator VshortIter;

typedef vector< pair<short, int> > Vpair;
typedef vector< pair<short, int> > VpairIter;

struct RichSample
{
	short data;
	int	  addr;

	char attr[10];
};





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

typedef vector<AWAVE> vAwave;
typedef vector<AWAVE>::iterator vAwaveIter;

class AUDIO_METHOD
{

	WAVE_HEAD	wave_tag;
	ifstream	fin;
public:
	bool		start = true;//Ĭ���𲽿���
	short		StartSampleGate = 400;  //�𲽲�������,��ʱ���˵��ڸ�ֵ���µĲ���

private:
	short	  *FormatSamples;
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
	const short PosApprZERO = 2;  //����������
	const short NegApprZERO = -2; //����������

	vector<RichSample> vSampleInPos;//
	vector<RichSample> vSampleInNeg;//
	
public:
	_declspec(dllexport) int SampleGetFromFile(char * url);
	//_declspec(dllexport) 
	_declspec(dllexport) void LoopAnalyseSample(Vshort &vSample);
	_declspec(dllexport) VshortIter SampleFindKey(VshortIter &iter, VshortIter SampleEnd, Vpair &PeakSamples, Vpair &TroughSamples);

private:

	short* SetBeginSample();
	//void SampleFindStart();
};