#pragma once
class SENSOR  //传感器 actor
{

	int value1; //传感器实时值
	int value0; //内部平衡值，基准  默认0
	int senty; //灵敏度,分辨率  //作用于UNIT的senseFrag感觉片段vector长度
	int local; //位置
	int type; //类型 温度 颜色 亮度 波响度 波频率 等一系列被分解后的基本  或者  虚拟构造的
	int id;  //该类型传感器编号
	void self_Updata();

public:
	
	int feedback(); //调用self_Updata()检查核实并传出数据
	SENSOR();
	~SENSOR();
};

