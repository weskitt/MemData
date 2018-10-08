#include "stdafx.h"
#include "WaveViewer.h"


bool WaveViewer::Init(char * file)
{
	GLInit();
	//X轴框架
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
		/* 在这里做渲染 */
		//int width, height;
		//glfwGetFramebufferSize(window, &width, &height);
		//glViewport(0, 0, width, height);
		//glClear(GL_COLOR_BUFFER_BIT);
		display();
		/* 交换缓冲区，即在window上更新内容 */
		glfwSwapBuffers(window);

		/* 轮询事件 */
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
	//创建base基本数据
	float preAmp = 0.00000001;
	int diffStep = 1;
	int T_step = 28;
	int PackStep = diffStep + T_step;
	int PairCount = 1920 / PackStep;
	BaseSamCount = PairCount*2;
	COMvertices = new Vertex[BaseSamCount];
	//int curX = 0;
	BaseVoiceSamp t_bvs;

	for (size_t i = 0; i < PairCount; i++)
	{
		t_bvs.index = i * PackStep;
		t_bvs.value = preAmp;
		t_bvs.invertPoint = 0;
		BaseSampMap[t_bvs.index] = t_bvs;
	}


	/******************************************************************/
	//塑形计算   数据修饰
	PhonationInfo tInfo;
	Voice tVoice;

	tInfo.areaID = 1;
	tInfo.preVoice = true;
	tInfo.InitlastU = true;
	tInfo.Initbegin = false;

	tInfo.startAmp = 0.03;
	tInfo.begin = -1.0;
	tInfo.end = -0.8;
	tVoice.vinfo.push_back(tInfo);

	tInfo.areaID = 2;
	tInfo.preVoice = false;
	tInfo.InitlastU = false;
	tInfo.Initbegin = true;
	tInfo.beginData = 0.5;

	tInfo.begin = -0.8;
	tInfo.end = 0.3;
	tInfo.ort = -0.001;//0不变，-1收缩，1膨胀
	tInfo.RootRate = 8;
	tInfo.Arate0 = 3;
	tInfo.Arate1 = -0.08;
	tVoice.vinfo.push_back(tInfo);

	tInfo.areaID = 3;
	tInfo.preVoice = false;
	tInfo.InitlastU = false;
	tInfo.Initbegin = false;
	tInfo.begin = 0.03;
	tInfo.end = 1.0;
	tInfo.ort = 0.001;//0不变，-1收缩，1膨胀
	tInfo.RootRate = 8;
	tInfo.Arate0 = 3	; //收缩时， 为负-则外凸， 为正-则内凹
	tInfo.Arate1 = -0.08;
	tVoice.vinfo.push_back(tInfo);

	lastU = preAmp;
	VInfoIter infoPart = tVoice.vinfo.begin();
	BaseMapIter comIter = BaseSampMap.begin();

	while ( infoPart != tVoice.vinfo.end() && comIter!= BaseSampMap.end() )
	{
		if ( general_x(comIter->first) >= infoPart->begin && general_x(comIter->first) < infoPart->end) {
			infoPart->fusion(comIter->second, lastU);
		}
		else{
			++infoPart;
			--comIter;
		}
		++comIter;
	}


	/******************************************************************/
	//数据补完
	//一:补全逆转数据
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
