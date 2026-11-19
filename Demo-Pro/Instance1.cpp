#include "SceneBuilder.h"
#include "ModelBuilder.h"
#include "GeometryBuilder.h"
#include "MaterialPool.h"
#include "ComponentBuilder.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Instance1::init()
{
	//声明渲染状态
	renderState = RenderState::Default3D();

	//访问材质池
	MaterialPool* matPool = MaterialPool::getInstance();

	//在场景中创建并加入一个坐标轴
	Axis axis;
	axis.material = matPool->getMat("mat0");
	addModel("axis", std::make_shared<Axis>(axis));

	//在场景中创建并加入一个圆锥
	Cone cone;
	cone.setMaterial(matPool->getMat("mat1"));
	cone.setTransform(Transform(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	cone.addComponent("coneSpin", std::make_shared<SpinComponent>(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f));
	cone.addComponent("coneOrbit", std::make_shared<OrbitComponent>());
	addModel("cone", std::make_shared<Cone>(cone));

	//在场景中创建并加入一个球体
	Sphere sphere;
	sphere.setMaterial(matPool->getMat("mat2"));
	sphere.setTransform(Transform(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	sphere.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 1.0f, 0.0f)));
	addModel("sphere", std::make_shared<Sphere>(sphere));

	//在场景中创建并加入一个圆柱
	Cylinder cylinder;
	cylinder.setMaterial(matPool->getMat("mat3"));
	cylinder.setTransform(Transform(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f), glm::vec3(0.5f)));
	cylinder.addComponent("cylinderSpin", std::make_shared<SpinComponent>());
	cylinder.addComponent("cylinderOrbit", std::make_shared<OrbitComponent>());
	addModel("cylinder", std::make_shared<Cylinder>(cylinder));

	//在场景中创建并加入一个立方体
	Cube cube;
	cube.setMaterial(matPool->getMat("mat4"));
	cube.addComponent("CubeSpin", std::make_shared<SpinComponent>());
	addModel("cube", std::make_shared<Cube>(cube));
	
}

void Instance1::updata(float dt)
{
	Scene::updata(dt);
	Scene::render();

	//更新立方体
	std::shared_ptr<Cube> cube = getModelAs<Cube>("cube");
	cube->getMaterialAs<TextureMaterial>()->mixRate = 0.5f + 0.5f * sin(totalTime);

}