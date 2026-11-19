#pragma once
#include "Model.h"
#include "GeometryBuilder.h"
#include <vector>
#include <cmath>

//坐标轴
class Axis : public Line
{
public:
	float xLen;
	float yLen;
	float zLen;

	Axis()
	{
		//初始化
		setMesh();
		setTransform(glm::vec3(0.0f));
	}

	~Axis()
	{
	}

	//构建坐标轴
	void setMesh(float _xLen = 100.0f, float _yLen = 100.0f, float _zLen = 100.0f)
	{
		xLen = _xLen;
		yLen = _yLen;
		zLen = _zLen;
		mesh = GeometryBuilder::createAxisMesh(xLen, yLen, zLen);
	}

};

//三角形
class Triangle : public Model
{
public:

	Triangle()
	{
		//初始化
		setMesh();
		setTransform(glm::vec3(0.0f));
	}
	~Triangle()
	{
	}

	//设置网格
	void setMesh
	(
		glm::vec3 pos1 = glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3 pos2 = glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3 pos3 = glm::vec3(0.0f, 0.5f, 0.0f)
	)
	{
		mesh = GeometryBuilder::createTriangleMesh(pos1, pos2, pos3);
	}
};

//立方体
class Cube : public Model
{
public:
	float xLen;
	float yLen;
	float zLen;

	Cube()
	{
		//初始化
		setMesh();
		setTransform(glm::vec3(0.0f));
	}

	~Cube()
	{
	}

	void setMesh(float _xLen = 1.0f, float _yLen = 1.0f, float _zLen = 1.0f)
	{
		xLen = _xLen;
		yLen = _yLen;
		zLen = _zLen;
		mesh = GeometryBuilder::createCubeMesh(xLen, yLen, zLen);
	}
};

//球体
class Sphere : public Model
{
public:
	int segments;
	float radius;

	Sphere()
	{
		//初始化时调用一次默认的网格生成
		setMesh();
		setTransform(glm::vec3(0.0f));
	}

	~Sphere()
	{
	}

	void setMesh(int _segments = 16, float _radius = 1.0f)
	{
		segments = _segments;
		radius = _radius;
		mesh = GeometryBuilder::createSphereMesh(segments, segments, radius);
	}
};

//圆柱体
class Cylinder : public Model
{
public:
	int   segments;
	float height;
	float radius;

	Cylinder()
	{
		//初始化
		setMesh();
		setTransform(glm::vec3(0.0f));
	}

	~Cylinder() {}

	void setMesh(int _segments = 16, float _height = 2.0f, float _radius = 1.0f)
	{
		segments = _segments;
		height = _height;
		radius = _radius;
		mesh = GeometryBuilder::createCylinderMesh(segments, height, radius);
	}
};

//圆锥体
class Cone : public Model
{
public:
	int   segments;
	float height;
	float radius;

	Cone()
	{
		//初始化
		setMesh();
		setTransform(glm::vec3(0.0f));
	}

	~Cone() {}

	void setMesh(int _segments = 16, float _height = 2.0f, float _radius = 1.0f)
	{
		segments = _segments;
		height = _height;
		radius = _radius;
		mesh = GeometryBuilder::createConeMesh(segments, height, radius);
	}
};