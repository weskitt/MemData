#pragma once
class SENSOR
{

	int value1; //传感器实时值
	int value0; //内部平衡值，
	int local; //位置
	int type1; //类型 温度 颜色 亮度 波响度 波频率 等一系列被分解后的基本
	int state; //状态 正趋势 负趋势 稳定//

public:
	void self_Updata();
	SENSOR();
	~SENSOR();
};

