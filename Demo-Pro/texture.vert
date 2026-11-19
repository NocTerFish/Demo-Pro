#version 460 core

layout (location = 0) in vec3 aPos;			// 位置
layout (location = 1) in vec4 aColor;		// 颜色（现在不用）
layout (location = 2) in vec2 aTexCoord;	// 纹理坐标

out vec4 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	ourColor = aColor;

	TexCoord = aTexCoord;

	gl_Position = projection * view * model * vec4(aPos, 1.0);
}