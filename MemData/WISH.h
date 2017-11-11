#pragma once
class WISH
{
	bool flag;// 期望达成标签

	//位置 类型 数量
	SENSOR Sensors[senLocal][senType][senCount];


public:
	WISH();
	~WISH();
};

