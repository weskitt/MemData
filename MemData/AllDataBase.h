#pragma once
class AllDataBase
{
private: //��������
	struct PhonationInfo
	{
		int begin;
		int endl;
		int rate; //������仯��
		int rate0; //���ӱ仯�ʣ������޸���rate
	};
	struct VoiceData
	{
		string Pinyin;
		int tone;  //����
		vector<PhonationInfo> info;
		vector<int> data;
	};
public:
	AllDataBase();
	~AllDataBase();
};

