#include "stdafx.h"
#include "READWAVE.h"


int READWAVE::GetData(char * url)
{   //在外部更新文件地址
	//打开wav文件并获取wav头信息
	fin.open(url, ios::binary);
	fin.read((char*)&wave_tag, sizeof(WAVE_HEAD));
	int srcSize = wave_tag.dataSize;//数据长度

	//分配转换空间
	char *samples=new char[srcSize];
	short * samnums = new short[srcSize/2];

	//复原采样数据到vSamples
	fin.read(samples, srcSize);
	memcpy(samnums, samples, srcSize);
	for (size_t i = 0; i < srcSize/2; i++)
		vSamples.push_back(samnums[i]);

	delete(samples);
	delete(samnums);
	return vSamples.size();
}

void READWAVE::split(vector<AWAVE>& splitWave)
{
	AWAVE Awave;
	ALL_KEY_CHUNKS keyChunks;
	//short samUp(0), samDown(0);
	short		diff; //相邻采样点振幅偏差，用于检查修正异常关键采样点
	bool		start(true);//默认起步开关
	int			WaveState(0); 
	int			WAVE_RISE(1), WAVE_DOWN(2); //关键波形上升下降开关
	bool		IsValidRise, IsValidDown;
	short		samA, samB;	
	const short WAVE_COUNT(5);  //识别形成波的最低样本数
	short		WaveRiseCount(0), WaveDownCount(0);//上升下降样本计数器
	short		waveCount(0);          //样本计数器
	int			offset = 0;

	vector< pair<short, int> > PeakSamples;   //波峰集合，第1个参数为相对第一个采样的位置偏移
	vector< pair<short, int> > TroughSamples; //波谷集合，第1个参数为相对第一个采样的位置偏移
	short		StartSampleGate(10);  //起步采样阀门,起步时过滤低于该值以下的采样
	const short PositiveApproximateZERO(2);  //正向近似零点
	const short NegativeApproximateZERO(-2); //负向近似零点

	for (auto iter = vSamples.begin(); iter != vSamples.end(); ++iter)
	{
		if (start) {
			if (*iter > StartSampleGate) {
				while ( (*iter)>PositiveApproximateZERO && (*iter)<NegativeApproximateZERO ){ //找最接近零点样本samA
					++iter;
				}
				samA = *iter;      //最接近零点样本samA
				samB = *(++iter);  //最接近零点样本samA的下一个样本samB
				if (samB < samA) WaveState = WAVE_RISE;//预测波峰
				else			 WaveState = WAVE_DOWN;//预测波谷
				++offset;
				start = false;	   //结束启动
				
				//iter的值等于samB;
			}
		}
		//以上启动结束，下面开始寻找关键样本
		else
		{
			while (iter != vSamples.end())
			{
				while (WaveState == WAVE_RISE) {
					if (samB < samA) {  //寻波峰
						samB = samA;
						samA = *(++iter);
						++offset;
					}
					else {	//探到波峰samB,此时samB > samA
						if (WAVE_COUNT < WaveRiseCount) //上升样本数量充足
							PeakSamples.push_back(make_pair(samB, offset));//记录样本
						//开始探索波谷
						WaveState = WAVE_DOWN;
						WaveRiseCount = 1;
						break;
					}

				}

				while (WaveState == WAVE_DOWN) {
					if (samB > samA) {  //寻波谷
						samB = samA;
						samA = *(++iter);
						++offset;
					}
					else {	//探到波谷samB,此时samB < samA
						if (WAVE_COUNT < WaveDownCount) //下降样本数量充足
							PeakSamples.push_back(make_pair(samB, offset));//记录样本
						//开始探索波峰
						WaveState = WAVE_RISE;
						WaveRiseCount = 1;
						break;
					}

				}
			}
		}
	}
}

READWAVE::READWAVE()
{
}


READWAVE::~READWAVE()
{
}
