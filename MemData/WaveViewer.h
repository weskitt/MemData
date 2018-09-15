#pragma once
#include "Mygl.h"
class WaveViewer :
	public Mygl, READWAVE
{
public:
	//struct Vertex
	//{
	//	GLfloat Position[2];
	//};
	//Vertex * vertices;
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

