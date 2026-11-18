#version 460 core

//接受顶点着色器传来的输入
in vec4 ourColor;

//输出
out vec4 FragColor;

void main()
{
	// 直接使用插值后的颜色
	FragColor = ourColor;
}