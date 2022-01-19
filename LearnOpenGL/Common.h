#pragma once

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <fstream>
using namespace std;

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#define _DEBUG_LOG_PRINT 1

// 初始化摄像机位置
glm::vec3 cameraPos = glm::vec3(0.0f, 0.f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.f, 0.f, 0.f);
// 相机方向的反向
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//std::cout << "CameraDir: (" << cameraDirection.x << "," << cameraDirection.y << "," << cameraDirection.z << ")" << std::endl;
// 向上的方向,随便定义一个方向
glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f);
// 相机的右向量
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//std::cout << "cameraRight: (" << cameraRight.x << "," << cameraRight.y << "," << cameraRight.z << ")" << std::endl;
// 相机的向上方向
glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
//std::cout << "cameraUp: (" << cameraUp.x << "," << cameraUp.y << "," << cameraUp.z << ")" << std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window); 


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


	// 相机移动控制
	float cameraSpeed = 0.05f; // 自定义的速度，会和电脑的性能有关系
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * (-cameraDirection);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += cameraSpeed * (-cameraRight);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * (-cameraDirection);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= cameraSpeed * (-cameraRight);

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
