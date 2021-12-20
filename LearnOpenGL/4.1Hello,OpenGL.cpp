#include <glad/glad.h>
#include <glfw3.h>

#include <iostream>

// ������Ⱦ�ӿڴ�С�ĺ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// ���ô��ڴ�С�Ĳ���
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// ��ʼ��glfw�⣬��ʼ��֮�󣬴󲿷ֿ��еĺ����ſ���ʹ��
	glfwInit();
	// ����glfw�İ汾��Ϣ
	// Ҳ��һЩ������Ϣ��������Բο�����https://www.glfw.org/docs/latest/window.html#window_hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ����opengl es ��context����
	// �±�ע�͵��Ĵ����δע�͵���������ͬ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// mac ƽ̨��֧��
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
	// ע��һ������--���ڴ�С�ı�ʱ���Ż���õĻص�����
	// ��Ҫ����Ⱦѭ��֮ǰע��
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ����opengl�ĺ���ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// ��Ⱦѭ��
	// glfwWindowShouldClose�� ���glfw�Ƿ�Ҫ�󴰿��˳�
	while (!glfwWindowShouldClose(window))
	{
		// ����Ƿ���esc���룬������ͽ�����Ⱦѭ��
		processInput(window);

		// ��Ҫʵ�ֵ���Ⱦָ��
		// ÿ������ʱʹ�õ���Ļ��ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����һ֡����Ⱦ���,�������������ص�buffer
		// GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT,GL_STENCIL_BUFFER_BIT
		glClear(GL_COLOR_BUFFER_BIT);

		// ����������
		glfwSwapBuffers(window);
		// ����Ƿ�����꣬���̵��¼������������ö�Ӧ�Ļص�����
		glfwPollEvents();
	}

	// ��Ⱦ����֮���ͷ���ص���Դ
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// �Ƿ���esc��,
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}