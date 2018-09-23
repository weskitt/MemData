#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();
	//X轴框架
	/************************************************************************/
	Frame[0].Position[0] = -1.5f;
	Frame[0].Position[1] =  0.0f;
	Frame[1].Position[0] =  1.5f;
	Frame[1].Position[1] =  0.0f;
	NumVertices_Frame = 2;
	/************************************************************************/
	GetPCMData(file);
	PCMSamCount = vSamples.size();
	PCMvertices = new Vertex[PCMSamCount];
	for (size_t i = 0; i < PCMSamCount; i++)
	{
		PCMvertices[i].Position[0] = -1.0f + (i / (GLfloat)(PCMSamCount - 1))*2.0f;
		PCMvertices[i].Position[1] = (GLfloat)vSamples[i] / SHRT_MAX;  //SHRT_MAX 32767
	}
	/*-----------------------------------------------------------------------*/
	GerneralWave();
	MapToVertex();
	/***********************************************************************/
	GLUpload(PCMSamCount, COMSamCount);	

	FrameShader = Shader("shaders/triangles/Frame.vert", "shaders/triangles/Frame.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return true;
}

void WaveViewer::Run()
{
	checkError();
	while (!glfwWindowShouldClose(window))
	{
		/* 在这里做渲染 */
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* 交换缓冲区，即在window上更新内容 */
		glfwSwapBuffers(window);

		/* 轮询事件 */
		//glfwPollEvents();
		glfwWaitEvents();
	}
}

WaveViewer::WaveViewer()
{
}


WaveViewer::~WaveViewer()
{
}

void WaveViewer::GerneralWave()
{
	//创建基本数据
	GLfloat preAmp = 0.05;
	int relativeStep = 5;
	int T_step = 13;
	int PackStep = relativeStep + T_step;
	COMSamCount = 1920 / PackStep;
	COMvertices = new Vertex[COMSamCount];
	int curX = 0;
	for (size_t i = 0; i < COMSamCount; i++)
	{
		curX = i * PackStep;
		COMSamplesMap[curX] = preAmp;
		//创建基本数据
		++i;
		curX += relativeStep;
		COMSamplesMap[curX] = -preAmp;
	}
	/******************************************************************/
	//塑形计算
	PhonationInfo tInfo;
	Voice tVoice;
	tInfo.areaID = 1;
	tInfo.begin = -1.0;
	tInfo.end = 0.0;
	tInfo.RootRate = 0.05; //膨胀
	tVoice.info.insert(make_pair(tInfo.areaID, tInfo));

	tInfo.areaID = 2;
	tInfo.begin = 0.0; 
	tInfo.end = 1.0;
	tInfo.RootRate = -0.05;//收缩 连续变化
	tVoice.info.insert(make_pair(tInfo.areaID, tInfo));
	GLfloat lastValue = preAmp;
	float t_rate = 0.05;
	for(auto &var : COMSamplesMap)
	{
		
		if ( general_x(var.first) < 0 )
		{
			//var.second = lastValue;
			var.second = var.second + t_rate;
			t_rate += 0.01;
			//lastValue = var.second;
		}
		else
		{
			//var.second = lastValue;
			var.second = var.second*(1 - t_rate);
			t_rate += 0.05;
			//lastValue = var.second;
		}
		
	}

	/******************************************************************/
	//数据补完

}

void WaveViewer::MapToVertex()
{
	int count = COMSamplesMap.size();
	COMvertices = new Vertex[count];

	int index = -1;
	for each (auto var in COMSamplesMap)
	{
		index += 1;
		COMvertices[index].Position[0] = general_x(var.first);
		COMvertices[index].Position[1] = var.second;
		
	}
}

void WaveViewer::display()
{
	frameDisplay();
	//***************************************************************
	if(Wflag)
		PCMdisplay();
	else
		COMdisplay();

	//Error = checkError();
}

void WaveViewer::PCMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glDrawArrays(GL_LINE_STRIP, 0, PCMSamCount);
}

void WaveViewer::COMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_COMSamData]);
	glDrawArrays(GL_LINE_STRIP, 0, COMSamCount);
}
