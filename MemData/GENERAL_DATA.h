#pragma once

typedef void * DATA_ADDR;
typedef const int DATA_TYPE;

class GENERAL_DATA
{

	void *    addr; //ָ������
	int       type; //��������
	int       rank; //�ȼ� A_RANK B_RANK ...
	int       value;//�õȼ���ֵ

public:
	GENERAL_DATA();
	~GENERAL_DATA();
};

