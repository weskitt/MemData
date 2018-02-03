// MemData.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs {ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

void init(void)
{
	GLfloat vertices[NumVertices][2]=
	{
		{-0.9, -0.9},{0.85, -0.9},{-0.9, 0.85},  //triangle 1
		{0.9, -0.85},{0.9, 0.9}, {-0.85, 0.9}    //triangle 2
	};

	//glGenBuffers(NumBuffers, Buffers);
	glCreateBuffers(NumBuffers, Buffers);
	
	
	
}




int main()
{

	READWAVE Rwave;
	Rwave.GetData("cai3.wav");



	GLFWwindow* window;
	/* 初始化glfw库 */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		return -1;
	}

	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);

	/* 循环，直到用户关闭窗口 */
	while (!glfwWindowShouldClose(window))
	{
		/* 在这里做渲染 */
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		/* 交换缓冲区，即在window上更新内容 */
		glfwSwapBuffers(window);

		/* 轮询事件 */
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}

