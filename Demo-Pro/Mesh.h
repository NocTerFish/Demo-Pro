#pragma once
#include<glad/glad.h>
#include<vector>
#include"Vertex.h"

class Mesh
{
public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint vertexSize;
	GLuint indexSize;

	Mesh();
	~Mesh();

	//禁止拷贝
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	//上传数据到GPU
	void setup(const std::vector<Vertex>& verts, const std::vector<GLushort>& indexs);

	//只更新顶点数据
	void updateVertices(const std::vector<Vertex>& verts);

	//绘制
	void draw(GLenum mode = GL_TRIANGLES) const;

	//统计
	GLuint GetIndexCount()  const { return indexSize; }
	GLuint GetVertexCount() const { return vertexSize; }

	void configureAttributes();
};