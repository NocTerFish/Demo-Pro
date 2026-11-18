#pragma once
#include "Component.h"
#include "Object.h"
#include <glm/glm.hpp>
#include <cmath>

//圆周运动组件
class OrbitComponent : public Component
{
public:
	glm::vec3 direction;	//初始运动方向（只取方向，长度无所谓）
	glm::vec3 center;		//圆心
	float speed;			//角速度（弧度/秒，正负决定转向）

	//onAttach里算出来的状态
	float     radius;		//半径
	float     angle;		//当前角度（0 = 起始位置）
	glm::vec3 radialDir;	//圆心 → 物体（单位向量）
	glm::vec3 tangentDir;	//运动方向在切线平面内的归一化投影
	glm::vec3 lastTargetPos;//上一帧算出的目标位置（用于算增量）

	OrbitComponent(glm::vec3 _direction = glm::vec3(1.0f), float _speed = 30.0f, glm::vec3 _center = glm::vec3(0.0f))
		: direction(_direction)
		, speed(_speed)
		, center(_center)
		, radius(0.0f)
		, radialDir(0.0f)
		, tangentDir(0.0f)
		, angle(0.0f)
		, lastTargetPos(0.0f)
	{
	}

	//挂载时：从物体初始位置和运动方向推导整个圆周
	void onAttach(Object& owner) override;

	// ── 每帧更新 ──
	void update(Object& owner, float dt) override;
};


//自转组件
class SpinComponent : public Component
{
public:
	glm::vec3 axis;	//旋转轴
	float speed;	//角速度

	SpinComponent(glm::vec3 _axis = glm::vec3(0.0f, 1.0f, 0.0f), float _speed = 30.0f)
		: axis(glm::normalize(_axis))
		, speed(_speed)
	{
	}

	void update(Object& owner, float dt) override;
};