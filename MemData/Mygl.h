#pragma once
class Mygl
{

	GLFWwindow* window;   /* 初始化glfw库 */

	enum VAO_IDs { Xaxis, SamData, NumVAOs };        //顶点数组对象相关ID
	enum Buffer_IDs { ArrayBuffer_Xaxis, ArrayBuffer_SamData, NumBuffers }; //数组缓冲相关ID
	enum Attrib_IDs { vPosition = 0 };          //属性相关ID

	GLuint VAOs[NumVAOs];         //定义 顶点数组对象 数组
	GLuint Buffers[NumBuffers];   //定义 缓冲对象     数组
	const GLuint NumVertices_Xaxis = 2; //定义 顶点	      个数
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

	GLfloat ZeroLine[2][2] =   //定义NumVertices个二维顶点 数据
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

