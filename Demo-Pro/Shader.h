#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint id;	//着色器程序对象的ID

	//默认构造函数
	Shader() : id(0)
	{	}

	//使用源码字符串的构造函数
	Shader(const char* vertexSource, const char* fragmentSource) : id(0)
	{
		compile(vertexSource, fragmentSource);

	}

	~Shader()
	{
		if (id != 0)
		{
			glDeleteProgram(id);
			id = 0;
		}
	}

	//禁止拷贝
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	//从文件加载
	bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vsSrc = readFile(vertexPath);
		std::string fsSrc = readFile(fragmentPath);

		if (vsSrc.empty() || fsSrc.empty())
			return false;

		return compile(vsSrc.c_str(), fsSrc.c_str());
	}

	void use()
	{
		glUseProgram(id);
	}

	//uniform相关函数
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void setVec3(const std::string& name, const glm::vec3& v) const
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(v));
	}

	void setVec4(const std::string& name, const glm::vec4& v) const
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(v));
	}

	void setMat4(const std::string& name, const glm::mat4& m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
	}

	//读文件
	static std::string readFile(const std::string& path)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			std::cout << "[Shader.h] 无法打开文件" << path << std::endl;
			return "";
		}

		std::stringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	//编译和链接
	bool compile(const char* vertexSource, const char* fragmentSource)
	{
		//创建着色器对象
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		//编译顶点着色器
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);

		//检查顶点着色器
		if(!checkCompile(vertex, "VERTEX"))
		{ 
			glDeleteShader(vertex);
			return false;
		}

		//编译片段着色器
		glShaderSource(fragment, 1, &fragmentSource, nullptr);
		glCompileShader(fragment);

		//检查片段着色器
		if (!checkCompile(fragment, "FRAGMENT"))
		{
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return false;
		}

		//创建着色器程序
		id = glCreateProgram();
		glAttachShader(id, vertex);
		glAttachShader(id, fragment);

		//链接
		glLinkProgram(id);
		if (!checkLink(id))
		{
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return false;
		}

		//程序创建完成后，清理遗留资源
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return true;
	}

	//检查编译
	static bool checkCompile(GLuint shader, const char* type)
	{
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char log[1024];
			glGetShaderInfoLog(shader, 1024, nullptr, log);
			std::cout << "[Shader] " << type << " 编译失败:\n" << log << std::endl;
			return false;
		}
		return true;
	}

	//检查链接
	static bool checkLink(GLuint program)
	{
		GLint success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (!success)
		{
			char log[1024];
			glGetProgramInfoLog(program, 1024, nullptr, log);
			std::cout << "[Shader] 链接失败:\n" << log << std::endl;
			return false;
		}
		return true;
	}
};
