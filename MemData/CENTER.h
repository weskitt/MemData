#pragma once
class CENTER
{
	WISH sensorWISH; //传感器期望，
	vector<WISH> wish; //临时的期望
	UNIT memory[fragLocal][fragType][fragCount];
public:
	CENTER();
	~CENTER();
};

