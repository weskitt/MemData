#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();

	/************************************************************************/
	GetPCMData(file);
	SamCount = vSamples.size();
	vertices = new Vertex[SamCount];
	for (size_t i = 0; i < SamCount; i++)
	{
		vertices[i].Position[0] = -1.0f + (i / (GLfloat)(SamCount - 1))*2.0f;
		vertices[i].Position[1] = (GLfloat)vSamples[i] / SHRT_MAX;  //SHRT_MAX 32767
	}
	/***********************************************************************/
	
	DataInit();
	return true;
}

void WaveViewer::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		/* ����������Ⱦ */
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* ����������������window�ϸ������� */
		glfwSwapBuffers(window);

		/* ��ѯ�¼� */
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
