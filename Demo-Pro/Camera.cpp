#include "Camera.h"
#include <cmath>
#include <iostream>

//构造函数
Camera::Camera(CameraConfig _cameraConfig) : cg(CameraConfig())
{
	_cameraConfig.aspect = _cameraConfig.width / _cameraConfig.height;
	cg = _cameraConfig;
	updateCameraVectors();
}

//view视图矩阵
glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(cg.position, cg.position + cg.front, cg.up);
}

//projection投影矩阵
glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(cg.fov), cg.aspect, cg.nearPlane, cg.farPlane);
}

//更新相机各个向量
void Camera::updateCameraVectors()
{
	glm::vec3 f;
	f.x = std::cos(glm::radians(cg.yaw)) * std::cos(glm::radians(cg.pitch));
	f.y = std::sin(glm::radians(cg.pitch));
	f.z = std::sin(glm::radians(cg.yaw)) * std::cos(glm::radians(cg.pitch));

	cg.front = glm::normalize(f);
	cg.right = glm::normalize(glm::cross(cg.front, cg.worldUp));
	cg.up = glm::normalize(glm::cross(cg.right, cg.front));

	if (cg.roll != 0.0f)
	{
		glm::mat3 rollMat = glm::mat3(glm::rotate
		(
			glm::mat4(1.0f),
			glm::radians(cg.roll),		//将roll的角度换算成弧度
			cg.front					//旋转轴
		));

		cg.up = glm::normalize(rollMat * cg.up);
		cg.right = glm::normalize(rollMat * cg.right);
	}
}

void Camera::setViewPoint(glm::vec3 target)
{
	glm::vec3 dir = glm::normalize(target - cg.position);
	cg.pitch = glm::degrees(std::asin(dir.y));
	cg.yaw = glm::degrees(std::atan2(dir.z, dir.x));
	updateCameraVectors();
}

//重置摄像机配置
void Camera::resetCamer()
{
	cg.position = glm::vec3(0.0f, 0.0f, 3.0f);
	cg.fov = 45.0f;
	cg.roll = 0.0f;
	setViewPoint(glm::vec3(0.0f, 0.0f, 0.0f));
	updateCameraVectors();
}

//按键控制相机方向移动
void Camera::processKeyboard(CameraMoveDir dir, float dt) 
{
	float velocity = cg.movementSpeed * dt;
	if (dir == F)
		cg.position += cg.front * velocity;
	if (dir == B)
		cg.position -= cg.front * velocity;
	if (dir == R)
		cg.position += cg.right * velocity;
	if (dir == L)
		cg.position -= cg.right * velocity;
	if (dir == U)
		cg.position += cg.up * velocity;
	if (dir == D)
		cg.position -= cg.up * velocity;
}

//用鼠标位置设置相机俯仰角和偏航角
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) 
{
	cg.yaw += xoffset * cg.mouseSensitivity;
	cg.pitch += yoffset * cg.mouseSensitivity;

	if (constrainPitch)
	{
		if (cg.pitch > 89.0f) 
			cg.pitch = 89.0f;
		if (cg.pitch < -89.0f) 
			cg.pitch = -89.0f;
	}

	updateCameraVectors();
}

//滚轮缩放fov
void Camera::processMouseScroll(float yoffset)
{
	cg.fov -= yoffset;

	if (cg.fov < 1.0f) 
		cg.fov = 1.0f;
	if (cg.fov > 90.0f) 
		cg.fov = 90.0f;
}

void Camera::processRoll(float dir, float dt)
{
	cg.roll += dir * cg.rollSpeed * dt;

	//区间-180到180
	if (cg.roll > 180.0f) 
		cg.roll -= 360.0f;
	if (cg.roll < -180.0f) 
		cg.roll += 360.0f;

	updateCameraVectors();
}

void Camera::printCg()
{
	std::cout << "摄像机位置：" << "\033[K\n";
	std::cout << "X：" << cg.position.x << "\033[K\n";
	std::cout << "Y：" << cg.position.y << "\033[K\n";
	std::cout << "Z：" << cg.position.z << "\033[K\n";
	std::cout << "摄像机角度：" << "\033[K\n";
	std::cout << "偏航角：" << cg.yaw << "\033[K\n";
	std::cout << "俯仰角：" << cg.pitch << "\033[K\n";
	std::cout << "滚筒角：" << cg.roll << "\033[K\n";
	std::cout << "摄像机fov：" << cg.fov << "\033[K\n";

}
