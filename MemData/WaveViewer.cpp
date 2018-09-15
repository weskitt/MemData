#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();

	/************************************************************************/
	Frame[0].Position[0] = -1.5f;
	Frame[0].Position[1] =  0.0f;
	Frame[1].Position[0] =  1.5f;
	Frame[1].Position[1] =  0.0f;
	NumVertices_Frame = 2;
	/************************************************************************/
	GetPCMData(file);

	SamCount = vSamples.size();
	vertices = new Vertex[SamCount];
	for (size_t i = 0; i < SamCount; i++)
	{
		vertices[i].Position[0] = -1.0f + (i / (GLfloat)(SamCount - 1))*2.0f;
		vertices[i].Position[1] = (GLfloat)vSamples[i] / SHRT_MAX;  //SHRT_MAX 32767
	}

	GLUpload();
	/***********************************************************************/
	

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
	glBindVertexArray(VAOs[VAO_SamData]);
	glDrawArrays(GL_LINE_STRIP, 0, SamCount);
}

void WaveViewer::COMdisplay()
{
}
