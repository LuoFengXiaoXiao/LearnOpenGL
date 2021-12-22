

#include "Common.h"

// 设置窗口的大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// 顶点着色器--感觉这样写很傻
// 颜色变量的属性位置设置为1
// 向片段着色器输出一个颜色
/*

#version 330 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 1

out vec3 ourColor; // 向片段着色器输出一个颜色

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}

*/

const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	ourColor = aColor;\n"
"}\n";

/*
#version 330 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
	FragColor = vec4(ourColor, 1.0);
}
*/


// 片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor,1.0f);\n"
"}\n";



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

	// 创建着色器程序对象
	// ------------------------------------
	// 创建顶点着色器
	//  ---------------------
	// 创建一个顶点着色器对象
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 引入顶点着色器的代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// 编译顶点着色器
	glCompileShader(vertexShader);
	// 判断着色器的编译结果
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//  ----------------------
	// 顶点着色器创建完成
	// 创建片段着色器
	//  ----------------------
	// 创建一个片段着色器对象
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// 设置片段着色器的代码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);
	// 判断编译结果
	glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//  -----------------------
	// 片段着色器创建完成
	// 创建着色器程序对象，并将顶点着色器和片段着色器链接到着色器程序对象
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// 链接着色器
	glLinkProgram(shaderProgram);
	// 判断链接结果
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// 清理顶点着色器和片段着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ---------------------------------------
	// 着色器程序对象创建完成


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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
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

		// 绘制三角形
		glUseProgram(shaderProgram);
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
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

