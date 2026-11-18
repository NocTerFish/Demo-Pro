#include"GeometryBuilder.h"
#include <cmath>

//构建默认立方体
//本来还想着能不能依靠EBO，尝试8个坐标点构造立方体，代码都写好了，结果不许！吃教训了，立方体的最少点方案只能由24点构建
//理由是每个点都需要携带法线信息，导致每个面向都需要构建四个点
std::shared_ptr<Mesh> GeometryBuilder::createCubeMesh(float xLen, float yLen, float zLen)
{
	float halfX = xLen / 2;
	float halfY = yLen / 2;
	float halfZ = zLen / 2;
	std::vector<Vertex> verts =
	{
		//顶面
		Vertex(glm::vec3(-halfX,  halfY,  halfZ), glm::vec2(0.0f, 0.0f), glm::vec3(0, 1, 0)),	// 0 前左
		Vertex(glm::vec3(halfX,  halfY,  halfZ), glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0)),	// 1 前右
		Vertex(glm::vec3(halfX,  halfY, -halfZ), glm::vec2(1.0f, 1.0f), glm::vec3(0, 1, 0)),	// 2 后右
		Vertex(glm::vec3(-halfX,  halfY, -halfZ), glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0)),	// 3 后左

		//侧面 uv范围0.0f到4.0f
		Vertex(glm::vec3(halfX, -halfY,  halfZ), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1)),	// 4  A下
		Vertex(glm::vec3(halfX,  halfY,  halfZ), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, 1)),	// 5  A上
		Vertex(glm::vec3(-halfX, -halfY,  halfZ), glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, 1)),	// 6  B下
		Vertex(glm::vec3(-halfX,  halfY,  halfZ), glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1)),	// 7  B上

		Vertex(glm::vec3(-halfX, -halfY,  halfZ), glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0)),	// 8  B下
		Vertex(glm::vec3(-halfX,  halfY,  halfZ), glm::vec2(1.0f, 1.0f), glm::vec3(-1, 0, 0)),	// 9  B上
		Vertex(glm::vec3(-halfX, -halfY, -halfZ), glm::vec2(2.0f, 0.0f), glm::vec3(-1, 0, 0)),	// 10  C下
		Vertex(glm::vec3(-halfX,  halfY, -halfZ), glm::vec2(2.0f, 1.0f), glm::vec3(-1, 0, 0)),	// 11  C上

		Vertex(glm::vec3(-halfX, -halfY, -halfZ), glm::vec2(2.0f, 0.0f), glm::vec3(0, 0, -1)),	// 12  C下
		Vertex(glm::vec3(-halfX,  halfY, -halfZ), glm::vec2(2.0f, 1.0f), glm::vec3(0, 0, -1)),	// 13  C上
		Vertex(glm::vec3(halfX, -halfY, -halfZ), glm::vec2(3.0f, 0.0f), glm::vec3(0, 0, -1)),	// 14 D下
		Vertex(glm::vec3(halfX,  halfY, -halfZ), glm::vec2(3.0f, 1.0f), glm::vec3(0, 0, -1)),	// 15 D上

		Vertex(glm::vec3(halfX, -halfY, -halfZ), glm::vec2(3.0f, 0.0f), glm::vec3(1, 0, 0)),	// 16 D下
		Vertex(glm::vec3(halfX,  halfY, -halfZ), glm::vec2(3.0f, 1.0f), glm::vec3(1, 0, 0)),	// 17 D上
		Vertex(glm::vec3(halfX, -halfY,  halfZ), glm::vec2(4.0f, 0.0f), glm::vec3(1, 0, 0)),	// 18 A下（闭合）
		Vertex(glm::vec3(halfX,  halfY,  halfZ), glm::vec2(4.0f, 1.0f), glm::vec3(1, 0, 0)),	// 19 A上（闭合）

		//底面
		Vertex(glm::vec3(-halfX, -halfY, -halfZ), glm::vec2(0.0f, 0.0f), glm::vec3(0, -1, 0)),	// 20 后左
		Vertex(glm::vec3(halfX, -halfY, -halfZ), glm::vec2(1.0f, 0.0f), glm::vec3(0, -1, 0)),	// 21 后右
		Vertex(glm::vec3(halfX, -halfY,  halfZ), glm::vec2(1.0f, 1.0f), glm::vec3(0, -1, 0)),	// 22 前右
		Vertex(glm::vec3(-halfX, -halfY,  halfZ), glm::vec2(0.0f, 1.0f), glm::vec3(0, -1, 0)),	// 23 前左
	};

	std::vector<GLushort> idx =
	{
		//顶面 法线+y 逆序绕点
		0,  1,  2,
		0,  2,  3,
		//正面 法线+z 逆序绕点
		4,  5,  6,
		5,  7,  6,
		//左面 法线-x 正序绕点
		8,  9,  10,
		9,  11,  10,
		//背面 法线-z 正序绕点
		12, 13, 14,
		13, 15, 14,
		//右面 法线+x 逆序绕点
		16, 17, 18,
		17, 19, 18,
		//底面 法线-y 正序绕点
		20, 21, 22,
		20, 22, 23,
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->setup(verts, idx);
	return mesh;
}