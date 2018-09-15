#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();

	/************************************************************************/
	GetPCMData(file);
	SamCount = vSamples.size();
	//unique_ptr<Vertex[]> vertices(new Vertex[SamCount]);
	vertices = new Vertex[SamCount];
	//vertices.
	for (size_t i = 0; i < SamCount; i++)
	{
		vertices[i].Position[0] = -1.0f + (i / (GLfloat)(SamCount - 1))*2.0f;
		vertices[i].Position[1] = (GLfloat)vSamples[i] / SHRT_MAX;  //SHRT_MAX 32767
		//cout << "i = " << i << endl;
		//cout << "vertices[i].Position[0] = " << vertices[i].Position[0] << endl;
		//cout << "vertices[i].Position[1] = " << vertices[i].Position[1] << endl;
	}
	/***********************************************************************/
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
	Error = checkError();
}

void WaveViewer::PCMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	glDrawArrays(GL_LINE_STRIP, 0, SamCount);
}

void WaveViewer::COMdisplay()
{
}
