#pragma once
class SENSE //感知,由传感器组成  actor
{
	SENSOR sensors[senLocal][senType][senCount];  // every 1/24秒解析获取元数据
public:
	bool grab(); //捕获数据并写入片段frag memory
	SENSE();
	~SENSE();
};

