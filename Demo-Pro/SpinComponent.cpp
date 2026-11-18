#include "ComponentBuilder.h"

void SpinComponent::update(Object& owner, float dt)
{
	//旋转天生就是增量
	owner.transform.rotation += axis * speed * dt;
}
