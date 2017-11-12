#pragma once
class UNIT  //可意识到的感觉(单一类型) 记忆基本单元 memory
{
	//vector<void *> frag; //各种类型的外部数据
	vector<int>  senseFrag; //感觉片段  memory
	int		  id; //该类型数据来源
	int       type; //数据类型
	int       rank; //等级 A_RANK B_RANK ... 片段的存在等级，等级越高，存在时间越长，A_RANK不可被覆盖遗忘的存在，Z_RANK临时的存在
	int       value;//该等级的值,亮度，显示度，用于回忆反馈

public:

	void self_Update();

	UNIT();
	~UNIT();
};

