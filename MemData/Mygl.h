#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

class Mygl
{
public:	
	GLFWwindow* window;   /* ��ʼ��glfw�� */
	char* Error;
	
	static const GLint AddsOperand;
	static const GLint SubtractsOperand;

	enum VAO_IDs { VAO_Frame, VAO_SamData, NumVAO };    //��������������ID
	
	enum VBO_IDs { VBO_Frame,
				   VBO_SamData, 
				   VBO_Instance_Offset, 
				   VBO_Instance_Scale, 
				   NumVBO }; //���黺�����ID

	enum Wave_IDs { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, WaveCount };
	
	enum Wave_Operate { Adds, Subtracts, Multiplied, Divides, WeightMod, AverageMod };
	
	enum DataCountInit {
		Zero_Dim, One_Dim, Two_Dim, Three_Dim,
		NumVertices_Frame = 2
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
	Vertex * vertices;
	int SamCount;
public:
	enum Attrib_IDs { vPos, vOffset, vScale };          //�������ID
	enum Sample_IDs { SamUp, SamDown, NumYaxis, NumSam=2 };

	static GLuint VAOs[NumVAO];         //���� ���������������
	static GLuint VBOs[NumVBO];		 //���� �������     ����
	

	const GLfloat ScaleFactor = 0.2f;
	const GLfloat PI = 3.1415926f;

	static WaveParam wPams[WaveCount];

	

	

	Shader FrameShader;
	Shader SamDataShader;


public:
	GLuint GLInit();
	GLuint DataInit();

	GLuint UpdateSample();
	//static 
	char* checkError();

	void glVersion();
	void frameDisplay();
	//void creatTestWave(GLfloat t, GLfloat scale_Y, GLfloat beginoffset, GLuint wx,  GLfloat (&waveData)[WaveCount][SamCount]);Vertex vertices[SamCount]
	//static void creatTestWave(Vertex (&vertices)[SamCount]);
	static void PscaleRedistribute(Wave_IDs wId, GLint operand, Wave_Operate rMod);
	Mygl();
	~Mygl();
};

