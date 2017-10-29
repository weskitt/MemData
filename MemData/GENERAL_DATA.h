#pragma once

typedef void * DATA_ADDR;
typedef const int DATA_TYPE;

int type1 = 0;
int type2 = 1;
int type3 = 2;
int type4 = 3;
//...

int A_RNAK = 0;  //���ɱ������Ƴ���
int B_RANK = 1;  //�ɱ������Ƴ���1������
int C_RANK = 2;  //�ɱ������Ƴ���2������
int D_RANK = 3;  //�ɱ������Ƴ���3����������
int Z_RANK = 4;  //��ʱ�ģ�һ˲��
//...

class GENERAL_DATA
{

	void *    addr; //ָ������
	int       type; //��������
	int       rank; //�ȼ� A_RANK B_RANK ...
	int       value;//�õȼ���ֵ

public:
	void self_Update();

	GENERAL_DATA();
	~GENERAL_DATA();
};

