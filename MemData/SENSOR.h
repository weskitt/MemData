#pragma once
class SENSOR  //������ actor
{

	int value1; //������ʵʱֵ
	int value0; //�ڲ�ƽ��ֵ��
	int senty; //������
	int local; //λ��
	int type1; //���� �¶� ��ɫ ���� ����� ��Ƶ�� ��һϵ�б��ֽ��Ļ���  ����  ���⹹���
	

public:
	void self_Updata();
	int feedback();
	SENSOR();
	~SENSOR();
};

