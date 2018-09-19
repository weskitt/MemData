#pragma once
#include "Mygl.h"
class WaveViewer :
	public Mygl, READWAVE
{
public:
	int PCMSamCount;
	int COMSamCount;
public:
	bool Init(char * file);
	void Run();
	WaveViewer();
	~WaveViewer();

public:
	void display();
	void PCMdisplay();
	void COMdisplay();
};

