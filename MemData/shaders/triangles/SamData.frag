#version 450 core

layout( location = 0 ) out vec4 fColor;

in vec4 vertColor;  // 从顶点着色器传来的输入变量（名称相同、类型相同）

void main()
{
    fColor = vertColor;
}
