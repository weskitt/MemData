#pragma once
class SENSOR
{

	int value1; //������ʵʱֵ
	int value0; //�ڲ�ƽ��ֵ��
	int local; //λ��
	int type1; //���� �¶� ��ɫ ���� ����� ��Ƶ�� ��һϵ�б��ֽ��Ļ���
	int state; //״̬ ������ ������ �ȶ�//

public:
	void self_Updata();
	SENSOR();
	~SENSOR();
};

