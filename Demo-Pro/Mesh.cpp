#include"Mesh.h"
#include<cstddef>

//构造函数
Mesh::Mesh() : VAO(0), VBO(0), EBO(0), vertexSize(0), indexSize(0)
{
}

//析构函数
Mesh::~Mesh()
{
	if (EBO) 
		glDeleteBuffers(1, &EBO);
	if (VBO)
		glDeleteBuffers(1, &VBO);
	if (VAO)
		glDeleteVertexArrays(1, &VAO);
}

//在GPU端开辟内存、绑定、上传数据，同时需要配置VAO
void Mesh::setup(const std::vector<Vertex>& verts, const std::vector<GLushort>& indexs)
{
	vertexSize = (GLuint)verts.size();
	indexSize = (GLuint)indexs.size();
	//创建VAO
	glGenVertexArrays(1, &VAO);
	//绑定VAO
	glBindVertexArray(VAO);
	//创建VBO
	glGenBuffers(1, &VBO);
	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//将CPU数据上传到GPU
	glBufferData
	(
		GL_ARRAY_BUFFER,				//目标缓冲区类型
		verts.size() * sizeof(Vertex),	//总字节数
		verts.data(),					//CPU端数据的起始指针
		GL_STATIC_DRAW					//使用模式提示
	);
	//创建EBO并邦定上传索引数据
	if (indexSize > 0)
	{
		//创建EBO
		glGenBuffers(1, &EBO);
		//绑定EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//将CPU数据上传到GPU
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexs.size() * sizeof(GLushort), indexs.data(), GL_STATIC_DRAW);
	}

	//配置属性
	configureAttributes();
	
	//解绑
	glBindVertexArray(0);
}

void Mesh::configureAttributes()
{
	//设置步长
	GLsizei stride = sizeof(Vertex);

	//将location 0 设置并启用点位信息的vec3
	glVertexAttribPointer
	(
		0,								//location序号
		3,								//该属性的分量数量
		GL_FLOAT,						//该属性的分量数据类型
		GL_FALSE,						//是否归一化
		stride,							//步长
		(void*)offsetof(Vertex, pos)	//该属性的偏移量 -- offsetof函数可以自动计算特定成员变量距离结构体起始位置的字节偏移量
	);
	glEnableVertexAttribArray(0);

	//将location 1 设置并启用颜色信息的vec4
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//将location 2 设置并启用UV纹理坐标的vec2
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, tex));
	glEnableVertexAttribArray(2);

	//将location 3 设置并启用法线信息的vec3
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);
}

void Mesh::updateVertices(const std::vector<Vertex>& verts)
{
	//如果新传入的数组信息字节数不等于旧信息的字节数，重新setup该数组
	if ((GLuint)verts.size() != vertexSize)
	{
		setup(verts, std::vector<GLushort>());
		return;
	}

	//否则，仅更新覆盖VBO数据，沿用VAO和EBO的管理和索引
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verts.size() * sizeof(Vertex), verts.data());
}

//绘制函数
void Mesh::draw(GLenum mode) const
{
	if (VAO == 0)
		return;

	glBindVertexArray(VAO);

	if (EBO)
	{
		//使用EBO进行绘制的函数
		glDrawElements
		(
			mode,				//图元类型 
			indexSize,			//索引个数
			GL_UNSIGNED_SHORT,	//索引的数据类型
			0					//偏移量
		);
	}
	else
	{
		//不使用EBO绘制的函数
		glDrawArrays
		(
			mode,		//图元类型
			0,			//起始索引
			vertexSize	//顶点个数
		);
	}

}
