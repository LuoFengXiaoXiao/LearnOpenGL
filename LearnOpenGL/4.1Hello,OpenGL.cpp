#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

// 设置渲染视口大小的函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// 设置窗口大小的参数
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// 初始化glfw库，初始化之后，大部分库中的函数才可以使用
	glfwInit();
	// 设置glfw的版本信息
	// 也有一些其它信息（具体可以参考）：https://www.glfw.org/docs/latest/window.html#window_hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// 忽略opengl es 的context参数
	// 下边注释掉的代码和未注释掉的作用相同
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// mac 平台的支持
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!!!" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	// 注册一个函数--窗口大小改变时，才会调用的回调函数
	// 需要在渲染循环之前注册
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 管理opengl的函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// 渲染循环
	// glfwWindowShouldClose： 检查glfw是否要求窗口退出
	while (!glfwWindowShouldClose(window))
	{
		// 检测是否有esc输入，有输入就结束渲染循环
		processInput(window);

		// 需要实现的渲染指令
		// 每次清屏时使用的屏幕颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清除上一帧的渲染结果,可以清除各种相关的buffer
		// GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT,GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		// 交换缓冲区
		glfwSwapBuffers(window);
		// 检测是否有鼠标，键盘等事件触发，并调用对应的回调函数
		glfwPollEvents();
	}

	// 渲染结束之后，释放相关的资源
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// 是否点击esc键,
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}