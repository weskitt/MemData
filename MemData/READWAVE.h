#pragma once

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
	short *data;
	int period;		//����
	int freq;		//Ƶ��
	int energy;		//�������
	int ways;		//��������
	int spread;		//ʱ��ֲ�(F2��F4��C6��B4��B2)
};

class READWAVE
{
	WAVE_HEAD wave_tag;
	ifstream fin;
	vector<short> vSample;
public:
	int GetData(char *); //���زɼ���vSample�е���������
	void split(vector<AWAVE> &splitWave);

	READWAVE();
	~READWAVE();
};

