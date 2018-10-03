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
	cout << checkError() << endl;
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

void WaveViewer::shape(BaseVoiceSamp &samp, VInfoIter info)
{
	//if (samp.value > 0){
	//samp.value = lastU + info->fusion(*info);
	//lastU = samp.value;
		//rootRate += rate0;
	//}
	//else if (samp.value < 0){
	//	samp.value = lastD - info->fusion(*info);
	//	lastD = samp.value;
		//rootRate += rate0;
	//}
}
void WaveViewer::GerneralWave()
{
	//����base��������
	float preAmp = 0.03;
	int diffStep = 5;
	int T_step = 28;
	int PackStep = diffStep + T_step;
	int PairCount = 1920 / PackStep;
	BaseSamCount = PairCount*2;
	COMvertices = new Vertex[BaseSamCount];
	//int curX = 0;
	BaseVoiceSamp t_bvs;

	for (size_t i = 0; i < PairCount; i++)
	{
		//SHRT_MAX
		//curX = i * PackStep;
		t_bvs.index = i * PackStep;
		t_bvs.value = preAmp;
		t_bvs.invertPoint = 0;
		BaseSampMap[t_bvs.index] = t_bvs;
		//������������
		//++i;
		//curX += diffStep;
		//BaseSampMap[curX] = -preAmp;
	}
	/******************************************************************/
	//���μ���   ��������
	//PhonationInfo::RootRate=0.04;
	PhonationInfo tInfo;
	Voice tVoice;

	tInfo.areaID = 1;
	tInfo.begin = -1.0;
	tInfo.end = -0.3;
	tInfo.ort = 1.0; //����
	tInfo.RootRate = 0.008;
	tInfo.Arate0 = 0.03; //����ʱ�� Ϊ��-����͹�� Ϊ��-���ڰ�
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));

	tInfo.areaID = 2;
	tInfo.begin = -0.3;
	tInfo.end = 0.3;
	tInfo.ort = 1.0;//���� �����仯
	tInfo.RootRate = 0.010;
	tInfo.Arate0 = 0.01;
	tVoice.vinfo.push_back(tInfo);

	tInfo.areaID = 3;
	tInfo.begin = 0.3;
	tInfo.end = 1.0;
	tInfo.ort = -1.0;//���� �����仯
	tInfo.RootRate = 0.013;
	tInfo.Arate0 = 0.02; //����ʱ�� Ϊ��-����͹�� Ϊ��-���ڰ�
	tVoice.vinfo.push_back(tInfo);
	//tVoice.info.insert(make_pair(tInfo.areaID, tInfo));	
	lastU = preAmp;
	VInfoIter infoPart = tVoice.vinfo.begin();
	BaseMapIter comIter = BaseSampMap.begin();

	while ( infoPart != tVoice.vinfo.end() && comIter!= BaseSampMap.end() )
	{
		if ( general_x(comIter->first) >= infoPart->begin && general_x(comIter->first) < infoPart->end) {
			
			comIter->second.value = lastU + infoPart->fusion(comIter->second);
			lastU = comIter->second.value;

			//
			//shape(comIter->second, infoPart);
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
	//һ:��ȫ��ת����
	for (auto samp : BaseSampMap)
	{
		t_bvs.index = samp.second.index + diffStep;
		t_bvs.invertPoint = samp.second.invertPoint;
		t_bvs.value = t_bvs.invertPoint - samp.second.value;

		BaseSampMap2[samp.second.index] = samp.second;
		BaseSampMap2[t_bvs.index] = t_bvs;
	}
}

void WaveViewer::MapToVertex()
{
	int count = BaseSampMap2.size();
	COMvertices = new Vertex[count];

	int index = -1;
	for each (auto var in BaseSampMap2)
	{
		index += 1;
		COMvertices[index].Position[0] = general_x(var.second.index);
		cout << COMvertices[index].Position[0] << endl;
		COMvertices[index].Position[1] = var.second.value;
		
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
