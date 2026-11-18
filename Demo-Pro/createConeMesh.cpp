#include"GeometryBuilder.h"
#include <cmath>

const float PI = 3.14159265358979323846f;

//构建圆锥体
std::shared_ptr<Mesh> GeometryBuilder::createConeMesh(int segments, float height, float radius)
{
	std::vector<Vertex> verts;
	std::vector<GLushort> idx;

	float halfH = height / 2.0f;
	float unitAngle = 2.0f * PI / segments;	//单位角度

	//圆锥顶点
	verts.push_back(Vertex(glm::vec3(0.0f, halfH, 0.0f), glm::vec2(0.5f, 1.0f), glm::normalize(glm::vec3(0, 1, 0))));

	//计算侧面
	for (int i = 0; i <= segments; i++)
	{
		//计算xz位置
		float angle = i * unitAngle;
		float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

		//计算纹理上的u坐标
		float u = float(i) / segments;

		//计算法线
		glm::vec3 normal = glm::normalize(glm::vec3(std::cos(angle), 0.0f, std::sin(angle)));

		//verts数组的1 到 segments + 1 项用于记录侧面点的信息
		verts.push_back(Vertex(glm::vec3(x, -halfH, z), glm::vec2(u, 0.0f),  normal));
	}

	//计算侧面的索引，i的取值为1 到 segments
	for (int i = 1; i <= segments; i++)
	{
		GLushort k1 = (GLushort)(i);			//该i的下顶点
		GLushort k2 = (GLushort)(i + 1);		//i+1的下顶点

		idx.push_back(0);
		idx.push_back(k2);
		idx.push_back(k1);
	}


	GLushort tempIndex = (GLushort)verts.size();
	//下圆面的中心点
	verts.push_back(Vertex(glm::vec3(0.0f, -halfH, 0.0f), glm::vec2(0.5f, 0.5f), glm::normalize(glm::vec3(0, -1, 0))));	

	//计算下圆面的顶点
	for (int i = 0; i <= segments; i++)
	{
		float angle = i * unitAngle;
		float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

		glm::vec2 uv(0.5f + 0.5f * std::cos(angle), 0.5f + 0.5f * std::sin(angle));

		verts.push_back(Vertex(glm::vec3(x, -halfH, z), uv, glm::normalize(glm::vec3(0, -1, 0))));
	}

	//计算索引
	for (int i = 0; i < segments; i++)
	{
		//-y法线，使用正序绕点
		idx.push_back(tempIndex);
		idx.push_back((GLushort)(tempIndex + i + 1));
		idx.push_back((GLushort)(tempIndex + i + 2));
	}

	//返回
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->setup(verts, idx);
	return mesh;
}