#include "SceneBuilder.h"
#include "ModelBuilder.h"
#include "GeometryBuilder.h"
#include "MaterialPool.h"
#include "ComponentBuilder.h"
#include "Light.h"
#include <GLFW/glfw3.h>
#include <cmath>

void Instance2::init()
{
	//声明渲染状态
	renderState = RenderState::Default3D();

	//访问材质池
	MaterialPool* matPool = MaterialPool::getInstance();

	//在场景中创建并加入一个坐标轴
	Axis axis;
	axis.material = matPool->getMat("mat0");
	addModel("axis", std::make_shared<Axis>(axis));

	//在场景中创建并加入一个立方体
	Cube cube;
	cube.setMaterial(matPool->getMat("mtp1"));
	cube.addComponent("spin", std::make_shared<SpinComponent>());
	addModel("cube", std::make_shared<Cube>(cube));

	//在场景中创建并加入一个球体
	Sphere sphere;
	sphere.setMaterial(matPool->getMat("mtp2"));
	sphere.setTransform(Transform(glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.3f)));
	sphere.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(1.0f, 0.0f, 0.0f)));
	addModel("sphere", std::make_shared<Sphere>(sphere));

	//创建一个圆锥
	Cone cone;
	cone.setMaterial(matPool->getMat("mtp3"));
	cone.setTransform(Transform(glm::vec3(-1.0f), glm::vec3(0.0f), glm::vec3(0.3f)));
	cone.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(1.0f, 0.0f, 0.0f)));	//圆周运动组件
	cone.addComponent("orbit2", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 1.0f, 0.0f)));	//圆周运动组件
	cone.addComponent("spin", std::make_shared<SpinComponent>(glm::vec3(1.0f, 0.0f, 0.0f)));	//自转组件
	addModel("cone", std::make_shared<Cone>(cone));		//将对象加入当前场景


	//创建光源
	Light light;
	light.setTransform(Transform(glm::vec3(2.0f, 1.0f, 0.0f)));
	light.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	addLight(std::make_shared<Light>(light));

	Sphere lightSphere;
	lightSphere.setMaterial(matPool->getMat("matBasic"));
	lightSphere.setTransform(Transform(glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.1f)));
	lightSphere.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	addModel("lightSphere", std::make_shared<Model>(lightSphere));
}

void Instance2::updata(float dt)
{
	Scene::updata(dt);
	Scene::render();

}