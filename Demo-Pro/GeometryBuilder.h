#pragma once
#include<memory>
#include<vector>
#include"Mesh.h"

class GeometryBuilder
{
public:
	//创建坐标系
	static std::shared_ptr<Mesh> createAxisMesh(float xLen, float yLen, float zLen);
	//创建三角形
	static std::shared_ptr<Mesh> createTriangleMesh
	(
		glm::vec3 pos1 = glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3 pos2 = glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3 pos3 = glm::vec3(0.0f, 0.5f, 0.0f)
	);
	//创建长方形
	static std::shared_ptr<Mesh> createRectangleMesh();
	//创建立方体
	static std::shared_ptr<Mesh> createCubeMesh(float xLen, float yLen, float zLen);
	//创建球体	需要经纬度细分数
	static std::shared_ptr<Mesh> createSphereMesh(int latSegments = 32, int longSegments = 32, float radius = 1.0f);
	//创建圆柱	需要圆面的细分数
	static std::shared_ptr<Mesh> createCylinderMesh(int segments = 32, float height = 2.0f, float radius = 1.0f);
	//创建圆锥体
	static std::shared_ptr<Mesh> createConeMesh(int segments = 32, float height = 2.0f, float radius = 1.0f);
};