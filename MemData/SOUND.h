#pragma once

class SOUND
{
	int power;  //����������

	int p1;     //����ʵʱ����
	int sf;     //Ƶ��
	int fb;     //����

	int bt;     //��������bt

	//��������
	int pt;  //����ʱ��
	//int flowR;  //����
	int pr;     //ѹ��



	void breathUpdate()   //����ʵʱ��������
	{
		p1 = power*sin(bt); //����ʵʱ����
	}
public:

	void wave0();
	SOUND();
	~SOUND();
};

