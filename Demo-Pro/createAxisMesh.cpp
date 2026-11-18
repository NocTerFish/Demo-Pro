#include"GeometryBuilder.h"
#include <cmath>


//构建默认坐标系
std::shared_ptr<Mesh> GeometryBuilder::createAxisMesh(float xLen, float yLen, float zLen)
{
	float halfX = xLen / 2;
	float halfY = yLen / 2;
	float halfZ = zLen / 2;
	std::vector<Vertex> verts =
	{
		
		Vertex(glm::vec3(-halfX, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.1f)),
		Vertex(glm::vec3(halfX, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 0.1f)),
		Vertex(glm::vec3(0.0f, -halfY, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.1f)),
		Vertex(glm::vec3(0.0f, halfY, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 0.1f)),
		Vertex(glm::vec3(0.0f, 0.0f, -halfZ), glm::vec4(0.0f, 0.0f, 1.0f, 0.1f)),
		Vertex(glm::vec3(0.0f, 0.0f, halfZ), glm::vec4(0.0f, 0.0f, 1.0f, 0.1f)),
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->setup(verts, std::vector<GLushort>());

	return mesh;
}