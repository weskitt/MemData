#pragma once
class AllDataBase
{
public: //��������

	struct BaseVoiceSamp
	{
		int index;
		float value;
		int invertPoint; //��ת�� ��Y��ֵ
	};
	struct PhonationInfo
	{
		int areaID;
		float begin; //�����������
		float end;   //���������յ�
		int countEnd;

		float ort;
		bool effected=false;
		//static float RootRate; //������仯��
		bool averageRate=false;
		float RootRate;
		

		float baseN;
		int counter=0;

		float Arate0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
		float fusion()
		{
			
			if (!averageRate) //�����������仯
			{
				counter += Arate0;
				RootRate = baseN * counter * ort;
			}

			return RootRate;
			/*if (effected)
				return RootRate;
			else
			{
				effected = true;
				return RootRate *= ort;
			}*/
		}
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

