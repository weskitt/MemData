#pragma once
class SENSOR
{

	int value1; //������ʵʱֵ
	int value0; //�ڲ�ƽ��ֵ��
	int senty; //������
	//int local; //λ��
	//int type1; //���� �¶� ��ɫ ���� ����� ��Ƶ�� ��һϵ�б��ֽ��Ļ���  ����  ���⹹���
	int state; //�����仯״̬ ������ ������ �ȶ�//

public:
	void self_Updata();
	SENSOR();
	~SENSOR();
};

