

#include "Common.h"
#include "Shader.h"

// 设置窗口的大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// 初始化并设置glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 使用Shader类读取着色器
	Shader ourShader("shader/VertexShader/Triangle.vs", "shader/FragShader/Triangle.fs");


	// 链接顶点属性--告诉GPU解释顶点数据的方法
	// ----------------------------------------
	// 创建初始的顶点数组
	float vertices[] = {
		// 位置              // 颜色
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
	};

	// 创建VAO和VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// 绑定VAO
	glBindVertexArray(VAO);
	// 绑定VBO,复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 设置顶点位置属性指针
	// 该处的最后一个位置为位置偏移
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 设置顶点颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 复制空值顶点数组到缓存中，为了以后安全地解除绑定
	// 将VAO和VBO传递到地位置均设置为空
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// --------------------------------
	// 顶点链接完成

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue);
		
		std::cout << greenValue << std::endl;

		ourShader.setFloat("xOffset", greenValue);

		// 绘制三角形
		ourShader.use();
		// 只有一个VAO，所以不需要每次都去绑定，但是绑定可以使程序更有条理
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 结束之后删除相关的内存占用
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//删除shader中program的内存占用
	ourShader.deleteProgram();

	glfwTerminate();
	return 0;
}

