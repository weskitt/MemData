#include "stdafx.h"
#include "Mygl.h"

bool Mygl::Wflag = true;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_2:
		Mygl::Wflag = false;
		break;
	case GLFW_KEY_1:
		Mygl::Wflag = true;
		break;
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	default:
		break;
	}
}
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
GLuint Mygl::GLInit()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())  return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1920, 960, "Hello World", NULL, NULL);	
	if (!window)
	{
		/* 没有创建会返回NULL */
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	/* 设置当前的窗口上下文 */
	glfwMakeContextCurrent(window);

	glewInit();

	glPointSize(1);  //设置4个像素为一点
	glLineWidth(1);  //设置线宽为4

	glVersion();
}

GLuint Mygl::GLUpload(int PCMSamCount, int COMSamCount)
{   
	//glfwGetTime();
	glCreateVertexArrays(NumVAO, VAOs);  //等效glGenVertexArrays(NumVAOs, VAOs)
										  //创建 NumVAOs 个未使用的 VAO对象 到数组VAOs中
	glCreateBuffers(NumVBO, VBOs);  //等效glGenBuffers(NumBuffers, Buffers);
										   //创建 NumBuffers 个未使用的 缓冲对象VBO 到数组Buffers中

	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_PCMSamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*PCMSamCount, PCMvertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));  
	glEnableVertexAttribArray(vPos); 
	/*glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Offset]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * SamCount, &offsets[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vOffset, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vOffset);
	glVertexAttribDivisor(vOffset, 1);
	Error = checkError();
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Instance_Scale]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * SamCount, &scales[0], GL_STATIC_DRAW);
	for (int i = 0; i < 4; i++)
	{
		glVertexAttribPointer(vScale + i, //mat4类型会占领连续的4个位置,因此vScale占领了2,3,4,5四个索引位置。
							  4, GL_FLOAT, GL_FALSE, // vec4
							  sizeof(glm::mat4),	 // Stride
							  (void *)(sizeof(glm::vec4)* i)); // Start offset
		glEnableVertexAttribArray(vScale + i);
		glVertexAttribDivisor(vScale + i, 1);
	}
	Error = checkError();
	*/
	glBindVertexArray(VAOs[VAO_Frame]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_Frame]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Frame), Frame, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPos); 


	glBindVertexArray(0);

	return GLuint();
}

GLuint Mygl::UpdateSample(int PCMSamCount)
{
	//this->Sample[]
	/*
	for (GLuint i = 0; i < SamCount; i++)
	{
		GLfloat x = -1.0f + (i / (GLfloat)(SamCount - 1))*2.0f;
		vertices[i].Position[0] = x;//x
		vertices[i].Position[1] =
			sin(x * wPams[w1].wT) / wPams[w1].pScale;
			/*+ sin(x * wPams[w1].wT) / wPams[w1].pScale
			+ sin(x * wPams[w2].wT) / wPams[w2].pScale
			+ sin(x * wPams[w3].wT) / wPams[w3].pScale
			+ sin(x * wPams[w4].wT) / wPams[w4].pScale
			+ sin(x * wPams[w5].wT) / wPams[w5].pScale
			+ sin(x * wPams[w6].wT) / wPams[w6].pScale
			+ sin(x * wPams[w7].wT) / wPams[w7].pScale
			+ sin(x * wPams[w8].wT) / wPams[w8].pScale
			+ sin(x * wPams[w9].wT) / wPams[w9].pScale;
	}
	*/
	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_PCMSamData]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * PCMSamCount, &PCMvertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return 0;
}

char* Mygl::checkError()
{
	//while ((error = glGetError()) != GL_NO_ERROR)
	//{
		// Process/log the error.
	//}
	switch (glGetError())
	{
	case  GL_NO_ERROR:
		return ("GL_NO_ERROR\n");
	case GL_INVALID_ENUM:
		return ("GL Invalid Enum\n");
	case GL_INVALID_VALUE:
		return ("GL Invalid Value\n");
	case GL_INVALID_OPERATION:
		return ("GL Invalid Operation\n");
	case GL_OUT_OF_MEMORY:
		return ("GL Out Of Memory\n");
		//case GL_INVALID_FRAMEBUFFER_OPERATION:  
		//  return ("GL Invalid FrameBuffer Operation\n");  
	case  GL_STACK_OVERFLOW:
		return ("GL Stack Overflow\n");
	case GL_STACK_UNDERFLOW:
		return ("GL Stack Underflow\n");
		//case GL_TABLE_TOO_LARGE:  
		//  return ("GL Table Too Large\n");  
	};
	return "GL Undefined Error";
}

 void Mygl::glVersion()
{

	cout << "OpenGL:" << endl;
	cout << glGetString(GL_VENDOR) << endl;
	cout << glGetString(GL_RENDERER) << endl;
	cout << glGetString(GL_VERSION) << "\n" << endl;
	//cout << glGetString(GLEW_VERSION) << endl;
	//glewGetString
	cout << "GLEW:" << endl;
	cout << glewGetString(GLEW_VERSION) << "\n" << endl;

	cout << "GLFW:" << endl;
	cout << glfwGetVersionString() << "\n" << endl;

	//cout << glfwGetTime() << "\n" << endl;
	
}

void Mygl::frameDisplay()
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black); //设置默认清除色black

	FrameShader.use();
	glBindVertexArray(VAOs[VAO_Frame]);
	glDrawArrays(GL_LINE_STRIP, 0, NumVertices_Frame);
}


Mygl::Mygl()
{
}

Mygl::~Mygl()
{
	glfwTerminate();
}

