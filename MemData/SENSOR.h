#pragma once
class SENSOR  //������ actor
{

	int value1; //������ʵʱֵ
	int value0; //�ڲ�ƽ��ֵ����׼  Ĭ��0
	int senty; //������,�ֱ���  //������UNIT��senseFrag�о�Ƭ��vector����
	int local; //λ��
	int type; //���� �¶� ��ɫ ���� ����� ��Ƶ�� ��һϵ�б��ֽ��Ļ���  ����  ���⹹���
	int id;  //�����ʹ��������
	void self_Updata();

public:
	
	int feedback(); //����self_Updata()����ʵ����������
	SENSOR();
	~SENSOR();
};

