#pragma once
class SENSOR
{
private:
	int local;  //��������ַ
	int type;   //����������
	int sensation; //ʵʱ��Ӧ��

	int sensesSpeed;   //�о���������
	int suitableSenses; //��ʱ��Ӧ�Ĺ��Ը�Ӧ��
	int originalSuitableSenses;  //Ԥ��Ŀɺ��Եĸ�Ӧ��
	int diffSenses; //ʵʱ�����Ը�Ӧ������ senses - suitableSenses
public:
	//virtual bool ReFreshSensor(); //ˢ�´�������Ӧ��
	SENSOR();
	virtual ~SENSOR();
};

