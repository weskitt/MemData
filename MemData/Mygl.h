#pragma once

#define BUFFER_OFFSET(a) ((void*)(a))

class Mygl
{
public:	
	GLFWwindow* window;   /* 初始化glfw库 */
	char* Error;
	static bool Wflag;


	enum VAO_IDs { VAO_Frame, VAO_SamData, NumVAO };    //顶点数组对象相关ID
	
	enum VBO_IDs { VBO_Frame,
				   VBO_SamData, 
				   VBO_Instance_Offset, 
				   VBO_Instance_Scale, 
				   NumVBO }; //数组缓冲相关ID

	enum Wave_IDs { w0, w1, w2, w3, w4, w5, w6, w7, w8, w9, WaveCount };
	
	enum Wave_Operate { Adds, Subtracts, Multiplied, Divides, WeightMod, AverageMod };
	
	enum DataCountInit {
		Zero_Dim, One_Dim, Two_Dim, Three_Dim,
		NumVertices_Frame = 2
	};

	struct Vertex
	{
		GLfloat Position[2];
	};
	Vertex * vertices;
	int SamCount;
public:
	enum Attrib_IDs { vPos, vOffset, vScale };          //属性相关ID
	enum Sample_IDs { SamUp, SamDown, NumYaxis, NumSam=2 };

	GLuint VAOs[NumVAO];         //定义 顶点数组对象数组
	GLuint VBOs[NumVBO];		 //定义 缓冲对象     数组
	

	const GLfloat ScaleFactor = 0.2f;
	const GLfloat PI = 3.1415926f;
	   	

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
	
	Mygl();
	~Mygl();
};

