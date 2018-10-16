#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

class Mygl :
	public AllDataBase
{
public:	
	const GLuint WIDTH = 1920, HEIGHT = 960;
	GLFWwindow* window;   /* ��ʼ��glfw�� */
	char* Error;
	static bool Wflag;

	enum VAO_IDs { VAO_Frame, 
				   VAO_Text, 
				   VAO_PCMSamData, 
				   VAO_COMSamData, 
				   NumVAO };    //��������������ID
	
	enum VBO_IDs { VBO_Frame,
				   VBO_Text,
				   VBO_PCMSamData, 
				   VBO_COMSamData, 
				   //VBO_Instance_Offset, 
				   //VBO_Instance_Scale, 
				   NumVBO }; //���黺�����ID

	enum Wave_IDs { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, WaveCount };

	struct Vertex
	{
		GLfloat Position[2];
	};
	Vertex * PCMvertices;
	Vertex * COMvertices;
	Vertex Frame[2];

	int NumVertices_Frame;
public:
	enum Attrib_IDs { vType_Position, vType_Offset, vType_Scale };          //�������ID

	GLuint VAOs[NumVAO];         //���� ���������������
	GLuint VBOs[NumVBO];		 //���� �������     ����

	Shader FrameShader;
	Shader SamDataShader;

public:
	FT_Library ft;
	FT_Face face;

public:
	void FTInit();
	GLuint GLInit();
	GLuint GLUpload(int PCMSamCount, int COMSamCount);
	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	GLuint UpdateSample(int COMSamCount);

	char* checkError();

	void glVersion();
	void frameDisplay();
	
	Mygl();
	~Mygl();
};

