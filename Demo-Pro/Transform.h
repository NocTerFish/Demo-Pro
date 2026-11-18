#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	glm::vec3 position;	//位置
	glm::vec3 rotation;	//旋转
	glm::vec3 scale;	//缩放

	//默认构造函数
	Transform
	(
		glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), 
		glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f)
	) 
		: position(_position)
		, rotation(_rotation)
		, scale(_scale)
	{
	}

	glm::mat4 GetMatrix() const
	{
		glm::mat4 m(1.0f);
		//平移
		m = glm::translate(m, position);

		//旋转
		m = glm::rotate(m, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m = glm::rotate(m, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m = glm::rotate(m, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		//缩放
		m = glm::scale(m, scale);

		return m;
	}
};