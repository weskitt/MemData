#pragma once
class FRAGMENT
{
	vector<void *> frag; //�������͵��ⲿ����
	int       type; //��������
	int       rank; //�ȼ� A_RANK B_RANK ... Ƭ�εĴ��ڵȼ����ȼ�Խ�ߣ�����ʱ��Խ����A_RANK���ɱ����������Ĵ��ڣ�Z_RANK��ʱ�Ĵ���
	int       value;//�õȼ���ֵ,���ȣ���ʾ�ȣ����ڻ��䷴��

public:

	void self_Update();

	FRAGMENT();
	~FRAGMENT();
};

