#pragma once
class SENSOR  //传感器 actor
{

	int value1; //传感器实时值
	int value0; //内部平衡值，
	int senty; //灵敏度
	int local; //位置
	int type1; //类型 温度 颜色 亮度 波响度 波频率 等一系列被分解后的基本  或者  虚拟构造的
	

public:
	void self_Updata();
	int feedback();
	SENSOR();
	~SENSOR();
};

