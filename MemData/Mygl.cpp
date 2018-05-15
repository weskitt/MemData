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
	const GLuint SamCount = 1000;
	const GLfloat factor = 0.5f;
	const GLfloat PI = 3.1415926f;
	GLuint w1 = 0;
	GLfloat X_offset = -0.999f;
	//GLfloat x = -1000 * PI;
	GLfloat x = 0.0f;

	GLfloat preData[SamCount][2];
	while (w1 < SamCount)
	{
		//preData[w1] = sin(w1);
		preData[w1][0] = X_offset;
		preData[w1][1] = sin(x)*factor;
		X_offset += 0.002;
		x += 0.1f;
		++w1;

	}
	GLfloat ZeroLine[2][2] =   //定义NumVertices个二维顶点 数据
	{
		{ -1.5f, 0.0f },{ 1.5f, 0.0f }//,{-0.9, 0.85},  //triangle 1
									//{0.9, -0.85},{0.9, 0.9}, {-0.85, 0.9}    //triangle 2
	};
	//GLfloat Chunk[4][2] =
	//{
	//	{ -0.999f, 0.5f },{ -0.997f, 0.5f },   //4    12
	//	{ -0.999f, -0.5f },{ -0.997f, -0.5f }  //20   28
	//};
	GLfloat Data[1][2] = {
		{ -0.999f, 0.0f },
	};

	
	//缩放矩阵
	glm::mat4 scales[SamCount];
	glm::mat4 scale;

	glm::vec2 offsets[SamCount];
	glm::vec2 offset;
	
	GLfloat Y_offset = 0.0f;
	for (GLuint index = 0; index < SamCount; index++)
	{
		offset.x =  X_offset;
		offset.y = 0.5f;
		offsets[index] = offset;
		X_offset += 0.02f;

		glm::mat4 scale;
		scale = glm::scale(scale, glm::vec3(1.0f, 0.5f, 1.0f));
		scales[index] = scale;
		//Y_scale += 0.001f;
	}
	//sin(glfwGetTime())


	glCreateVertexArrays(NumVAO, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
										  //创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中
	glCreateBuffers(NumVBO, VBOs);  //等效glGenBuffers(NumBuffers, Buffers);
										   //创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中
	
	

	Error = checkError();
	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(preData), preData, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));  
	glEnableVertexAttribArray(vPos); 
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Offset]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * SamCount, &offsets[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vOffset, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vOffset);
	glVertexAttribDivisor(vOffset, 1);
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Scale]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * SamCount, &scales[0], GL_STATIC_DRAW);
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(vScale + i, //mat4类型会占领连续的4个位置,因此vScale占领了2,3,4,5四个索引位置。
							  4, GL_FLOAT, GL_FALSE, // vec4
							  sizeof(glm::mat4),	 // Stride
							  (void *)(sizeof(glm::vec4)* i)); // Start offset
		glEnableVertexAttribArray(vScale + i);
		glVertexAttribDivisor(vScale + i, 1);
	}
	Error = checkError();

	glBindVertexArray(VAOs[VAO_Xaxis]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Xaxis]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZeroLine), ZeroLine, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPos); 
	glBindVertexArray(0);
	Error = checkError();

	XaxisShader = Shader("shaders/triangles/Xaxis.vert", "shaders/triangles/Xaxis.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return GLuint();
}

GLuint Mygl::UpdateSample()
{
	//this->Sample[]
	return GLuint();
}

char* Mygl::checkError()
{
	//while ((error = glGetError()) != GL_NO_ERROR)
	//{
		// Process/log the error.
	//}
	switch (glGetError())
	{
	case  GL_NO_ERROR:
		return ("GL_NO_ERROR\n");
	case GL_INVALID_ENUM:
		return ("GL Invalid Enum\n");
	case GL_INVALID_VALUE:
		return ("GL Invalid Value\n");
	case GL_INVALID_OPERATION:
		return ("GL Invalid Operation\n");
	case GL_OUT_OF_MEMORY:
		return ("GL Out Of Memory\n");
		//case GL_INVALID_FRAMEBUFFER_OPERATION:  
		//  return ("GL Invalid FrameBuffer Operation\n");  
	case  GL_STACK_OVERFLOW:
		return ("GL Stack Overflow\n");
	case GL_STACK_UNDERFLOW:
		return ("GL Stack Underflow\n");
		//case GL_TABLE_TOO_LARGE:  
		//  return ("GL Table Too Large\n");  
	};
	return "GL Undefined Error";
}

void Mygl::display()
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //设置默认清除色black


	XaxisShader.use();
	glBindVertexArray(VAOs[VAO_Xaxis]);
	glDrawArrays(GL_LINE_STRIP, 0, NumVertices_Xaxis);

	//***************************************************************

	//定义矩阵

	//传输矩阵
	SamDataShader.use();
	//GLuint transLoc = glGetUniformLocation(SamDataShader.ID, "trans");
	//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat), sizeof(GLfloat), &Sample[SamUp]);
	//glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamUp]);
	//glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamDown]);
	//glBufferSubData(GL_ARRAY_BUFFER, 7 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamDown]);
	//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, NumVertices_SamData, 1000);
	glDrawArrays(GL_LINE_STRIP, 0, NumVertices_SamData);

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
