#version 450 core

layout( location = 0 ) in vec3 vPos;

out vec4 vertColor;  // 为片段着色器指定一个颜色输出

uniform mat4 trans;
//uniform float t;

void main()
{
    gl_Position = trans * vec4(vPos, 1.0f);
    vertColor= vec4(0.0, 0.5, 0.0, 0.0);
}
