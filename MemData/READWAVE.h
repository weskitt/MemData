#pragma once

struct WAVE_HEAD
{
	//char				ChunkID[4];         // "RIFF"��־  
	//unsigned int		ChunkSize;			// �ļ�����(WAVE�ļ��Ĵ�С, ����ǰ8���ֽ�)  
	//char				Format[4];          // "WAVE"��־  
	//char				SubChunk1ID[4];     // "fmt "��־  
	//unsigned int		SubChunk1Size;		// �����ֽ�(����)  
	//unsigned short int	AudioFormat;		// ��ʽ���(10HΪPCM��ʽ����������)  
	//unsigned short int	NumChannels;		// ͨ����(������Ϊ1, ˫����Ϊ2)  
	//unsigned short int	SampleRate;			// ������(ÿ��������), ��ʾÿ��ͨ���Ĳ����ٶ�  
	//unsigned int		ByteRate;			// ������Ƶ���ݴ�������, ��ֵΪ:ͨ����*ÿ������λ��*ÿ����������λ��/8  
	//unsigned short int	BlockAlign;			// ÿ����������λ��(���ֽ���), ��ֵΪ:ͨ����*ÿ����������λֵ/8  
	//unsigned short int	BitsPerSample;		// ÿ����������λ��, ��ʾÿ�������и�������������λ��.  
	//char				SubChunk2ID[4];     // ���ݱ��"data"  
	//unsigned int		SubChunk2Size;		// �������ݵĳ���  


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



class READWAVE
{
	WAVE_HEAD wave_tag;
	ifstream fin;
	vector<short> vSample;
public:
	void GetData(char *);
	READWAVE();
	~READWAVE();
};

