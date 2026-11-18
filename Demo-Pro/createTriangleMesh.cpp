#include"GeometryBuilder.h"
#include <cmath>

//构建默认三角形
std::shared_ptr<Mesh> GeometryBuilder::createTriangleMesh(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 pos3)
{
	//默认顶点信息
	std::vector<Vertex> verts =
	{
		Vertex(pos1, glm::vec2(0.0f, 0.0f)),	//左下
		Vertex(pos2, glm::vec2(1.0f, 0.0f)),	//右下
		Vertex(pos3, glm::vec2(0.5f, 1.0f)),	//上
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->setup(verts, std::vector<GLushort>());
	return mesh;
}