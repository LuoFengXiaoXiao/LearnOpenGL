

#include "Common.h"

// 设置窗口的大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 顶点着色器--感觉这样写很傻
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

// 片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
"}\n";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
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
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	// 设置片段着色器的代码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	// 编译片段着色器
	glCompileShader(fragmentShader);
	// 判断编译结果
	glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	glCompileShader(fragmentShader1);

	glGetProgramiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//  -----------------------
	// 片段着色器创建完成
	// 创建着色器程序对象，并将顶点着色器和片段着色器链接到着色器程序对象
	unsigned int shaderProgram = glCreateProgram();
	unsigned int shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	// 链接着色器
	glLinkProgram(shaderProgram);
	// 判断链接结果
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glLinkProgram(shaderProgram1);
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
	glDeleteShader(fragmentShader1);
	// ---------------------------------------
	// 着色器程序对象创建完成


	// 链接顶点属性--告诉GPU解释顶点数据的方法
	// ----------------------------------------
		// 创建初始的顶点数组
	float vertices[] = {
		-1.f, 0.0f, 0.0f,   // 左1
		-0.5f, 0.5f, 0.0f,  // 左2
		0.0f, 0.0f, 0.0f, // 左3
	};

	float vertices1[] = {
		// 第二个三角形
		0.0f, 0.0f, 0.0f, // 左3
		0.5f, 0.5f, 0.0f,   // 左4
		1.0f, 0.0f, 0.0f // 左5
	};

	// 创建VAO和VBO
	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);


	// 绑定VAO
	glBindVertexArray(VAOs[0]);
	// 绑定VBO,复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 绑定VAO
	glBindVertexArray(VAOs[1]);
	// 绑定VBO,复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	// 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 结束之后删除相关的内存占用
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

