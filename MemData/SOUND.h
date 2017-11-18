#pragma once

class SOUND
{
	int power;  //呼吸总气量

	int p1;     //呼吸实时气量
	int sf;     //发声频率

	int fb0;     //韧性0
	int fb1;     //韧性1 
	//两个震动带

	int bt;     //呼吸周期bt

	//主动参数
	int pt;  //持续时长
	//int flowR;  //流量
	int pr;     //压力

	pair<int, int> prpt;
	vector< pair<int, int> > prpts;
	//-----------------------------------------------------
	//-----------------------------------------------------
	int getP1()   //呼吸实时气量更新
	{
		p1 = power*sin(bt); //计算实时气长
		return p1;
	};
	int getSF()  //获取实时的发声频率
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

