// MemData.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{

	READWAVE Rwave;
	Mygl mygl;

	Rwave.GetData("cai3.wav");
	//Rwave.split();
	
	mygl.GLInit();
	mygl.DataInit();
	mygl.Run();
    return 0;
}

