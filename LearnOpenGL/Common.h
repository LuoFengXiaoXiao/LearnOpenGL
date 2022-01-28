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

// ���ô��ڵĴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ����֡�ʣ�Timing
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��


/* δ�����������
float fov = 45.f;
// �������⺯��
bool firstMouse = true;

// ������ز���
double lastX=400, lastY=300,yaw=-90,pitch = 0;

*/

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


//// ��ʼ�������λ��
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.f, 3.0f);
//glm::vec3 cameraTarget = glm::vec3(0.f, 0.f, 0.f);
//// �������ķ���
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
////std::cout << "CameraDir: (" << cameraDirection.x << "," << cameraDirection.y << "," << cameraDirection.z << ")" << std::endl;
//// ���ϵķ���,��㶨��һ������
//glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f);
//// �����������
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
////std::cout << "cameraRight: (" << cameraRight.x << "," << cameraRight.y << "," << cameraRight.z << ")" << std::endl;
//// ��������Ϸ���
//glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));
////std::cout << "cameraUp: (" << cameraUp.x << "," << cameraUp.y << "," << cameraUp.z << ")" << std::endl;

/*δ�����������ʱ�Ĳ���
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

*/


// ���ڴ�С�ı�ص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// ����������ص�
void processInput(GLFWwindow * window); 
// ���λ�øı�ص�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// �����ֻص�
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	/*δ����������д��
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


	// ����ƶ����ƣ�δ�����������
	/*
		float cameraSpeed = 2.5f* deltaTime; // �Զ�����ٶȣ���͵��Ե������й�ϵ
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
	/*�������������ʱ��д��
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
	// �������Ƿ��ǵ�һ�ν��봰��
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
