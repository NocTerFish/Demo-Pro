#include "SceneBuilder.h"
#include "ModelBuilder.h"
#include "GeometryBuilder.h"
#include "MaterialPool.h"
#include "ComponentBuilder.h"
#include "LightBuilder.h"
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
	cube.setTransform(Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
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
	cone.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 1.0f, -1.0f)));	//圆周运动组件
	cone.addComponent("spin", std::make_shared<SpinComponent>(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f));	//自转组件
	addModel("cone", std::make_shared<Cone>(cone));		//将对象加入当前场景

	//创建聚光灯
	SpotLight spot;
	spot.cutOff = 20.0f;
	spot.cutOffRatio = 0.3f;
	spot.color = glm::vec3(0.5f, 1.0f, 0.5f);
	spot.setTransform(Transform(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f)));
	addLight(std::make_shared<SpotLight>(spot));

	Sphere spotSphere;
	spotSphere.setMaterial(matPool->getMat("matBasic"));
	spotSphere.setTransform(Transform(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.1f)));
	addModel("spotSphere", std::make_shared<Sphere>(spotSphere));

	//创建点光源
	PointLight point;
	point.setTransform(Transform(glm::vec3(2.0f, 1.0f, 0.0f)));
	point.color = glm::vec3(1.0f, 0.5f, 0.5f);
	point.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 0.0f, 1.0f)));
	addLight(std::make_shared<PointLight>(point));

	Sphere pointSphere;
	pointSphere.setMaterial(matPool->getMat("matBasic"));
	pointSphere.setTransform(Transform(glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.1f)));
	pointSphere.addComponent("orbit", std::make_shared<OrbitComponent>(glm::vec3(0.0f, 0.0f, 1.0f)));
	addModel("pointSphere", std::make_shared<Sphere>(pointSphere));

	//创建方向光
	DirLight dir;
	dir.setTransform(Transform(glm::vec3(0.0f, 0.0f, -3.0f)));
	dir.color = glm::vec3(0.5f, 0.5f, 1.0f);
	addLight(std::make_shared<DirLight>(dir));

	Sphere dirSphere;
	dirSphere.setMaterial(matPool->getMat("matBasic"));
	dirSphere.setTransform(Transform(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.1f)));
	addModel("dirSphere", std::make_shared<Sphere>(dirSphere));
}

void Instance2::updata(float dt)
{ 
	Scene::updata(dt);
	Scene::render();
}