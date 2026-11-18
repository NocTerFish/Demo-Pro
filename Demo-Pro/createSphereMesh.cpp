#include"GeometryBuilder.h"
#include <cmath>

const float PI = 3.14159265358979323846f;

//构建球体
std::shared_ptr<Mesh> GeometryBuilder::createSphereMesh(int latSegments, int longSegments, float radius)
{
	std::vector<Vertex> verts;
	std::vector<GLushort> idx;

	//循环计算生成顶点
	for (int lat = 0; lat <= latSegments; lat++)
	{
		float theta = lat * PI / latSegments;	//计算当前的纬度角，范围0到PI，lat == 0时表示北极点
		float sinTheta = std::sin(theta);
		float cosTheta = std::cos(theta);

		//在已确认纬度的情况下，循环生成经度点
		for (int lon = 0; lon <= longSegments; lon++)
		{
			float phi = lon * 2.0f * PI / longSegments;	//计算当前的经度角，范围0到2PI
			float sinPhi = std::sin(phi);
			float cosPhi = std::cos(phi);

			//计算点位置
			glm::vec3 pos
			(
				radius * sinTheta * cosPhi,		//半径 * sin(纬度角) = 该纬度下的xz平面圆的半径长，再乘 cos(经度角)，求得该点的x值
				radius * cosTheta,				//半径 * cos(纬度角) = 该点的y值
				radius * sinTheta * sinPhi		//同x值，该纬度下的xz平面圆的半径长 * sin(经度角)，求得该点的z值
			);

			//计算UV
			glm::vec2 uv((float)lon / longSegments, 1.0f - (float)lat / latSegments);

			//法线归一化
			glm::vec3 normal = glm::normalize(pos);

			//将数据构建成Vertex
			verts.push_back(Vertex(pos, uv, normal));
		}
	}

	//生成索引
	for (int lat = 0; lat < latSegments; lat++)
	{
		for (int lon = 0; lon < longSegments; lon++)
		{
			GLushort first = (GLushort)(lat * (longSegments + 1) + lon);
			GLushort second = (GLushort)(first + longSegments + 1);

			idx.push_back(first);
			idx.push_back(first + 1);
			idx.push_back(second);

			idx.push_back(first + 1);
			idx.push_back(second + 1);
			idx.push_back(second);
		}
	}

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->setup(verts, idx);
	return mesh;
}