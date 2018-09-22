#pragma once
class AllDataBase
{
public: //关于语音
	struct PhonationInfo
	{
		int begin;
		int endl;
		int rate; //该区域变化率

		int rate0; //附加变化率，用于修改主rate，实现:变加速，变减速
	};
	struct Voice
	{
		string symbol; //符号，用于存储显示字符
		string pinyin; //符号发音
		int tone;  //声调
		vector<PhonationInfo> info;
		map<int, int> keyData;
		vector<int> data; //发音具体数据
	};
public:

public:
	map<string, Voice> VoiceData;
	AllDataBase();
	~AllDataBase();
};

