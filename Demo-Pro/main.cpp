#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>
#include<cmath>
#include"RenderState.h"
#include"TexturePool.h"
#include"Materials.h"
#include"Objects.h"
#include"Camera.h"
#include"Scene.h"
#include"SceneBuilder.h"

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool cameraControl = true;

//鼠标回调
void mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
		return;
	}

	if (!cameraControl)
		return;

	//计算偏移
	float xoffset = (float)xpos - lastX;
	float yoffest = lastY - (float)ypos;
	lastX = (float)xpos;
	lastY = (float)ypos;

	Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
	camera->processMouseMovement(xoffset, yoffest);
}

//滚轮回调
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!cameraControl)
		return;

	Camera* camera = (Camera*)glfwGetWindowUserPointer(window);
	camera->processMouseScroll((float)yoffset);
}

//键盘回调
void processInput(GLFWwindow* window, float dt)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//切换鼠标是否控制摄像机
	static bool toggleWasPressed = false;
	bool toggleNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

	if (toggleNow && !toggleWasPressed)
	{
		cameraControl = !cameraControl;

		if (cameraControl)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;   //下一帧第一次鼠标移动只记录坐标
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	toggleWasPressed = toggleNow;

	if (!cameraControl)
		return;

	Camera* camera = (Camera*)glfwGetWindowUserPointer(window);	//获得当前窗口的用户指针，转换回摄像机指针

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
		camera->processKeyboard(F, dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
		camera->processKeyboard(B, dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		camera->processKeyboard(L, dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		camera->processKeyboard(R, dt);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->processKeyboard(U, dt);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera->processKeyboard(D, dt);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->processRoll(-1.0f, dt);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->processRoll(1.0f, dt);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		camera->resetCamer();
}

//打印函数
void printInfo(GLFWwindow* window)
{
	Camera* camera = (Camera*)glfwGetWindowUserPointer(window);	//获得当前窗口的用户指针，转换回摄像机指针
	std::cout << "\033[H";
	camera->printCg();
	std::cout << "\033[?25l" << std::flush;
}

int main()
{
	glfwInit();

	//确定 OpenGL 4.6 Core Profile 的上下文
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow
	(
		SCR_WIDTH,	//窗口宽度
		SCR_HEIGHT, //窗口高度
		"Demo-Pro", //窗口标题
		NULL,		//monitor: 指定窗口在哪个显示器上显示，NULL表示默认显示器
		NULL		//share: 指定窗口共享资源的窗口，NULL表示不共享
	);

	if (window == NULL)
	{
		std::cout << "创建窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}

	//将窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);

	//加载openGL的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//打印 GPU 支持的最大顶点属性数
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "GPU支持的最大顶点属性数: " << nrAttributes << std::endl;

	//创建场景实例
	Instance1 scene;
	scene.init();

	//获得当前场景的相机指针，将其转化为void类型指针，放入窗口用户指针中供回调引用
	glfwSetWindowUserPointer(window, (void*)&scene.camera);

	//注册回调
	glfwSetCursorPosCallback(window, mouseCallBack);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//初始化计时器
	float lastTime = (float)glfwGetTime();

	//while主循环
	while (!glfwWindowShouldClose(window))
	{
		//更新计时器
		float now = (float)glfwGetTime();
		float dt = now - lastTime;
		lastTime = now;

		processInput(window, dt);

		//场景实例的updata更新
		scene.updata(dt);

		//在控制台中打印摄像机信息
		printInfo(window);

		//交换缓冲
		glfwSwapBuffers(window);

		//处理事件
		glfwPollEvents();
	}

	//清理
	glfwTerminate();
	return 0;
}