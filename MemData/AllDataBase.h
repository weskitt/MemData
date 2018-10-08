#pragma once
class AllDataBase
{
public: //��������

	struct BaseVoiceSamp
	{
		int index;
		float value;
		int invertPoint; //��ת�� ��Y��ֵ
		int areaID;
	};
	struct PhonationInfo
	{
		int areaID;
		float begin; //�����������
		float end;   //���������յ�
		int countEnd;
		float beginData = 0.5;

		
		bool Initbegin=false;
		bool preVoice = false;
		float startAmp;
		bool InitlastU = false;
		
		float ort;
		float RootRate;
		float Arate0; //���ӱ仯�ʣ������޸���rate��ʵ��:����٣������
		float Arate1;
		float Arate2;
		float baseN;

		void fusion(BaseVoiceSamp& bvs, float &lastU)
		{
			if (preVoice) 
			{
				if (InitlastU) {
					lastU = startAmp;
					InitlastU = false;
				}
				bvs.value = lastU;
				lastU = bvs.value;
			}
			else
			{
				if (Initbegin){
					lastU = beginData;
					Initbegin = false;
				}
				//counter += 1; //���ٲ���

				Arate0 += Arate1;

				baseN = Arate0 * RootRate* ort;
				bvs.value = lastU + baseN;
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

