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

	struct Vertex
	{
		GLfloat Position[2];
	};
	Vertex * vertices;
	Vertex Frame[2];
	int SamCount;
	int NumVertices_Frame;
public:
	enum Attrib_IDs { vPos, vOffset, vScale };          //属性相关ID

	GLuint VAOs[NumVAO];         //定义 顶点数组对象数组
	GLuint VBOs[NumVBO];		 //定义 缓冲对象     数组

	Shader FrameShader;
	Shader SamDataShader;
	
public:
	GLuint GLInit();
	GLuint GLUpload();

	GLuint UpdateSample();

	char* checkError();

	void glVersion();
	void frameDisplay();
	
	Mygl();
	~Mygl();
};

