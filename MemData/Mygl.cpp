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
	GLuint const SamCount = 600;

	glm::mat4 scales[SamCount];
	glm::mat4 scale;
	GLfloat Y_scale = 0.001f;
	//GLfloat t = ;
	

	glm::vec2 offsets[SamCount];
	glm::vec2 offset;
	GLfloat X_offset = 0.001f;
	for (GLuint index = 0; index < SamCount; index++)
	{
		offset.x =  X_offset;
		offset.y = 0.0f;
		offsets[index] = offset;
		X_offset += 0.003f;

		glm::mat4 scale;
		scale = glm::scale(scale, glm::vec3(1.0f, Y_scale, 1.0f));
		scales[index] = scale;
		Y_scale += 0.001f;
	}
//sin(glfwGetTime())


	glCreateVertexArrays(NumVAO, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
										  //创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中
	glCreateBuffers(NumVBO, VBOs);  //等效glGenBuffers(NumBuffers, Buffers);
										   //创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中
	
	


	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Chunk), Chunk, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));  
	glEnableVertexAttribArray(vPos); 

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Offset]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 600, &offsets[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vOffset, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vOffset);
	glVertexAttribDivisor(vOffset, 1);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Scale]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 600, &scales[0], GL_STATIC_DRAW);
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(vScale + i, //mat4类型会占领连续的4个位置,因此vScale占领了2,3,4,5四个索引位置。
							  4, GL_FLOAT, GL_FALSE, // vec4
							  sizeof(glm::mat4),	 // Stride
							  (void *)(sizeof(glm::vec4)* i)); // Start offset
		glEnableVertexAttribArray(vScale + i);
		glVertexAttribDivisor(vScale + i, 1);
	}
	//glBindVertexArray(0);
	//glVertexAttribPointer(vScale, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	//glEnableVertexAttribArray(vScale);
	//glVertexAttribDivisor(vScale, 1);
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
	glDrawArrays(GL_LINES, 0, NumVertices_Xaxis);

	//***************************************************************

	//定义矩阵

	//传输矩阵
	SamDataShader.use();
	//GLuint transLoc = glGetUniformLocation(SamDataShader.ID, "trans");
	//glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat), sizeof(GLfloat), &Sample[SamUp]);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamUp]);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamDown]);
	glBufferSubData(GL_ARRAY_BUFFER, 7 * sizeof(GLfloat), sizeof(GLfloat), &Sample[SamDown]);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, NumVertices_SamData, 1000);
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
