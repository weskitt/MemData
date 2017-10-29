#pragma once

typedef void * DATA_ADDR;
typedef const int DATA_TYPE;

int type1 = 0;
int type2 = 1;
int type3 = 2;
int type4 = 3;
//...

int A_RNAK = 0;  //不可被覆盖移除的
int B_RANK = 1;  //可被覆盖移除的1级数据
int C_RANK = 2;  //可被覆盖移除的2级数据
int D_RANK = 3;  //可被覆盖移除的3级数据最弱
int Z_RANK = 4;  //临时的，一瞬间
//...

class GENERAL_DATA
{

	void *    addr; //指针类型
	int       type; //整型类型
	int       rank; //等级 A_RANK B_RANK ...
	int       value;//该等级的值

public:
	void self_Update();

	GENERAL_DATA();
	~GENERAL_DATA();
};

