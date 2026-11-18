#pragma once
#include<glad/glad.h>
#include<SOIL2/SOIL2.h>
#include<string>
#include<iostream>

class Texture
{
public:
	GLuint id;
	int width;
	int height;

	Texture() : id(0), width(0), height(0)
	{
	}

	~Texture()
	{
		if (id != 0)
		{
			glDeleteTextures(1, &id);
			id = 0;
		}
	}

	// 禁止拷贝
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	bool loadFromFile(const std::string& path)
	{
		id = SOIL_load_OGL_texture
		(
			path.c_str(), 
			SOIL_LOAD_AUTO,		//图片的RGBA通道数
			SOIL_CREATE_NEW_ID,	//生成一个新纹理ID 或 指定一个纹理ID用新图片进行覆盖

			//标志位，用于控制加载和生成纹理时的行为，可从下列中多选
			//SOIL_FLAG_INVERT_Y		垂直翻转图像
			//SOIL_FLAG_MIPMAPS			自动为纹理生成Mipmap
			//SOIL_FLAG_TEXTURE_REPEATS	设置纹理环绕模式为 GL_REPEAT，不指定则默认为 GL_CLAMP_TO_EDGE
			//SOIL_FLAG_MULTIPLY_ALPHA	将RGB值与Alpha值相乘，用于获得正确的透明混合效果
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
		);

		if (id == 0)
		{
			std::cout << "[Texture.h] 加载失败 ： " << path << std::endl;
		}

		//绑定纹理对象
		glBindTexture(GL_TEXTURE_2D, id);

		//设置纹理对象的具体属性
		//设置环绕方式
		glTexParameteri
		(
			GL_TEXTURE_2D,		//要修改的纹理目标类型
			GL_TEXTURE_WRAP_S,	//要设置的属性名称
			GL_REPEAT			//要为当前属性设置的具体值
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//设置过滤方式
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//查询并赋值尺寸信息
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

		return true;
	}

	void bind(GLuint unit = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, id);
	}
};