#pragma once
class AllDataBase
{
public: //��������

	struct PhonationInfo
	{
		float begin; //�����������
		float end;   //���������յ�
		int RootRate; //������仯��

		int rate0 = 0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
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

