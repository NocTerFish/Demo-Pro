#version 460 core

//输入
layout (location = 0) in vec3 aPos;		// 位置
layout (location = 1) in vec4 aColor;	// 颜色

//输出到片段着色器
out vec4 ourColor;

//变换矩阵
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);

	//顶点颜色传给片段着色器
	//GPU会在三角形内部插值
	ourColor = aColor;
}