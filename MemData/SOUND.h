#pragma once

class SOUND
{
	int power;  //总气长

	int p1;     //实时气长
	int sf;     //频率
	int fb;     //韧性

	int bt;     //呼吸周期bt

	//主动参数
	int pt;  //持续时长
	//int flowR;  //流量
	int pr;     //压力



	void dataUpdate()
	{
		p1 = power*sin(bt); //计算实时气长
	}
public:

	void wave0();
	SOUND();
	~SOUND();
};

