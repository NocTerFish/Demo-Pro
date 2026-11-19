#pragma once
#include "Texture.h"
#include <map>
#include <memory>
#include <string>
#include <iostream>

//全局单例的纹理池
class TexturePool
{
public:

	std::map<std::string, std::shared_ptr<Texture>> textures;

	//构造函数
	TexturePool()
	{
	}

	//拷贝构造函数
	TexturePool(const TexturePool&);

	//拷贝赋值函数
	TexturePool& operator= (const TexturePool&);

	static TexturePool* getInstance()
	{
		static TexturePool instance;
		return &instance;
	}

	//加载纹理
	void loadTex(const std::string& name, const std::string& path)
	{
		if (textures.find(name) != textures.end())
		{
			std::cout << "[TexturePool.h] 纹理重名，已覆盖" << name << std::endl;
		}

		std::shared_ptr<Texture> tex = std::make_shared<Texture>();
		if (tex->loadFromFile(path))
		{
			textures[name] = tex;
		}
	}

	//按名字获取
	std::shared_ptr<Texture> getTex(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Texture>>::iterator it = textures.find(name);
		if (it != textures.end())
			return it->second;

		std::cout << "[TexturePool.h] 未找到: " << name << std::endl;
		return nullptr;
	}
};