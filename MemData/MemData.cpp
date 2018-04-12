// MemData.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"



enum VAO_IDs { Triangles, NumVAOs };        //顶点数组对象相关ID
enum Buffer_IDs {ArrayBuffer, NumBuffers }; //数组缓冲相关ID
enum Attrib_IDs { vPosition = 0 };          //属性相关ID

GLuint VAOs[NumVAOs];         //定义 顶点数组对象 数组
GLuint Buffers[NumBuffers];   //定义 缓冲对象     数组
const GLuint NumVertices = 6; //定义 顶点	      个数

void init(void)
{
	GLfloat vertices[NumVertices][2]=   //定义NumVertices个二维顶点 数据
	{
		{-0.9, -0.9},{0.85, -0.9},{-0.9, 0.85},  //triangle 1
		{0.9, -0.85},{0.9, 0.9}, {-0.85, 0.9}    //triangle 2
	};

	
	glCreateVertexArrays(NumVAOs, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
	//创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中
	glBindVertexArray(VAOs[Triangles]);


	glCreateBuffers(NumBuffers, Buffers);  //等效glGenBuffers(NumBuffers, Buffers);
	//创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	//绑定缓存对象为 GL_ARRAY_BUFFER模式上下文 来为后面储存顶点数据
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
	//将数据载入缓存对象，glNamedBufferStorage(Buffers[ArrayBuffer],...)直接作用于buffer指定的缓冲
	
	

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "shaders/triangles/triangles.vert"},
		{GL_FRAGMENT_SHADER, "shaders/triangles/triangles.frag"},
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	//顶点索引及格式设置
	glEnableVertexAttribArray(vPosition); //应用该索引及格式
}

void display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //设置默认清除色black
	glBindVertexArray(VAOs[Triangles]);  //绑定对象
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
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

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
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

