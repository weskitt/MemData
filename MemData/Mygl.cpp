#include "stdafx.h"
#include "Mygl.h"

bool Mygl::Wflag = false;

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
void Mygl::FTInit()
{
	
	if (FT_Init_FreeType(&ft))
		cout << "ERROR::FREETYPE: Could not init FreeType Library" << endl;

	
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		cout << "ERROR::FREETYPE: Failed to load font" << endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //����byte-alignment����
	for (GLubyte c = 0; c < 128; c++)
	{
		// �����ַ������� 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// ������������
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// ��������ѡ��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// ���ַ��洢���ַ����б���
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
}
GLuint Mygl::GLInit()
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())  return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);	
	if (!window)
	{
		/* û�д����᷵��NULL */
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);
	/* ���õ�ǰ�Ĵ��������� */
	glfwMakeContextCurrent(window);

	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	//������ͶӰ
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WIDTH), 0.0f, static_cast<GLfloat>(HEIGHT));
	FrameShader = Shader("shaders/triangles/Frame.vert", "shaders/triangles/Frame.frag");
	FrameShader.use();
	glUniformMatrix4fv(glGetUniformLocation( , "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Set OpenGL options
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glPointSize(1);  //����4������Ϊһ��
	glLineWidth(1);  //�����߿�Ϊ4

	glVersion();
}

GLuint Mygl::GLUpload(int PCMSamCount, int COMSamCount)
{   
	//glfwGetTime();
	glCreateVertexArrays(NumVAO, VAOs);  //��ЧglGenVertexArrays(NumVAOs, VAOs)
										  //���� NumVAOs ��δʹ�õ� VAO���� ������VAOs��
	glCreateBuffers(NumVBO, VBOs);  //��ЧglGenBuffers(NumBuffers, Buffers);
										   //���� NumBuffers ��δʹ�õ� �������VBO ������Buffers��

	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_PCMSamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*2*PCMSamCount, PCMvertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));  
	glEnableVertexAttribArray(vPos); 
	checkError();
	glBindVertexArray(VAOs[VAO_COMSamData]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[VBO_COMSamData]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * COMSamCount, COMvertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPos);
	checkError();
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
		glVertexAttribPointer(vScale + i, //mat4���ͻ�ռ��������4��λ��,���vScaleռ����2,3,4,5�ĸ�����λ�á�
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

void Mygl::RenderText(Shader & shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
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
		cout << "GL_NO_ERROR\n" << endl;
		return ("GL_NO_ERROR\n");
	case GL_INVALID_ENUM:
		cout << "GL Invalid Enum\n" << endl;
		return ("GL Invalid Enum\n");
	case GL_INVALID_VALUE:
		cout << "GL Invalid Value\n" << endl;
		return ("GL Invalid Value\n");
	case GL_INVALID_OPERATION:
		cout << "GL Invalid Operation\n" << endl;
		return ("GL Invalid Operation\n");
	case GL_OUT_OF_MEMORY:
		cout << "GL Out Of Memory\n" << endl;
		return ("GL Out Of Memory\n");
		//case GL_INVALID_FRAMEBUFFER_OPERATION:  
		//  return ("GL Invalid FrameBuffer Operation\n");  
	case  GL_STACK_OVERFLOW:
		cout << "GL Stack Overflow\n" << endl;
		return ("GL Stack Overflow\n");
	case GL_STACK_UNDERFLOW:
		cout << "GL Stack Underflow\n" << endl;
		return ("GL Stack Underflow\n");
		//case GL_TABLE_TOO_LARGE:  
		//  return ("GL Table Too Large\n");  
	};
	cout << "GL Undefined Error\n" << endl;
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
	glClearBufferfv(GL_COLOR, 0, black); //����Ĭ�����ɫblack

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

