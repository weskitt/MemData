#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();
	GetPCMData(file);
	SamCount = vSamples.size();
	Vertex *vertices = new Vertex[SamCount];
	for (size_t i = 0; i < SamCount; i++)
	{
		vertices[i].Position[0] = i;
		vertices[i].Position[1] = vSamples[i] / SHRT_MAX;
	}
	DataInit();
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
	PCMdisplay();
}

void WaveViewer::PCMdisplay()
{
	Error = checkError();
	SamDataShader.use();
	Error = checkError();
	glBindVertexArray(VAOs[VAO_SamData]);
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	Error = checkError();
	glDrawArrays(GL_POINT, 0, SamCount);
	Error = checkError();
}

void WaveViewer::COMdisplay()
{
}
