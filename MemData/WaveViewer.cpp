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

	GLfloat preAmp=0.3;
	int relativeStep=12;
	int T_step=38;
	int PackStep = relativeStep + T_step;
	COMSamCount = PackStep / 1920;
	COMvertices = new Vertex[COMSamCount];
	for (size_t curX = 0; curX < 1920; curX++)
	{
		COMvertices[curX].Position[0]=
	}

	/***********************************************************************/
	GLUpload(PCMSamCount, COMSamCount);	

	FrameShader = Shader("shaders/triangles/Frame.vert", "shaders/triangles/Frame.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return true;
}

void WaveViewer::Run()
{
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

void WaveViewer::display()
{
	frameDisplay();
	//***************************************************************
	if(Wflag)
		PCMdisplay();
	else
		COMdisplay();

	Error = checkError();
}

void WaveViewer::PCMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glDrawArrays(GL_LINE_STRIP, 0, PCMSamCount);
}

void WaveViewer::COMdisplay()
{
}
