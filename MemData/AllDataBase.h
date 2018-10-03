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
		float ort;
		bool effected=false;
		//static float RootRate; //������仯��
		bool averageRate=true;
		float RootRate;

		float Arate0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
		float fusion(BaseVoiceSamp &samp){
			//if (!effected) {
			//	RootRate = Arate0*samp.index;
			//	effected = true;
			//}
			if (!averageRate) //�����������仯
				RootRate = Arate0 * samp.index;

			return RootRate *= ort;
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

