#version 450 core

layout( location = 0 ) in vec4 vPosition;

out vec4 vertColor;  // 为片段着色器指定一个颜色输出

void
main()
{
    gl_Position = vPosition;
    vertColor= vec4(0.0, 0.5, 0.0, 0.5);
}
