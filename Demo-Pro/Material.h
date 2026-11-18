#pragma once
#include"Shader.h"
#include"RenderContext.h"

class Material
{
public:
	Shader* shader;	//Material类不拥有着色器成员，但需要着色器的指针进行调用

	Material() : shader(nullptr)
	{
	}

	virtual ~Material()
	{
	}



	//纯虚的绑定材质函数
	virtual void bind(const RenderContext& ctx) = 0;
};