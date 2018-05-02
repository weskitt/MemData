#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

class Mygl
{

	GLFWwindow* window;   /* ��ʼ��glfw�� */

	enum VAO_IDs { VAO_Xaxis, VAO_SamData, NumVAO };        //��������������ID
	
	enum VBO_IDs { VBO_Xaxis, 
				   VBO_SamData, 
				   VBO_Instance_Offset, 
				   VBO_Instance_Scale, 
				   NumVBO }; //���黺�����ID

	enum Attrib_IDs { vPos, vOffset, vScale };          //�������ID
	enum Sample_IDs { SamUp, SamDown, NumYaxis, NumSam=2 };

	GLuint VAOs[NumVAO];         //���� ����������� ����
	GLuint VBOs[NumVBO];   //���� �������     ����
	const GLuint NumVertices_Xaxis = 2; //���� ����	      ����
	const GLuint NumVertices_SamData = 4;

	GLenum error;
	GLenum xx = (GLuint)GL_INVALID_OPERATION;
	char* Error;

	/*ShaderInfo shaders_Xaxis[] = {
	{ GL_VERTEX_SHADER, "shaders/triangles/Xaxis.vert" },
	{ GL_FRAGMENT_SHADER, "shaders/triangles/Xaxis.frag" },
	{ GL_NONE, NULL }
	};
	GLuint program_Xaxis;
	
	ShaderInfo shaders_SamData[] = {
	{ GL_VERTEX_SHADER, "shaders/triangles/SamData.vert" },
	{ GL_FRAGMENT_SHADER, "shaders/triangles/SamData.frag" },
	{ GL_NONE, NULL }
	};
	GLuint program_SamData;
	//GLuint program;
	
	program = LoadShaders(shaders);
    */

	Shader XaxisShader;
	Shader SamDataShader;

	GLfloat ZeroLine[2][2] =   //����NumVertices����ά���� ����
	{
		{ -1.5f, 0.0f },{ 1.5f, 0.0f }//,{-0.9, 0.85},  //triangle 1
									//{0.9, -0.85},{0.9, 0.9}, {-0.85, 0.9}    //triangle 2
	};
	GLfloat Chunk[4][2] =
	{
		{ -0.999f, 0.5f },{ -0.997f, 0.5f },   //4    12
		{ -0.999f, -0.5f },{ -0.997f, -0.5f }  //20   28
	};

	GLfloat Sample[NumSam]= { 0.2f, -0.4f };


public:
	GLuint GLInit();
	GLuint DataInit();
	GLuint UpdateSample();
	char* checkError();
	void display();
	GLuint Run();
	Mygl();
	~Mygl();
};

