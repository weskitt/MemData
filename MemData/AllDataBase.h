#pragma once
class AllDataBase
{
public: //关于语音

	struct BaseVoiceSamp
	{
		int index;
		float value;
		int invertPoint; //反转点 ，Y轴值
		int areaID;
	};
	struct PhonationInfo
	{
		int areaID;
		float begin; //区域描述起点
		float end;   //区域描述终点
		int countEnd;
		float beginData = 0.5;

		
		bool Initbegin=false;
		bool preVoice = false;
		float startAmp;
		bool InitlastU = false;
		
		float ort;
		float RootRate;
		float Arate0; //附加变化率，用于修改主rate，实现:变加速，变减速
		float Arate1;
		float Arate2;
		float baseN;

		void fusion(BaseVoiceSamp& bvs, float &lastU)
		{
			if (preVoice) 
			{
				if (InitlastU) {
					lastU = startAmp;
					InitlastU = false;
				}
				bvs.value = lastU;
				lastU = bvs.value;
			}
			else
			{
				if (Initbegin){
					lastU = beginData;
					Initbegin = false;
				}
				//counter += 1; //加速参数

				Arate0 += Arate1;

				baseN = Arate0 * RootRate* ort;
				bvs.value = lastU + baseN;
				lastU = bvs.value;
			}
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

