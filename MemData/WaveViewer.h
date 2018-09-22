#pragma once
//#include "Mygl.h"  ´ý²âÊÔ×¢ÊÍ
class WaveViewer :
	public Mygl, READWAVE, AllDataBase
{
public:
	int PCMSamCount;
	int COMSamCount;

	
	map<int, GLfloat, less<void>> COMSamplesMap;

	typedef map<int, GLfloat, less<void>>::iterator MapIter;

public:
	bool Init(char * file);
	void Run();
	WaveViewer();
	~WaveViewer();

public:
	GLfloat general_x(int curX){ 
		return -1.0f + (curX / (GLfloat)(1920 - 1))*2.0f;  
	}
	void GerneralWave();
	void MapToVertex();
	void display();
	void PCMdisplay();
	void COMdisplay();
};

