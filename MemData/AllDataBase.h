#pragma once
class AllDataBase
{
public: //��������

	struct PhonationInfo
	{
		int areaID;
		float begin; //�����������
		float end;   //���������յ�
		float RootRate; //������仯��

		float rate0 = 0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
	};
	struct Voice
	{
		string symbol; //���ţ����ڴ洢��ʾ�ַ�
		string pinyin; //���ŷ���
		int tone;  //����
		map< int, PhonationInfo, less<void> > info;
		vector<PhonationInfo> vinfo;
		map<int, int, less<void> > keyData;  //��ϲ������ؼ�֡����
		vector<int> data; //������������
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

