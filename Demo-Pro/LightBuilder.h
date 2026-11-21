#pragma once
#include "Light.h"

//方向光
class DirLight : public Light
{
public:
	DirLight
	(
		Transform _transform = Transform(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)),	//变换
		glm::vec3 _color = glm::vec3(1.0f),				//光照颜色
		float _strength = 1.0f							//光照强度
	)
		:Light(_transform, _color, _strength, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
	{
		type = 0;
	}

	~DirLight()
	{
	}

	virtual void updata(float dt) override;
};

//点光源
class PointLight : public Light
{
public:
	PointLight
	(
		Transform _transform = Transform(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)),	//变换
		glm::vec3 _color = glm::vec3(1.0f),		//光照颜色
		float _strength = 1.0f,		//光照强度
		float _quadratic = 0.032f,	//二次项系数
		float _linear = 0.09f,		//一次项系数
		float _constant = 1.0f		//常数项
	) 
		: Light(_transform, _color, _strength, 0.0f, 0.0f, _quadratic, _linear, _constant)
	{
		type = 1;
	}

	~PointLight()
	{
	}

	virtual void updata(float dt) override;
};

//聚光灯
class SpotLight : public Light
{
public:
	SpotLight
	(
		Transform _transform = Transform(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f)),
		glm::vec3 _color = glm::vec3(1.0f),
		float _strength = 1.0f,
		float _cutOff = 60.0f,		//切光角角度
		float _cutOffRatio = 0.5f,	//外切光角 / 内切光角 的角度比例
		float _quadratic = 0.032f,	//二次项系数
		float _linear = 0.09f,		//一次项系数
		float _constant = 1.0f		//常数项

	)
		: Light(_transform, _color, _strength, _cutOff, _cutOffRatio, _quadratic, _linear, _constant)
	{
		type = 2;
	}

	~SpotLight()
	{
	}

	virtual void updata(float dt) override;
};