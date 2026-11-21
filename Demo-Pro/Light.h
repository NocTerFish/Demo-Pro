#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Light : public Object
{
public:
	int type;				//光源类型
	glm::vec3 color;		//光源颜色
	float strength;			//光照强度

	float cutOff;			//切光角度
	float cutOffRatio;		//内切光角度 / 外切光角度 的比率

	//衰减计算
	float quadratic;		//二次项系数
	float linear;			//一次项系数
	float constant;			//常数

	Light
	(
		Transform _transform,
		glm::vec3 _color,
		float _strength,
		float _cutOff, 
		float _cutOffRatio,
		float _quadratic,
		float _linear,
		float _constant
	)
	{
		transform = _transform;
		color = _color;
		strength = _strength;
		cutOff = _cutOff;
		cutOffRatio = _cutOffRatio;
		quadratic = _quadratic;
		linear = _linear;
		constant = _constant;
	}

	glm::vec3 getDir()
	{
		glm::vec3 r = glm::radians(transform.rotation);
		float cx = cos(r.x);
		float sx = sin(r.x);
		float cy = cos(r.y);
		float sy = sin(r.y);
		
		return glm::normalize(glm::vec3(sy, -sx * cy, cx * cy));
	}

	//更新函数
	virtual void updata(float dt) override
	{
		Object::updata(dt);
	}
};