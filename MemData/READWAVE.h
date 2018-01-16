#pragma once

struct WAVE_HEAD
{
	//char				ChunkID[4];         // "RIFF"标志  
	//unsigned int		ChunkSize;			// 文件长度(WAVE文件的大小, 不含前8个字节)  
	//char				Format[4];          // "WAVE"标志  
	//char				SubChunk1ID[4];     // "fmt "标志  
	//unsigned int		SubChunk1Size;		// 过渡字节(不定)  
	//unsigned short int	AudioFormat;		// 格式类别(10H为PCM格式的声音数据)  
	//unsigned short int	NumChannels;		// 通道数(单声道为1, 双声道为2)  
	//unsigned short int	SampleRate;			// 采样率(每秒样本数), 表示每个通道的播放速度  
	//unsigned int		ByteRate;			// 波形音频数据传输速率, 其值为:通道数*每秒数据位数*每样本的数据位数/8  
	//unsigned short int	BlockAlign;			// 每样本的数据位数(按字节算), 其值为:通道数*每样本的数据位值/8  
	//unsigned short int	BitsPerSample;		// 每样本的数据位数, 表示每个声道中各个样本的数据位数.  
	//char				SubChunk2ID[4];     // 数据标记"data"  
	//unsigned int		SubChunk2Size;		// 语音数据的长度  


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

