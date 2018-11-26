#pragma once
class SENSE //感知,由传感器组成  actor
{
	SENSOR sensors[senLocal][senType][senCount];  // 
public:
	bool grab(); //捕获数据并写入片段frag memory
	SENSE();
	~SENSE();
};

