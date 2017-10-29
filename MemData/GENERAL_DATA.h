#pragma once

typedef void * DATA_ADDR;
typedef const int DATA_TYPE;

class GENERAL_DATA
{

	void *    addr; //指针类型
	int       type; //整型类型
	int       rank; //等级 A_RANK B_RANK ...
	int       value;//该等级的值

public:
	GENERAL_DATA();
	~GENERAL_DATA();
};

