#pragma once
#include "Object.h"
#include"Mesh.h"
#include"Material.h"
#include"RenderContext.h"

class Model : public Object
{
public:
	std::shared_ptr<Mesh> mesh;			//网格数据
	std::shared_ptr<Material> material;	//材质成员，里面包含着色器的指针进行引用

	//接受外部传入的顶点信息构建Mesh
	void inComeMesh(const std::vector<Vertex>& verts, const std::vector<GLushort>& indices = std::vector<GLushort>())
	{
		mesh = std::make_shared<Mesh>();
		mesh->setup(verts, indices);
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

	//更新函数
	virtual void updata(float dt) override
	{
		Object::updata(dt);
	}

};

class Line : public Model
{
public:
	float lineWidth;	//线宽

	Line() : lineWidth(1.0f)
	{
	}

	~Line()
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