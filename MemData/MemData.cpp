// MemData.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"



enum VAO_IDs { Y_Axis,SamData , NumVAOs };        //顶点数组对象相关ID
enum Buffer_IDs {ArrayBuffer_Yaxis, ArrayBuffer_SamData, NumBuffers }; //数组缓冲相关ID
enum Attrib_IDs { vPosition = 0 };          //属性相关ID

GLuint VAOs[NumVAOs];         //定义 顶点数组对象 数组
GLuint Buffers[NumBuffers];   //定义 缓冲对象     数组
const GLuint NumVertices_Yaxis = 2; //定义 顶点	      个数
const GLuint NumVertices_SamData = 4;

void init(void)
{
	GLfloat ZeroLine[NumVertices_Yaxis][2]=   //定义NumVertices个二维顶点 数据
	{
		{-0.98, 0.0},{0.98, 0.0}//,{-0.9, 0.85},  //triangle 1
		//{0.9, -0.85},{0.9, 0.9}, {-0.85, 0.9}    //triangle 2
	};
	GLfloat Chunk[NumVertices_SamData][2]=
	{
		{ -0.00004, 0.25 }, { 0.00004, 0.25 },
		{ -0.00004, -0.25 }, { 0.00004, -0.25 }
	};

	
	glCreateVertexArrays(NumVAOs, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
	//创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中

	glCreateBuffers(NumBuffers, Buffers);  //等效glGenBuffers(NumBuffers, Buffers);
	//创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中
	
	glNamedBufferStorage(Buffers[ArrayBuffer_Yaxis], sizeof(ZeroLine), ZeroLine, 0);
	glNamedBufferStorage(Buffers[ArrayBuffer_SamData], sizeof(Chunk), Chunk, 0);
	//将数据载入缓存对象，glNamedBufferStorage(Buffers[ArrayBuffer],...)直接作用于buffer指定的缓冲
	
	
	

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "shaders/triangles/triangles.vert"},
		{GL_FRAGMENT_SHADER, "shaders/triangles/triangles.frag"},
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glBindVertexArray(VAOs[Y_Axis]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_Yaxis]);

	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//顶点索引及格式设置
	glEnableVertexAttribArray(vPosition); //应用该索引及格式


	glPointSize(4);  //设置4个像素为一点
	glLineWidth(1);  //设置线宽为4
}

void display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //设置默认清除色black
	glBindVertexArray(VAOs[Y_Axis]);  //绑定对象
	glDrawArrays(GL_LINES, 0, NumVertices_Yaxis);

	glBindVertexArray(VAOs[SamData]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumVertices_SamData);
}



int main()
{

	READWAVE Rwave;
	Rwave.GetData("cai3.wav");
	//Rwave.split();


	GLFWwindow* window;   /* 初始化glfw库 */

	if (!glfwInit())  return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1900, 960, "Hello World", NULL, NULL);		if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		return -1;
	}

	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);
	 
	glewInit();

	init();
	/* 循环，直到用户关闭窗口 */
	while (!glfwWindowShouldClose(window))
	{
		/* 在这里做渲染 */
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* 交换缓冲区，即在window上更新内容 */
		glfwSwapBuffers(window);

		/* 轮询事件 */
		glfwPollEvents();
	}

	glfwTerminate();

    return 0;
}

