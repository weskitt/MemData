#pragma once
class SENSE //��֪,�ɴ��������  actor
{
	SENSOR sensors[senLocal][senType][senCount];  // 
public:
	bool grab(); //�������ݲ�д��Ƭ��frag memory
	SENSE();
	~SENSE();
};

