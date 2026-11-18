#include "SceneBuilder.h"
#include "Objects.h"
#include "GeometryBuilder.h"
#include "ShaderLibrary.h"
#include "TexturePool.h"
#include "Materials.h"
#include "ComponentBuilder.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Instance1::init()
{
	//声明渲染状态
	renderState = RenderState::Default3D();

	//注册着色器
	ShaderLibrary* lib = ShaderLibrary::getInstance();
	lib->addFromFile("texture", "texture.vert", "texture.frag");
	lib->addFromFile("color", "color.vert", "color.frag");

	//创建纹理池
	TexturePool* TexPool = TexturePool::getInstance();
	TexPool->loadTex("wives1", "wives1.png");
	TexPool->loadTex("wives2", "wives2.png");
	TexPool->loadTex("wives3", "wives3.png");
	TexPool->loadTex("wives4", "wives4.png");

	//创建坐标轴用的0号材质
	auto mat0 = std::make_shared<VertexColorMaterial>();
	mat0->shader = lib->get("color");
	//创建材质1
	auto mat1 = std::make_shared<TextureMaterial>();
	mat1->shader = lib->get("texture");
	mat1->tex1 = TexPool->get("wives1");
	mat1->mixRate = 0.0f;
	//创建材质2
	auto mat2 = std::make_shared<TextureMaterial>();
	mat2->shader = lib->get("texture");
	mat2->tex1 = TexPool->get("wives2");
	mat2->mixRate = 0.0f;
	//创建材质3
	auto mat3 = std::make_shared<TextureMaterial>();
	mat3->shader = lib->get("texture");
	mat3->tex1 = TexPool->get("wives4");
	mat3->mixRate = 0.0f;
	//创建材质4
	auto mat4 = std::make_shared<TextureMaterial>();
	mat4->shader = lib->get("texture");
	mat4->tex1 = TexPool->get("wives2");
	mat4->tex2 = TexPool->get("wives3");
	mat4->mixRate = 0.5f;

	//在场景中创建并加入一个坐标轴
	Axis axis;
	axis.material = mat0;
	addObject("axis", std::make_shared<Axis>(axis));

	//在场景中创建并加入一个圆锥
	Cone cone;
	cone.setMaterial(mat1);
	cone.setTransform(Transform(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	cone.addComponent("coneSpin", std::make_shared<SpinComponent>(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f));
	cone.addComponent("coneOrbit", std::make_shared<OrbitComponent>());
	addObject("cone", std::make_shared<Cone>(cone));

	//在场景中创建并加入一个球体
	Sphere sphere;
	sphere.setMaterial(mat2);
	sphere.setTransform(Transform(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	sphere.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 1.0f, 0.0f)));
	addObject("sphere", std::make_shared<Sphere>(sphere));

	//在场景中创建并加入一个圆柱
	Cylinder cylinder;
	cylinder.setMaterial(mat3);
	cylinder.setTransform(Transform(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	cylinder.addComponent("cylinderSpin", std::make_shared<SpinComponent>());
	cylinder.addComponent("cylinderOrbit", std::make_shared<OrbitComponent>());
	addObject("cylinder", std::make_shared<Cylinder>(cylinder));

	//在场景中创建并加入一个立方体
	Cube cube;
	cube.setMaterial(mat4);
	cube.addComponent("CubeSpin", std::make_shared<SpinComponent>());
	addObject("cube", std::make_shared<Cube>(cube));
	
}

void Instance1::updata(float dt)
{
	Scene::updata(dt);
	Scene::render();

	//更新立方体
	std::shared_ptr<Cube> cube = getObjectAs<Cube>("cube");
	cube->getMaterialAs<TextureMaterial>()->mixRate = 0.5f + 0.5f * sin(totalTime);

}