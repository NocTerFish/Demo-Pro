#pragma once
#include<memory>
#include<glm/glm.hpp>
#include<iostream>
#include<map>
#include<string>
#include"Mesh.h"
#include"Material.h"
#include"Transform.h"
#include"RenderContext.h"
#include"Component.h"

class Object
{
public:
	Transform transform;				//变换信息
	std::shared_ptr<Mesh> mesh;			//网格数据
	std::shared_ptr<Material> material;	//材质成员，里面包含着色器的指针进行引用
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

	//接受外部传入的顶点信息构建Mesh
	void inComeMesh(const std::vector<Vertex>& verts, const std::vector<GLushort>& indices = std::vector<GLushort>())
	{
		mesh = std::make_shared<Mesh>();
		mesh->setup(verts, indices);
	}

	//接受外部传入的变换信息
	void setTransform(Transform _transform)
	{
		transform = _transform;
	}

	//设置网格
	virtual void setMesh()
	{
	}

	//接受外部传入的材质
	void setMaterial(std::shared_ptr<Material> _material)
	{
		material = _material;
	}
	//转换成具体类型的材质函数
	template <typename T>
	std::shared_ptr<T> getMaterialAs()
	{
		auto typed = std::dynamic_pointer_cast<T>(material);
		if (!typed)
		{
			std::cout << "[Object.h] 取材质的类型" << typeid(T).name() << "不匹配" << std::endl;
		}
		return typed;
	}

	//渲染流程
	void draw(const RenderContext& ctx)
	{
		//防御性编程
		if (!mesh || !material || !material->shader)
		{
			std::cout << "[Object.h] mesh或material或material的shader成员为空" << std::endl;
			return;
		}
		
		//激活着色器
		material->bind(ctx);
		

		//设置矩阵
		material->shader->setMat4("model", transform.GetMatrix());
		material->shader->setMat4("view", ctx.view);
		material->shader->setMat4("projection", ctx.projection);

		//调用子类的绘制函数
		drawSelf(ctx);
	}

	//子类多态的绘制函数
	virtual void drawSelf(const RenderContext& ctx)
	{
		mesh->draw();
	}
};

class LineObject : public Object
{
public:
	float lineWidth;	//线宽

	LineObject() : lineWidth(1.0f) 
	{
	}

	~LineObject() 
	{
	}

	void drawSelf(const RenderContext& ctx) override
	{
		if (!mesh) return;

		glLineWidth(lineWidth);        //设置线宽
		mesh->draw(GL_LINES);          //用线图元
		glLineWidth(1.0f);             //恢复
	}
};