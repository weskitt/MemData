#pragma once
class AllDataBase
{
public: //关于语音

	struct BaseVoiceSamp
	{
		int index;
		float value;
		int invertPoint; //反转点 ，Y轴值
	};
	struct PhonationInfo
	{
		int areaID;
		float begin; //区域描述起点
		float end;   //区域描述终点
		float ort;
		bool effected=false;
		//static float RootRate; //该区域变化率
		bool averageRate=true;
		float RootRate;

		float Arate0; //附加变化率，用于修改主rate，实现:变加速，变减速
		float fusion(BaseVoiceSamp &samp){
			//if (!effected) {
			//	RootRate = Arate0*samp.index;
			//	effected = true;
			//}
			if (!averageRate) //非匀速增长变化
				RootRate = Arate0 * samp.index;

			return RootRate *= ort;
		}
	};
	struct Voice
	{
		string symbol; //符号，用于存储显示字符
		string pinyin; //符号发音
		int tone;  //声调
		map< int, PhonationInfo, less<void> > info;
		vector<PhonationInfo> vinfo;
		map<int, int, less<void> > keyData;  //间断不连续关键帧数据
		vector<int> data; //发音具体数据
	};

	typedef map<int, PhonationInfo>::iterator InfoIter;
	typedef vector<PhonationInfo>::iterator VInfoIter;
	typedef map<int, int>::iterator KeyDataIter;

public:

public:
	map<string, Voice> VoiceData;
	AllDataBase();
	~AllDataBase();
};

