#pragma once
class Mygl
{

	GLFWwindow* window;   /* ��ʼ��glfw�� */

	enum VAO_IDs { Xaxis, SamData, NumVAOs };        //��������������ID
	enum Buffer_IDs { ArrayBuffer_Xaxis, ArrayBuffer_SamData, NumBuffers }; //���黺�����ID
	enum Attrib_IDs { vPosition = 0 };          //�������ID

	GLuint VAOs[NumVAOs];         //���� ����������� ����
	GLuint Buffers[NumBuffers];   //���� �������     ����
	const GLuint NumVertices_Xaxis = 2; //���� ����	      ����
	const GLuint NumVertices_SamData = 4;



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
		{ -0.0025f, 0.5f },{ 0.0025f, 0.5f },
		{ -0.0025f, -0.5f },{ 0.0025f, -0.5f }
	};
public:
	GLuint GLInit();
	GLuint DataInit();
	void display();
	GLuint Run();
	Mygl();
	~Mygl();
};

