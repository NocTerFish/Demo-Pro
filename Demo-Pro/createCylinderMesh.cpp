#include"GeometryBuilder.h"
#include <cmath>

const float PI = 3.14159265358979323846f;

//构建圆柱体
std::shared_ptr<Mesh> GeometryBuilder::createCylinderMesh(int segments, float height, float radius)
{
	std::vector<Vertex> verts;
	std::vector<GLushort> idx;

	float halfH = height / 2.0f;
	float unitAngle = 2.0f * PI / segments;	//单位角度

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

		//verts数组的0 到 2 * segments + 1项用于记录侧面的信息
		verts.push_back(Vertex(glm::vec3(x, -halfH, z), glm::vec2(u, 0.0f), normal));	//数组偶数为侧面的下顶点
		verts.push_back(Vertex(glm::vec3(x, halfH, z), glm::vec2(u, 1.0f), normal));	//数组奇数为侧面的上顶点
	}

	//计算侧面的索引，i的取值为0 到 segments - 1
	for (int i = 0; i < segments; i++)
	{
		GLushort k1 = (GLushort)(i * 2);			//该i的下顶点
		GLushort k2 = (GLushort)(i * 2 + 1);		//该i的上顶点
		GLushort k3 = (GLushort)((i + 1) * 2);		//i+1的下顶点
		GLushort k4 = (GLushort)((i + 1) * 2 + 1);	//i+1的上顶点

		idx.push_back(k1);
		idx.push_back(k2);
		idx.push_back(k3);
		idx.push_back(k2);
		idx.push_back(k4);
		idx.push_back(k3);
	}

	GLshort tempIndex = (GLushort)verts.size();	//先临时存储当前顶点数组的大小
	//上圆面的中心点
	verts.push_back(Vertex(glm::vec3(0.0f, halfH, 0.0f), glm::vec2(0.5f, 0.5f), glm::normalize(glm::vec3(0, 1, 0))));

	//计算上圆面的顶点
	for (int i = 0; i <= segments; i++)
	{
		float angle = i * unitAngle;
		float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

		//uv用极坐标映射至0到1的区间
		glm::vec2 uv(0.5f + 0.5f * std::cos(angle), 0.5f + 0.5f * std::sin(angle));

		verts.push_back(Vertex(glm::vec3(x, halfH, z), uv, glm::vec3(0, 1, 0)));
	}

	//计算上圆面的索引
	for (int i = 0; i < segments; i++)
	{
		//+y法线，使用逆序绕点
		idx.push_back(tempIndex);
		idx.push_back((GLushort)(tempIndex + i + 2));
		idx.push_back((GLushort)(tempIndex + i + 1));
	}

	tempIndex = (GLushort)verts.size();
	//下圆面的中心点
	verts.push_back(Vertex(glm::vec3(0.0f, -halfH, 0.0f), glm::vec2(0.5f, 0.5f), glm::normalize(glm::vec3(0, -1, 0))));

	//计算下圆面的顶点
	for (int i = 0; i <= segments; i++)
	{
		float angle = i * unitAngle;
		float x = radius * std::cos(angle);
		float z = radius * std::sin(angle);

		glm::vec2 uv(0.5f + 0.5f * std::cos(angle), 0.5f + 0.5f * std::sin(angle));

		verts.push_back(Vertex(glm::vec3(x, -halfH, z), uv, glm::vec3(0, -1, 0)));
	}

	//计算下圆面索引
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