#include "SceneBuilder.h"
#include "Objects.h"
#include "GeometryBuilder.h"
#include "ShaderLibrary.h"
#include "TexturePool.h"
#include "MaterialPool.h"
#include "ComponentBuilder.h"
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
	addObject("axis", std::make_shared<Axis>(axis));

	//在场景中创建并加入一个立方体
	Cube cube;
	cube.setMaterial(matPool->getMat("mat4"));
	cube.setTransform(glm::vec3(1.0f));
	cube.addComponent("spin", std::make_shared<SpinComponent>());	//自转组件
	cube.addComponent("orbit", std::make_shared<OrbitComponent>());	//圆周运动组件
	addObject("cube", std::make_shared<Cube>(cube));

}

void Instance2::updata(float dt)
{
	Scene::updata(dt);
	Scene::render();

}