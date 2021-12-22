#pragma once

#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>
#include <fstream>
using namespace std;

#define _DEBUG_LOG_PRINT 1

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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
