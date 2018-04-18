#include "stdafx.h"
#include "Mygl.h"


GLuint Mygl::GLInit()
{

	if (!glfwInit())  return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1920, 960, "Hello World", NULL, NULL);		if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		return -1;
	}
	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);

	glewInit();

	glPointSize(4);  //设置4个像素为一点
	glLineWidth(1);  //设置线宽为4

	
}

GLuint Mygl::DataInit()
{
	glCreateVertexArrays(NumVAOs, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
										  //创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中
	glCreateBuffers(NumBuffers, Buffers);  //等效glGenBuffers(NumBuffers, Buffers);
										   //创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中
	glBindVertexArray(VAOs[SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_SamData]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(Chunk), Chunk, GL_DYNAMIC_STORAGE_BIT);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));  
	//顶点索引及格式设置
	glEnableVertexAttribArray(vPosition); //应用该索引及格式


	glBindVertexArray(VAOs[Xaxis]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_Xaxis]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(ZeroLine), ZeroLine, GL_DYNAMIC_STORAGE_BIT);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	//顶点索引及格式设置
	glEnableVertexAttribArray(vPosition); //应用该索引及格式

	XaxisShader = Shader("shaders/triangles/Xaxis.vert", "shaders/triangles/Xaxis.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return GLuint();
}

void Mygl::display()
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //设置默认清除色black


	XaxisShader.use();
	glBindVertexArray(VAOs[Xaxis]);
	glDrawArrays(GL_LINES, 0, NumVertices_Xaxis);

	//***************************************************************

	glm::mat4 trans;
	GLfloat t = sin(glfwGetTime());
	trans = glm::translate(trans, glm::vec3(t, 0.0f, 0.0f));

	SamDataShader.use();
	GLuint transLoc = glGetUniformLocation(SamDataShader.ID, "trans");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(VAOs[SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_SamData]);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat), sizeof(GLfloat), &t);
	//glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), sizeof(GLfloat), &t);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(GLfloat), sizeof(GLfloat), &t);
	glBufferSubData(GL_ARRAY_BUFFER, 7 * sizeof(GLfloat), sizeof(GLfloat), &t);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumVertices_SamData);
}

GLuint Mygl::Run()
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
		glfwPollEvents();
	}

	return GLuint();
}

Mygl::Mygl()
{
}

Mygl::~Mygl()
{
	glfwTerminate();
}
