#pragma once
#include<memory>
#include<glm/glm.hpp>
#include<iostream>
#include<map>
#include<string>
#include"Transform.h"
#include"Component.h"

class Object
{
public:
	Transform transform;	//变换信息
	std::map<std::string, std::shared_ptr<Component>> componentMap;	//组件列表

	Object()
	{	
	}

	virtual ~Object()
	{	
	}

	//添加组件
	void addComponent(const std::string& name, std::shared_ptr<Component> _component)
	{
		if (componentMap.find(name) != componentMap.end())
		{
			std::cout << "[Object.h] 名字重复，已覆盖组件: " << name << std::endl;
		}

		_component->onAttach(*this);	//挂载时调用的初始化组件函数
		componentMap[name] = _component;
	}

	//取用组件
	template <typename T>
	std::shared_ptr<T> getComponentAs(const std::string& name)
	{
		auto it = componentMap.find(name);
		if (it == componentMap.end())
		{
			std::cout << "[Object.h] 未找到组件" << name << std::endl;
			return nullptr;
		}

		auto typed = std::dynamic_pointer_cast<T>(it->second);
		if (!typed)
		{
			std::cout << "[Object.h] 取组件的类型" << typeid(T).name() << "不匹配" << std::endl;
		}
		return typed;
	}

	//删除组件
	void removeComponent(const std::string& name)
	{
		auto it = componentMap.find(name);
		if (it == componentMap.end())
		{
			std::cout << "[Object.h] 未找到要删除的组件: " << name << std::endl;
			return;
		}

		it->second->onDetach(*this);	//调用组件的卸载时函数
		componentMap.erase(it);
	}

	//帧更新
	virtual void updata(float dt)
	{
		for (auto& pair : componentMap)
		{
			pair.second->update(*this, dt);
		}
	}

	//接受外部传入的变换信息
	void setTransform(Transform _transform)
	{
		transform = _transform;
	}

};
