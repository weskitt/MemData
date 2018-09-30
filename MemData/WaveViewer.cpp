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
	GLUpload(PCMSamCount, BaseSamCount);	

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

void WaveViewer::shape(GLfloat & value, float & rootRate, float rate0)
{
	if (value > 0){
		value = lastU + rootRate;
		lastU = value;
		rootRate += rate0;
	}
	else if (value < 0){
		value = lastD - rootRate;
		lastD = value;
		rootRate += rate0;
	}
}
void WaveViewer::GerneralWave()
{
	//创建base基本数据
	GLfloat preAmp = 0.001;  
	int relativeStep = 5;
	int T_step = 13;
	int PackStep = relativeStep + T_step;
	BaseSamCount = 1920 / PackStep;
	COMvertices = new Vertex[BaseSamCount];
	int curX = 0;
	for (size_t i = 0; i < BaseSamCount; i++)
	{
		curX = i * PackStep;
		BaseSamplesMap[curX] = preAmp;
		//创建基本数据
		++i;
		curX += relativeStep;
		BaseSamplesMap[curX] = -preAmp;
	}
	/******************************************************************/
	//塑形计算   数据修饰
	PhonationInfo tInfo;
	Voice tVoice;
	tInfo.areaID = 1;
	tInfo.begin = -1.0;
	tInfo.end = 0.0;
	tInfo.RootRate = 0.01; //膨胀
	tInfo.rate0 = 0.0004;
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));

	tInfo.areaID = 2;
	tInfo.begin = 0.0; 
	tInfo.end = 1.0;
	tInfo.RootRate = -0.01;//收缩 连续变化
	tInfo.rate0 = -0.0004;
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));	
	lastU = preAmp;
	lastD = -preAmp;
	VInfoIter infoPart = tVoice.vinfo.begin();
	BaseMapIter comIter = BaseSamplesMap.begin();
	while ( infoPart != tVoice.vinfo.end() && comIter!= BaseSamplesMap.end() )
	{
		if ( general_x(comIter->first) >= infoPart->begin && general_x(comIter->first) < infoPart->end) {
			shape(comIter->second, infoPart->RootRate, infoPart->rate0);
			//if (comIter->second > 0)
			//{
			//	comIter->second = lastU + infoPart->RootRate;
			//	lastU = comIter->second;
			//}
			//else if (comIter->second < 0)
			//{
			//	comIter->second = lastD - infoPart->RootRate;
			//	lastD = comIter->second;
			//}
		}
		else{
			++infoPart;
			--comIter;
		}
		++comIter;
	}

	/******************************************************************/
	//数据补完

}

void WaveViewer::MapToVertex()
{
	int count = BaseSamplesMap.size();
	COMvertices = new Vertex[count];

	int index = -1;
	for each (auto var in BaseSamplesMap)
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
	glDrawArrays(GL_LINE_STRIP, 0, BaseSamCount);
}
