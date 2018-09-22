#pragma once
class AllDataBase
{
private: //关于语音
	struct PhonationInfo
	{
		int begin;
		int endl;
		int rate; //该区域变化率
		int rate0; //附加变化率，用于修改主rate
	};
	struct VoiceData
	{
		string Pinyin;
		int tone;  //声调
		vector<PhonationInfo> info;
		vector<int> data;
	};
public:
	AllDataBase();
	~AllDataBase();
};

