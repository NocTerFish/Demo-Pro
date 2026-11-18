#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include <string>
#include "RenderContext.h"
#include "RenderState.h"
#include "Camera.h"
#include "Light.h"
#include "Object.h"

class Scene
{
public:
	std::map<std::string, std::shared_ptr<Object>> objectsMap;
	Camera camera;					//摄像机
	RenderState renderState;		//渲染状态
	std::vector<Light> lights;		//光源数组
	float totalTime;				//累计时间

	glm::vec4 clearColor;			//清屏颜色

	Scene() : totalTime(0), clearColor(0.1f, 0.1f, 0.1f, 1.0f)
	{
		setRenderState();
	}

	~Scene()
	{
	}

	//初始化场景
	virtual void init() {};

	//增加对象
	void addObject(const std::string& name, std::shared_ptr<Object> obj)
	{
		if (objectsMap.find(name) != objectsMap.end())
		{
			std::cout << "[Scene.h] 名字重复，已覆盖: " << name << std::endl;
		}
		objectsMap[name] = obj;
	}

	//取对象
	std::shared_ptr<Object> getObject(const std::string& name)
	{
		auto it = objectsMap.find(name);
		if (it == objectsMap.end())
		{
			std::cout << "[Scene.h] 未找到对象" << name << std::endl;
			return nullptr;
		}
		return it->second;
	}
	//转换成具体类型的取对象函数
	template <typename T>
	std::shared_ptr<T> getObjectAs(const std::string& name)
	{
		auto obj = getObject(name);
		if (!obj) 
			return nullptr;

		auto typed = std::dynamic_pointer_cast<T>(obj);
		if (!typed)
		{
			std::cout << "[Scene.h] 对象 " << name << " 类型不匹配" << std::endl;
		}
		return typed;
	}

	//增加光源
	void addLight(const Light& light)
	{
		lights.push_back(light);
	}

	//构建上下文
	RenderContext buildContext() const
	{
		RenderContext ctx;
		ctx.view = camera.getViewMatrix();
		ctx.projection = camera.getProjectionMatrix();
		ctx.cameraPos = camera.cg.position;
		ctx.lights = lights;
		ctx.time = totalTime;
		return ctx;
	}

	//自定义修改渲染状态
	void setRenderState(RenderState _renderState = RenderState::Default3D())
	{
		renderState = _renderState;
	}

	//场景帧更新函数
	virtual void updata(float dt)
	{
		totalTime += dt;
		for (auto& obj : objectsMap)
		{
			obj.second->updata(dt);
		}
	}

	//渲染函数
	void render()
	{
		//清屏
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//应用渲染状态
		renderState.apply();

		//构建上下文
		RenderContext ctx = buildContext();

		//遍历调用所有对象的绘制函数
		for (auto& obj : objectsMap)
		{
			obj.second->draw(ctx);
		}
	}

};