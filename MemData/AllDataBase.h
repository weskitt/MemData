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
		map<int, PhonationInfo> info;
		map<int, int> keyData;
		vector<int> data; //������������
	};

	typedef map<int, PhonationInfo>::iterator InfoIter;
	typedef map<int, int>::iterator KeyDataIter;

public:

public:
	map<string, Voice> VoiceData;
	AllDataBase();
	~AllDataBase();
};

