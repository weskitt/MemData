#pragma once
class SENSE //��֪,�ɴ��������  actor
{
	SENSOR_o sensors[senLocal][senType][senCount];  // every 1/24�������ȡԪ����
public:
	bool grab(); //�������ݲ�д��Ƭ��frag memory
	SENSE();
	~SENSE();
};

