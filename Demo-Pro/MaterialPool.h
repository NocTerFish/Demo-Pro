#pragma once
#include "materials.h"
#include <map>
#include <memory>
#include <string>

//全局单例的材质池
class MaterialPool
{
public:
	std::map<std::string, std::shared_ptr<Material>> materialPool;

	//构造函数
	MaterialPool()
	{
	}

	//拷贝构造函数
	MaterialPool(const MaterialPool&);

	//拷贝赋值函数
	MaterialPool& operator= (const MaterialPool&);

	static MaterialPool* getInstance()
	{
		static MaterialPool instance;
		return &instance;
	}

	//加载材质
	void loadMat(const std::string& name, const std::shared_ptr<Material> mat)
	{
		if (materialPool.find(name) != materialPool.end())
		{
			std::cout << "[MaterialPool.h] 材质重名，已覆盖" << name << std::endl;
		}

		materialPool[name] = mat;
	}

	//直接获取材质
	std::shared_ptr<Material> getMat(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Material>>::iterator it = materialPool.find(name);
		if (it != materialPool.end())
			return it->second;

		std::cout << "[MaterialPool.h] 未找到: " << name << std::endl;
		return nullptr;
	}

	//转换成具体类型材质获取
	template <typename T>
	std::shared_ptr<T> getMatAs(const std::string& name)
	{
		std::shared_ptr<Material> mat = getMat(name);
		if (mat == nullptr)
			return;

		auto typed = std::dynamic_pointer_cast<T>(mat);
		if (!typed)
		{
			std::cout << "[MaterialPool.h] 取材质的类型" << typeid(T).name() << "不匹配" << std::endl;
		}
		return typed;
	}
};