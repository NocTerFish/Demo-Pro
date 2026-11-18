#pragma once
#include<glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;		//位置
	glm::vec4 color;	//颜色
	glm::vec2 tex;		//UV纹理坐标
	glm::vec3 normal;	//法线

	//默认构造函数
	Vertex():
		pos(0.0f, 0.0f, 0.0f),
		color(1.0f, 1.0f, 1.0f, 1.0f),
		tex(0.0f, 0.0f),
		normal(0.0f, 0.0f, 1.0f)
	{	}

	//含位置、颜色的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec4& _color) 
		: pos(_pos), color(_color), tex(0.0f, 0.0f), normal(0.0f, 0.0f, 1.0f)
	{	}

	//含位置、纹理的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec2& _tex)
		: pos(_pos), color(1.0f, 1.0f, 1.0f, 1.0f), tex(_tex), normal(0.0f, 0.0f, 1.0f)
	{	}

	//含位置、法线的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec3& _normal)
		: pos(_pos), color(1.0f, 1.0f, 1.0f, 1.0f), tex(0.0f, 0.0f), normal(_normal)
	{
	}

	//含位置、颜色、纹理的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec4& _color, const glm::vec2& _tex)
		: pos(_pos), color(_color), tex(_tex), normal(0.0f, 0.0f, 1.0f)
	{
	}

	//含位置、纹理、法线的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec2& _tex, const glm::vec3& _normal)
		: pos(_pos), color(1.0f, 1.0f, 1.0f, 1.0f), tex(_tex), normal(_normal)
	{
	}

	//含位置、颜色、法线的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec4& _color, const glm::vec3& _normal)
		: pos(_pos), color(_color), tex(0.0f, 0.0f), normal(_normal)
	{
	}

	//全部参数的构造函数
	Vertex(const glm::vec3& _pos, const glm::vec4& _color, const glm::vec2& _tex, const glm::vec3& _normal)
		: pos(_pos), color(_color), tex(_tex), normal(_normal)
	{	}
};