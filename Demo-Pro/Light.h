#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	glm::vec3 position;		//光源位置
	glm::vec3 color;		//光源颜色
	float strength;			//光照强度

	Light
	(
		glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f),
		float _strength = 1.0f
	)
		: position(_position)
		, color(_color)
		, strength(_strength)
	{
	}

};

class pointLight : public Light
{
public:
};