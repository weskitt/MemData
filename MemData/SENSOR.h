#pragma once
class SENSOR
{

	int value1; //传感器实时值
	int value0; //内部平衡值，
	int local; //位置
	int type1; //类型
	int description; //描述//

public:
	SENSOR();
	~SENSOR();
};

