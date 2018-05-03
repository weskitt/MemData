#version 450 core

layout ( location = 0 ) in vec2 vPos;
layout ( location = 1 ) in vec2 vOffset;
layout ( location = 2 ) in mat4 vScale;
//特别注意。这里设置的mat4类型的输入变量，location为2，
//可是一个mat4类型会占领连续的4个位置
//因此vScale占领了2,3,4,5四个索引位置。
out vec4 vertColor;  // 为片段着色器指定一个颜色输出

//uniform mat4 trans;
//uniform float t;

void main()
{
    //gl_Position = trans * vec4(vPos + vOffset, 0.0f, 1.0f);
	//vPos.y=0.5f;
    gl_Position =vScale * vec4(vPos + vOffset, 0.0f, 1.0f);
	//gl_Position = vec4(vPos + vOffset, 0.0f, 1.0f);
    vertColor= vec4(0.0, 0.5, 0.0, 0.0);
}
