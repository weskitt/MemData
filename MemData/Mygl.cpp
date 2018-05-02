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
		/* û�д����᷵��NULL */
		glfwTerminate();
		return -1;
	}
	/* ���õ�ǰ�Ĵ��������� */
	glfwMakeContextCurrent(window);

	glewInit();

	glPointSize(4);  //����4������Ϊһ��
	glLineWidth(1);  //�����߿�Ϊ4

	
}

GLuint Mygl::DataInit()
{
	GLuint const SamCount = 600;

	glm::mat4 scales[SamCount];
	glm::mat4 scale;
	//GLfloat t = ;
	

	glm::vec2 offsets[SamCount];
	glm::vec2 offset;
	GLfloat X_offset = 0.001f;
	for (GLuint index = 0; index < SamCount; index++)
	{
		offset.x =  X_offset;
		offset.y = 0.0f;
		offsets[index] = offset;
		offset += 0.003f;;

		scale = glm::scale(scale, glm::vec3(0.0f, sin(glfwGetTime()), 0.0f));
		scales[index] = scale;
	}



	glCreateVertexArrays(NumVAO, VAOs);  //��ЧglGenVertexArrays(NumVAOs, VAOs)
										  //���� NumVAOs ��δʹ�õ� VAO���� ������VAOs��
	glCreateBuffers(NumVBO, VBOs);  //��ЧglGenBuffers(NumBuffers, Buffers);
										   //���� NumBuffers ��δʹ�õ� �������VBO ������Buffers��
	
	


	glBindVertexArray(VAOs[VAO_SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_SamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Chunk), Chunk, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));  
	glEnableVertexAttribArray(vPos); 
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Offset]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 600, &offsets[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vOffset, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vOffset);
	glVertexAttribDivisor(vOffset, 1);
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Scale]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * 600, &scales[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vScale, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vScale);
	glVertexAttribDivisor(vScale, 1);
	Error = checkError();

	glBindVertexArray(VAOs[VAO_Xaxis]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Xaxis]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZeroLine), ZeroLine, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPos); 
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
	glClearBufferfv(GL_COLOR, 0, black); //����Ĭ�����ɫblack


	XaxisShader.use();
	glBindVertexArray(VAOs[VAO_Xaxis]);
	glDrawArrays(GL_LINES, 0, NumVertices_Xaxis);

	//***************************************************************

	//�������

	//�������
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
		/* ����������Ⱦ */
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* ����������������window�ϸ������� */
		glfwSwapBuffers(window);

		/* ��ѯ�¼� */
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
