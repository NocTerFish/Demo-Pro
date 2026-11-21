#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "Material.h"
#include "Texture.h"

//基础纯色材质
class BasicMaterial : public Material
{
public:
	glm::vec4 color;

	BasicMaterial() : color(1.0f, 1.0f, 1.0f, 1.0f)
	{ 
	}

	void bind(const RenderContext& ctx) override
	{
		if (!shader)
			return;

		shader->use();
		shader->setVec4("baseColor", color);
	}
};

//顶点携带颜色的材质
class VertexColorMaterial : public Material
{
public:
	void bind(const RenderContext& ctx) override
	{
		if (!shader)
			return;

		shader->use();
	}
};

//双纹理混合材质
class TextureMaterial : public Material
{
public:
	std::shared_ptr<Texture> tex1;
	std::shared_ptr<Texture> tex2;
	float mixRate;		//贴图混合比率

	//默认构造函数
	TextureMaterial() : mixRate(0.2f)
	{
	}

	void bind(const RenderContext &ctx) override
	{
		if (!shader)
			return;

		shader->use();

		if (tex1)
		{
			tex1->bind(0);
			shader->setInt("tex1", 0);
		}

		if (tex2)
		{
			tex2->bind(1);
			shader->setInt("tex2", 1);
		}

		shader->setFloat("mixRate", mixRate);
	}
};

//光照材质
class PhongMaterial : public Material
{
public:
	static const int MAX_LIGHTS = 7;	//光源上限

	std::shared_ptr<Texture> tex;		//纹理贴图
	glm::vec3 ambient;	//环境光颜色
	glm::vec3 diffuse;	//漫反射颜色
	glm::vec3 specular;	//镜面反射颜色
	float shininess;	//高光指数

	//默认构造函数
	PhongMaterial()
		: ambient(0.3f, 0.3f, 0.3f)
		, diffuse(1.0f, 1.0f, 1.0f)
		, specular(1.0f, 1.0f, 1.0f)
		, shininess(32.0f)
	{
	}

	void bind(const RenderContext& ctx)
	{
		if (!shader)
			return;

		shader->use();

		shader->setVec3("material.ambient", ambient);
		shader->setVec3("material.diffuse", diffuse);
		shader->setVec3("material.specular", specular);
		shader->setFloat("material.shininess", shininess);

		shader->setVec3("viewPos", ctx.cameraPos);

		int lightCount = (int)ctx.lights.size();
		if (lightCount > MAX_LIGHTS)
		{
			lightCount = MAX_LIGHTS;
		}

		shader->setInt("lightCount", lightCount);

		for (int i = 0; i < lightCount; i++)
		{
			const std::shared_ptr<Light> L = ctx.lights[i];

			std::string prefix = "lights[" + std::to_string(i) + "].";

			shader->setInt(prefix + "type", L->type);
			shader->setVec3(prefix + "position", L->transform.position);
			shader->setVec3(prefix + "color", L->color);
			shader->setFloat(prefix + "strength", L->strength);
			shader->setVec3(prefix + "dir", L->getDir());
			shader->setFloat(prefix + "cutOff", L->cutOff);
			shader->setFloat(prefix + "cutOffRatio", L->cutOffRatio);
			shader->setFloat(prefix + "quadratic", L->quadratic);
			shader->setFloat(prefix + "linear", L->linear);
			shader->setFloat(prefix + "constant", L->constant);
		}
	}
};

//光照材质纹理
class texPhongMaterial : public Material
{
public:
	static const int MAX_LIGHTS = 7;	//光源上限

	std::shared_ptr<Texture> tex;	//纹理材质
	glm::vec3 ambient;	//环境光颜色
	glm::vec3 diffuse;	//漫反射颜色
	glm::vec3 specular;	//镜面反射颜色
	float shininess;	//高光指数

	//默认构造函数
	texPhongMaterial()
		: ambient(0.3f, 0.3f, 0.3f)
		, diffuse(1.0f, 1.0f, 1.0f)
		, specular(1.0f, 1.0f, 1.0f)
		, shininess(32.0f)
	{
	}

	void bind(const RenderContext& ctx)
	{
		if (!shader)
			return;

		shader->use();


		if (tex)
		{
			tex->bind(0);
			shader->setInt("tex", 0);
		}

		shader->setVec3("material.ambient", ambient);
		shader->setVec3("material.diffuse", diffuse);
		shader->setVec3("material.specular", specular);
		shader->setFloat("material.shininess", shininess);

		shader->setVec3("viewPos", ctx.cameraPos);

		int lightCount = (int)ctx.lights.size();
		if (lightCount > MAX_LIGHTS)
		{
			lightCount = MAX_LIGHTS;
		}

		shader->setInt("lightCount", lightCount);

		for (int i = 0; i < lightCount; i++)
		{
			const std::shared_ptr<Light> L = ctx.lights[i];

			std::string prefix = "lights[" + std::to_string(i) + "].";

			shader->setInt(prefix + "type", L->type);
			shader->setVec3(prefix + "position", L->transform.position);
			shader->setVec3(prefix + "color", L->color);
			shader->setFloat(prefix + "strength", L->strength);
			shader->setVec3(prefix + "dir", L->getDir());
			shader->setFloat(prefix + "cutOff", L->cutOff);
			shader->setFloat(prefix + "cutOffRatio", L->cutOffRatio);
			shader->setFloat(prefix + "quadratic", L->quadratic);
			shader->setFloat(prefix + "linear", L->linear);
			shader->setFloat(prefix + "constant", L->constant);
		}
	}
};