#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

static class Mygl
{

	GLFWwindow* window;   /* ��ʼ��glfw�� */
	char* Error;

public:	

	static const GLint AddsOperand;
	static const GLint SubtractsOperand;

	enum VAO_IDs { VAO_Xaxis, VAO_SamData, NumVAO };    //��������������ID
	enum VBO_IDs { VBO_Xaxis,
				   VBO_SamData, 
				   VBO_Instance_Offset, 
				   VBO_Instance_Scale, 
				   NumVBO }; //���黺�����ID
	enum Wave_IDs { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, WaveCount };
	enum Wave_Operate { Adds, Subtracts, Multiplied, Divides, WeightMod, AverageMod };
	enum DataCountInit {
		Zero_Dim, One_Dim, Two_Dim, Three_Dim,
		SamCount = 1000, NumVertices_Xaxis = 2
	};
	static GLfloat baseT;
	static GLfloat curT;
	struct WaveParam
	{
		GLfloat wT = 0.0f;
		GLfloat pScale = 0.0f;
		GLfloat weight = 0.0f;
	};
	struct Vertex
	{
		GLfloat Position[2];
	};

private:
	enum Attrib_IDs { vPos, vOffset, vScale };          //�������ID
	enum Sample_IDs { SamUp, SamDown, NumYaxis, NumSam=2 };

	static GLuint VAOs[NumVAO];         //���� ���������������
	static GLuint VBOs[NumVBO];		 //���� �������     ����
	

	const GLfloat ScaleFactor = 0.2f;
	const GLfloat PI = 3.1415926f;

	static WaveParam wPams[WaveCount];

	static Vertex vertices[SamCount];

	Shader XaxisShader;
	Shader SamDataShader;


public:
	GLuint GLInit();
	GLuint DataInit();

	static GLuint UpdateSample();
	//static 
	char* checkError();

	void glVersion();
	void display();
	//void creatTestWave(GLfloat t, GLfloat scale_Y, GLfloat beginoffset, GLuint wx,  GLfloat (&waveData)[WaveCount][SamCount]);Vertex vertices[SamCount]
	//static void creatTestWave(Vertex (&vertices)[SamCount]);
	static void PscaleRedistribute(Wave_IDs wId, GLint operand, Wave_Operate rMod);
	GLuint Run();
	Mygl();
	~Mygl();
};

