#pragma once
#include<glm/glm.hpp>
#include<vector>
#include"Light.h"

struct RenderContext
{
	glm::mat4 view;				//视图矩阵
	glm::mat4 projection;		//投影矩阵
	glm::vec3 cameraPos;		//相机位置
	std::vector<std::shared_ptr<Light>> lights;	//光源列表
	float time;					//动画用时

	//默认构造函数
	RenderContext() : view(1.0f), projection(1.0f), cameraPos(0.0f), time(0.0f) 
	{
	}
};