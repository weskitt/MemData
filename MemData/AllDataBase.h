#pragma once
class AllDataBase
{
public: //��������
	struct PhonationInfo
	{
		int begin;
		int endl;
		int rate; //������仯��

		int rate0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
	};
	struct Voice
	{
		string symbol; //���ţ����ڴ洢��ʾ�ַ�
		string pinyin; //���ŷ���
		int tone;  //����
		vector<PhonationInfo> info;
		map<int, int> keyData;
		vector<int> data; //������������
	};
public:

public:
	map<string, Voice> VoiceData;
	AllDataBase();
	~AllDataBase();
};

