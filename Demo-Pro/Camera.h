#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//相机移动方向
enum CameraMoveDir
{
	F,	//前
	B,	//后
	L,	//左
	R,	//右
	U,	//上
	D,	//下
};

//摄像机的配置信息
struct CameraConfig
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);	//相机位置
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);		//前向量
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);			//上向量
	glm::vec3 right;	//右向量
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);	//世界上向量

	float yaw = -90.0f;				//偏航角
	float pitch = 0.0f;				//俯仰角
	float roll = 0.0f;				//滚筒角

	float width = 1200.0f;			//视场宽度
	float height = 800.0f;			//视场高度
	float aspect;					//宽高比
	float fov = 45.0f;				//视野角度

	float nearPlane = 0.1f;			// 近平面
	float farPlane = 100.0f;		// 远平面

	float movementSpeed = 3.0f;		//移动速度
	float mouseSensitivity = 0.1f;	//鼠标灵敏度
	float rollSpeed = 90.0f;		//滚筒角转速

};

class Camera
{
public:
	CameraConfig cg;

	Camera(CameraConfig cg = CameraConfig());

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	void processKeyboard(CameraMoveDir dir, float dt);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset);
	void processRoll(float dir, float dt);

	//设置摄像机看向特定点位的函数
	void setViewPoint(glm::vec3 target);

	//重置摄像机
	void resetCamer();

	void updateCameraVectors();

	//打印当前摄像机信息
	void printCg();

};