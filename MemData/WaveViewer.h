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
	GLfloat GeneralCoordinate(int curX){ 
		return -1.0f + (curX / (GLfloat)(1920 - 1))*2.0f;  
	}

	void GerneralWave();
	void display();
	void PCMdisplay();
	void COMdisplay();
};

