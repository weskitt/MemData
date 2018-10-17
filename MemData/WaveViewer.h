#pragma once
//#include "Mygl.h"  ´ý²âÊÔ×¢ÊÍ
class WaveViewer :
	public Mygl, READWAVE, AllDataBase
{
public:
	int PCMSamCount;
	int BaseSamCount;
	float lastU;
	float lastD;
	
	//map<int, GLfloat, less<void>> BaseSamplesMap;
	map<int, BaseVoiceSamp, less<void>> BaseSampSingle;
	map<int, BaseVoiceSamp, less<void>> BaseSamps;
	typedef map<int, BaseVoiceSamp, less<void>>::iterator BaseMapIter;

public:
	bool Init(char * file);
	void Run();
	WaveViewer();
	~WaveViewer();

public:
	GLfloat general_x(int curX){ 
		return -1.0f + (curX / (GLfloat)(1920 - 1))*2.0f;  
	}
	void shape(BaseVoiceSamp &samp, VInfoIter info);
	void GerneralWave();
	void MapToVertex();
	void display();
	void PCMdisplay();
	void COMdisplay();
};

