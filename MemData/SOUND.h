#pragma once

class SOUND
{
	int power;  //����������

	int p1;     //����ʵʱ����
	int sf;     //����Ƶ��

	int fb0;     //����0
	int fb1;     //����1 
	//�����𶯴�

	int bt;     //��������bt

	//��������
	int pt;  //����ʱ��
	//int flowR;  //����
	int pr;     //ѹ��

	pair<int, int> prpt;
	vector< pair<int, int> > prpts;
	//-----------------------------------------------------
	//-----------------------------------------------------
	int getP1()   //����ʵʱ��������
	{
		p1 = power*sin(bt); //����ʵʱ����
		return p1;
	};
	int getSF()  //��ȡʵʱ�ķ���Ƶ��
	{
		return sf;
	}
	int getFB0()
	{
		return fb0;
	}
	int getFB1()
	{
		return fb1;
	}
	int getBT()
	{
		return bt;
	}
	int getPRPT();

	void Analyse(char *soundData, vector< pair<int, int> >& result);
public:

	void wave0();
	SOUND();
	~SOUND();
};

