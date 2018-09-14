#pragma once
class SENSOR
{
private:
	int local;  //传感器地址
	int type;   //传感器类型
	int sensation; //实时感应量

	int sensesSpeed;   //感觉传输速率
	int suitableSenses; //暂时适应的惯性感应量
	int originalSuitableSenses;  //预设的可忽略的感应量
	int diffSenses; //实时差异性感应量计算 senses - suitableSenses
public:
	//virtual bool ReFreshSensor(); //刷新传感器感应量
	SENSOR();
	virtual ~SENSOR();
};

