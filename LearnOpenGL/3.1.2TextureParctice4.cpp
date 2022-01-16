

#include "Common.h"
#include "Shader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "Texture/stb_image.h"



// 设置窗口的大小
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
	// 初始化并设置glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
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


	// 生成纹理，设置其id
	unsigned int texture;
	unsigned int texture1;
	glGenTextures(1, &texture);
	// 激活纹理
	glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
	// 绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 引入纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../Resource/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// 生成渐进纹理
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Load texture succeed!!!" << std::endl;
	}
	else
		std::cout << "Failed to load texture:" << "container.jpg" << std::endl;
	// 释放加载器的内存
	stbi_image_free(data);


	glGenTextures(1, &texture1);
	// 激活纹理
	glActiveTexture(GL_TEXTURE1); // 在绑定纹理之前先激活纹理单元
	// 绑定纹理
	glBindTexture(GL_TEXTURE_2D, texture1);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data1 = stbi_load("../Resource/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data1)
	{
		// 生成纹理
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		// 生成渐进纹理
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Load texture succeed!!!" << std::endl;
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data1);

	// 链接顶点属性--告诉GPU解释顶点数据的方法
	// ----------------------------------------
	// 创建初始的顶点数组
	float vertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// 创建VAO和VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// 绑定VAO
	glBindVertexArray(VAO);
	// 绑定VBO,复制顶点数组到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 绑定贴图
	glBindTexture(GL_TEXTURE_2D, texture);
	// 设置顶点位置属性指针
	// 该处的最后一个位置为位置偏移
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 设置顶点颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 设置纹理的属性指针
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// 复制空值顶点数组到缓存中，为了以后安全地解除绑定
	// 将VAO和VBO传递到地位置均设置为空
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	// --------------------------------
	int MixFlow = 500;

	// 渲染循环
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) + 1) / 2;
			
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			MixFlow <= 0 ? 0 : (MixFlow--);
			//MixFlow = 0;
			std::cout << "MixFlow: " << MixFlow << std::endl;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			MixFlow >= 1000 ? 1000 : (MixFlow++);
			//MixFlow = 10;
			std::cout << "MixFlow: " << MixFlow << std::endl;
		}

		float MixNum = MixFlow / 1000.f;
		ourShader.setFloat("xOffset", MixNum);
		// either set it manually like so:
		glUniform1i(glGetUniformLocation(ourShader.ID, "Texture1"), 0);
		ourShader.setInt("Texture2", 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// 绘制三角形
		ourShader.use();

		// 只有一个VAO，所以不需要每次都去绑定，但是绑定可以使程序更有条理
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// 结束之后删除相关的内存占用
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//删除shader中program的内存占用
	ourShader.deleteProgram();

	glfwTerminate();
	return 0;
}

