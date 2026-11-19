#pragma once
#include "Object.h"
#include <glm/glm.hpp>

class Light : public Object
{
public:
	glm::vec3 color;		//光源颜色
	float strength;			//光照强度

	Light
	(
		Transform _transform = Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)),
		glm::vec3 _color = glm::vec3(1.0f),
		float _strength = 1.0f
	)
	{
		transform = _transform;
		color = _color;
		strength = _strength;
	}

	//更新函数
	virtual void updata(float dt) override
	{
		Object::updata(dt);
	}
};