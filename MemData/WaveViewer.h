#pragma once
//#include "Mygl.h"  ´ý²âÊÔ×¢ÊÍ
class WaveViewer :
	public Mygl, READWAVE, AllDataBase
{
public:
	int PCMSamCount;
	int BaseSamCount;
	GLfloat lastU;
	GLfloat lastD;
	
	map<int, GLfloat, less<void>> BaseSamplesMap;

	typedef map<int, GLfloat, less<void>>::iterator BaseMapIter;

public:
	bool Init(char * file);
	void Run();
	WaveViewer();
	~WaveViewer();

public:
	GLfloat general_x(int curX){ 
		return -1.0f + (curX / (GLfloat)(1920 - 1))*2.0f;  
	}
	void shape(GLfloat &value, float &rootRate, float rate0);
	void GerneralWave();
	void MapToVertex();
	void display();
	void PCMdisplay();
	void COMdisplay();
};

