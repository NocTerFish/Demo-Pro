#pragma once
#include <glm/glm.hpp>

class Object;

class Component
{
public:
	virtual ~Component() {}

	//挂载时调用
	virtual void onAttach(Object& owner) {}

	//每帧更新
	virtual void update(Object& owner, float dt) = 0;

	//卸载时调用
	virtual void onDetach(Object& owner) {}
};