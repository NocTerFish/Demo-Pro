#include "ComponentBuilder.h"
#include <iostream>

const float PI = 3.14159265358979323846f;

//圆周运动组件
//挂载时，从物体初始位置和运动方向推导整个圆周运动所在平面
void OrbitComponent::onAttach(Object& owner)
{
	//计算半径方向
	glm::vec3 offset = owner.transform.position - center;
	radius = glm::length(offset);

	if (radius < 1e-5f)
	{
		std::cout << "[OrbitComponent.h] 物体与圆心重合，无法确定轨道" << std::endl;
		return;
	}

	//半径向量的归一化
	radialDir = glm::normalize(offset);

	//把运动方向投影到切线平面
	glm::vec3 v = direction - glm::dot(direction, radialDir) * radialDir;

	if (glm::length(v) < 1e-5f)
	{
		std::cout << "[OrbitComponent.h] 运动方向与半径平行，无法确定圆周" << std::endl;
		return;
	}

	//目标方向
	tangentDir = glm::normalize(v);

	//起始角度为0
	angle = 0.0f;

	//初始化起点
	lastTargetPos = owner.transform.position;
}

// ── 每帧更新 ──
void OrbitComponent::update(Object& owner, float dt)
{
	//推进角度
	angle += glm::radians(speed) * dt;
	if (angle > 2 * PI)
	{
		angle -= 2 * PI;
	}

	//圆上的目标位置
	//(radialDir, tangentDir) 就是平面内的一组正交基
	glm::vec3 targetPos = center + radius * (std::cos(angle) * radialDir + std::sin(angle) * tangentDir);

	//增量 = 目标位置 - 上一帧目标位置
	glm::vec3 delta = targetPos - lastTargetPos;

	owner.transform.position += delta;
	lastTargetPos = targetPos;
}