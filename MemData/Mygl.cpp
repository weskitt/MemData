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

	dataInit();
}

GLuint Mygl::dataInit()
{
	glCreateVertexArrays(NumVAOs, VAOs);  //��ЧglGenVertexArrays(NumVAOs, VAOs)
										  //���� NumVAOs ��δʹ�õ� VAO���� ������VAOs��
	glCreateBuffers(NumBuffers, Buffers);  //��ЧglGenBuffers(NumBuffers, Buffers);
										   //���� NumBuffers ��δʹ�õ� �������VBO ������Buffers��
	glBindVertexArray(VAOs[SamData]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_SamData]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(Chunk), Chunk, 0);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));  //������������ʽ����
	glEnableVertexAttribArray(vPosition); //Ӧ�ø���������ʽ


	glBindVertexArray(VAOs[Xaxis]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer_Xaxis]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(ZeroLine), ZeroLine, 0);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));//������������ʽ����
	glEnableVertexAttribArray(vPosition); //Ӧ�ø���������ʽ

	XaxisShader = Shader("shaders/triangles/Xaxis.vert", "shaders/triangles/Xaxis.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return GLuint();
}

void Mygl::display()
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //����Ĭ�����ɫblack


	glBindVertexArray(VAOs[Xaxis]);
	XaxisShader.use();
	glDrawArrays(GL_LINES, 0, NumVertices_Xaxis);


	glBindVertexArray(VAOs[SamData]);
	SamDataShader.use();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NumVertices_SamData);
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
