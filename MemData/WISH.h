#pragma once
class WISH
{
	bool flag;// 期望达成标签

	//位置 类型 数量
	SENSOR Sensors[senLocal][senType][senCount];  //1/24秒获取的元数据


public:
	WISH();
	~WISH();
};

