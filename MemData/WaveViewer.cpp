#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();
	//X����
	/************************************************************************/
	Frame[0].Position[0] = -1.5f;
	Frame[0].Position[1] =  0.0f;
	Frame[1].Position[0] =  1.5f;
	Frame[1].Position[1] =  0.0f;
	NumVertices_Frame = 2;
	/************************************************************************/
	GetPCMData(file);
	PCMSamCount = vSamples.size();
	PCMvertices = new Vertex[PCMSamCount];
	for (size_t i = 0; i < PCMSamCount; i++)
	{
		PCMvertices[i].Position[0] = -1.0f + (i / (GLfloat)(PCMSamCount - 1))*2.0f;
		PCMvertices[i].Position[1] = (GLfloat)vSamples[i] / SHRT_MAX;  //SHRT_MAX 32767
	}
	/*-----------------------------------------------------------------------*/
	GerneralWave();
	MapToVertex();
	/***********************************************************************/
	GLUpload(PCMSamCount, BaseSamCount);	

	FrameShader = Shader("shaders/triangles/Frame.vert", "shaders/triangles/Frame.frag");
	SamDataShader = Shader("shaders/triangles/SamData.vert", "shaders/triangles/SamData.frag");

	return true;
}

void WaveViewer::Run()
{
	checkError();
	while (!glfwWindowShouldClose(window))
	{
		/* ����������Ⱦ */
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* ����������������window�ϸ������� */
		glfwSwapBuffers(window);

		/* ��ѯ�¼� */
		//glfwPollEvents();
		glfwWaitEvents();
	}
}

WaveViewer::WaveViewer()
{
}


WaveViewer::~WaveViewer()
{
}

void WaveViewer::shape(GLfloat & value, VInfoIter info)
{
	if (value > 0){
		value = lastU + info->fusion(*info);
		lastU = value;
		//rootRate += rate0;
	}
	else if (value < 0){
		value = lastD - info->fusion(*info);
		lastD = value;
		//rootRate += rate0;
	}
}
void WaveViewer::GerneralWave()
{
	//����base��������
	GLfloat preAmp = 0.001;  
	int relativeStep = 5;
	int T_step = 13;
	int PackStep = relativeStep + T_step;
	BaseSamCount = 1920 / PackStep;
	COMvertices = new Vertex[BaseSamCount];
	int curX = 0;
	for (size_t i = 0; i < BaseSamCount; i++)
	{
		curX = i * PackStep;
		BaseSamplesMap[curX] = preAmp;
		//������������
		++i;
		curX += relativeStep;
		BaseSamplesMap[curX] = -preAmp;
	}
	/******************************************************************/
	//���μ���   ��������
	PhonationInfo::RootRate=0.04;
	PhonationInfo tInfo;
	Voice tVoice;

	tInfo.areaID = 1;
	tInfo.begin = -1.0;
	tInfo.end = -0.3;
	tInfo.ort = 1.0; //����
	tInfo.rate0 = -0.0005; //����ʱ�� Ϊ��-����͹�� Ϊ��-���ڰ�
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));

	tInfo.areaID = 2;
	tInfo.begin = -0.3;
	tInfo.end = 0.3;
	tInfo.ort = 1.0;//���� �����仯
	tInfo.rate0 = -0.0016;
	tVoice.vinfo.push_back(tInfo);

	tInfo.areaID = 3;
	tInfo.begin = 0.3;
	tInfo.end = 1.0;
	tInfo.ort = -1.0;//���� �����仯
	tInfo.rate0 = -0.0020; //����ʱ�� Ϊ��-����͹�� Ϊ��-���ڰ�
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));	
	lastU = preAmp;
	lastD = -preAmp;
	VInfoIter infoPart = tVoice.vinfo.begin();
	BaseMapIter comIter = BaseSamplesMap.begin();
	while ( infoPart != tVoice.vinfo.end() && comIter!= BaseSamplesMap.end() )
	{
		if ( general_x(comIter->first) >= infoPart->begin && general_x(comIter->first) < infoPart->end) {
			shape(comIter->second, infoPart);
			//if (comIter->second > 0)
			//{
			//	comIter->second = lastU + infoPart->RootRate;
			//	lastU = comIter->second;
			//}
			//else if (comIter->second < 0)
			//{
			//	comIter->second = lastD - infoPart->RootRate;
			//	lastD = comIter->second;
			//}
		}
		else{
			++infoPart;
			--comIter;
		}
		++comIter;
	}

	/******************************************************************/
	//���ݲ���

}

void WaveViewer::MapToVertex()
{
	int count = BaseSamplesMap.size();
	COMvertices = new Vertex[count];

	int index = -1;
	for each (auto var in BaseSamplesMap)
	{
		index += 1;
		COMvertices[index].Position[0] = general_x(var.first);
		COMvertices[index].Position[1] = var.second;
		
	}
}

void WaveViewer::display()
{
	frameDisplay();
	//***************************************************************
	if(Wflag)
		PCMdisplay();
	else
		COMdisplay();

	//Error = checkError();
}

void WaveViewer::PCMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_PCMSamData]);
	glDrawArrays(GL_LINE_STRIP, 0, PCMSamCount);
}

void WaveViewer::COMdisplay()
{
	SamDataShader.use();
	glBindVertexArray(VAOs[VAO_COMSamData]);
	glDrawArrays(GL_LINE_STRIP, 0, BaseSamCount);
}
