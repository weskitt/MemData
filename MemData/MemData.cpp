// MemData.cpp: 定义控制台应用程序的入口点。
//记忆块-部件(带舒适传感器)->作用->情绪感情变量(影响全局)

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

