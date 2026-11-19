#pragma once
#include "Shader.h"
#include <map>
#include <string>
#include <iostream>

class ShaderLibrary
{
public:
	std::map<std::string, Shader*> shaders;	//注册表，名字和着色器指针相对应的键值对

	ShaderLibrary& operator=(const ShaderLibrary&);
	ShaderLibrary(const ShaderLibrary&);

	ShaderLibrary() 
	{
	}

	~ShaderLibrary()
	{
		for (std::map<std::string, Shader*>::iterator it = shaders.begin(); it != shaders.end(); ++it)
		{
			delete it->second;
		}
		shaders.clear();
	}

	static ShaderLibrary* getInstance()
	{
		static ShaderLibrary instance;
		return &instance;
	}

	//从源码注册
	void add(const std::string& name, const char* vs, const char* fs)
	{
		//如果注册表中已经存在该name
		if (shaders.find(name) != shaders.end())
			return;		

		Shader* shader = new Shader(vs, fs);

		if (shader->id != 0)
			shaders[name] = shader;
		else
			delete shader;
	}

	//从文件注册
	void addFromFile(const std::string& name, const std::string& vertPath, const std::string& fragPath)
	{
		if (shaders.find(name) != shaders.end())
			return;

		Shader* shader = new Shader();
		if (shader->loadFromFile(vertPath, fragPath))
			shaders[name] = shader;
		else
			delete shader;
	}

	//取用指定名字的着色器
	Shader* get(const std::string& name)
	{
		std::map<std::string, Shader*>::iterator it = shaders.find(name);
		if (it != shaders.end())
			return it->second;

		std::cout << "[ShaderLibrary.h] 未找到: " << name << std::endl;
		return nullptr;
	}
};