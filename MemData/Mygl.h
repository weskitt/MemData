#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

class Mygl
{

	GLFWwindow* window;   /* 初始化glfw库 */
	char* Error;

	enum VAO_IDs { VAO_Xaxis, VAO_SamData, NumVAO };    //顶点数组对象相关ID
	
	enum VBO_IDs { VBO_Xaxis, 
				   VBO_SamData, 
				   VBO_Instance_Offset, 
				   VBO_Instance_Scale, 
				   NumVBO }; //数组缓冲相关ID

	enum Attrib_IDs { vPos, vOffset, vScale };          //属性相关ID
	enum Sample_IDs { SamUp, SamDown, NumYaxis, NumSam=2 };
	enum Wave_IDs { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, WaveCount = 10 };
	enum DataCountInit{ Zero_Dim, One_Dim, Two_Dim, Three_Dim, 
						SamCount=1000, NumVertices_Xaxis = 2 };

	GLuint VAOs[NumVAO];         //定义 顶点数组对象 数组
	GLuint VBOs[NumVBO];		 //定义 缓冲对象     数组
	

	const GLfloat ScaleFactor = 0.2f;
	const GLfloat PI = 3.1415926f;
	const GLfloat Begin_offset = -1.0f;

	const GLfloat wScale0 = ScaleFactor, wT0 = 0.01f, wBegin_Offset0 = 1.000f;
	const GLfloat wScale1 = ScaleFactor, wT1 = 0.05f, wBegin_Offset1 = 0.990f;
	const GLfloat wScale2 = ScaleFactor, wT2 = 0.10f, wBegin_Offset2 = 0.800f;
	const GLfloat wScale3 = ScaleFactor, wT3 = 0.50f, wBegin_Offset3 = 0.980f;
	const GLfloat wScale4 = ScaleFactor, wT4 = 1.00f, wBegin_Offset4 = 0.975f;

	
	struct Vertex
	{
		GLfloat Position[2];
	};

	Vertex vertices[SamCount];

	

	Shader XaxisShader;
	Shader SamDataShader;


public:
	GLuint GLInit();
	GLuint DataInit();

	GLuint UpdateSample();
	char* checkError();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void display();
	//void creatTestWave(GLfloat t, GLfloat scale_Y, GLfloat beginoffset, GLuint wx,  GLfloat (&waveData)[WaveCount][SamCount]);Vertex vertices[SamCount]
	void creatTestWave(GLfloat t, GLfloat scale_Y, GLfloat beginoffset, GLuint wx, Vertex (&vertices)[SamCount]);
	GLuint Run();
	Mygl();
	~Mygl();
};

