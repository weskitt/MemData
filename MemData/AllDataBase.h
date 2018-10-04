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
		bool averageRate = false;
		bool aeraAmp = false;
		float startAmp;
		bool InitlastU = true;
		float RootRate;
		float baseN;
		int counter=0;

		float Arate0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
		void fusion(BaseVoiceSamp& bvs, float &lastU)
		{
			if (aeraAmp) {
				bvs.value = startAmp;
				if (!InitlastU) {
					lastU = bvs.value;
					InitlastU = true;
				}
			}
			if (!averageRate) //�����ٱ仯
			{
				counter += Arate0;
				RootRate = baseN * counter * ort;

				bvs.value = lastU + RootRate;
				lastU = bvs.value;
			}


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

