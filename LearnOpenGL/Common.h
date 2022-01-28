#pragma once

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <fstream>
using namespace std;

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include "Camera.h"

#define _DEBUG_LOG_PRINT 1

// 设置窗口的大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 跟踪帧率，Timing
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间


/* 未创建摄像机类
float fov = 45.f;
// 鼠标进入检测函数
bool firstMouse = true;

// 鼠标的相关参数
double lastX=400, lastY=300,yaw=-90,pitch = 0;

*/

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


//// 初始化摄像机位置
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.f, 3.0f);
//glm::vec3 cameraTarget = glm::vec3(0.f, 0.f, 0.f);
//// 相机方向的反向
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
////std::cout << "CameraDir: (" << cameraDirection.x << "," << cameraDirection.y << "," << cameraDirection.z << ")" << std::endl;
//// 向上的方向,随便定义一个方向
//glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f);
//// 相机的右向量
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
////std::cout << "cameraRight: (" << cameraRight.x << "," << cameraRight.y << "," << cameraRight.z << ")" << std::endl;
//// 相机的向上方向
//glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
////std::cout << "cameraUp: (" << cameraUp.x << "," << cameraUp.y << "," << cameraUp.z << ")" << std::endl;

/*未创建摄像机类时的参数
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

*/


// 窗口大小改变回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 鼠标键盘输入回调
void processInput(GLFWwindow * window); 
// 鼠标位置改变回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// 鼠标滚轮回调
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*未有摄像机类的写法
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
	
	*/

	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// 相机移动控制，未创建摄像机类
	/*
		float cameraSpeed = 2.5f* deltaTime; // 自定义的速度，会和电脑的性能有关系
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	*/

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	/*不存在摄像机类时的写法
		if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		std::cout << "Mouse has in Screen succeed!!!"<<"x= "<<lastX << " y= "<<lastY << std::endl;
		firstMouse = false;
	}

	double xoffset = (xpos - lastX);
	double yoffset = (lastY - ypos);
	lastX = xpos;
	lastY = ypos;

	double sensitivity = 0.05f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	//std::cout << "Mouse has in Screen succeed!!!" << "xoffset= " << xoffset << " yoffset= " << yoffset << std::endl;

	yaw += xoffset;
	pitch += yoffset;
	std::cout << "Mouse has in Screen succeed!!!" << "yaw= " << yaw << " pitch= " << pitch << std::endl;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front= glm::vec3(0.0f,0.0f,-1.0f);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	
	*/
	// 检测鼠标是否是第一次进入窗口
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}


//! Print the log info to console;
static void log(std::string strLog)
{
#ifdef _DEBUG_LOG_PRINT
	std::cout << strLog << std::endl;

	//! Write the debug log in file(debug.log);
	fstream fs("./debug.log", ios::app);
	fs << strLog << endl;
	fs.close();
#endif
}

//! Print the opengl and glsl's version information;
static void TEGlVersionInfo(void)
{
	const GLubyte* byteGlVersion = glGetString(GL_VERSION);
	const GLubyte* byteGlVendor = glGetString(GL_VENDOR);
	const GLubyte* byteGlRenderer = glGetString(GL_RENDERER);
	const GLubyte* byteSLVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::string strTemp = "OpenGL version: ";
	strTemp += (char*)byteGlVersion;
	log(strTemp);

	strTemp = "GL_VENDOR: ";
	strTemp += (char*)(byteGlVendor);
	log(strTemp);

	strTemp = "GL_RENDERER: ";
	strTemp += (char*)(byteGlRenderer);
	log(strTemp);

	strTemp = "GLSL version: ";
	strTemp += (char*)(byteSLVersion);
	log(strTemp);
}
