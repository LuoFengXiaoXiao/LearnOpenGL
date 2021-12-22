

#include "Common.h"

// ���ô��ڵĴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// ������ɫ��--�о�����д��ɵ
// ��ɫ����������λ������Ϊ1
// ��Ƭ����ɫ�����һ����ɫ
/*

#version 330 core
layout (location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0
layout (location = 1) in vec3 aColor; // ��ɫ����������λ��ֵΪ 1

out vec3 ourColor; // ��Ƭ����ɫ�����һ����ɫ

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = aColor; // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
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


// Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor,1.0f);\n"
"}\n";



int main()
{
	// ��ʼ��������glfw
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

	// ������ɫ���������
	// ------------------------------------
	// ����������ɫ��
	//  ---------------------
	// ����һ��������ɫ������
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// ���붥����ɫ���Ĵ���
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// ���붥����ɫ��
	glCompileShader(vertexShader);
	// �ж���ɫ���ı�����
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//  ----------------------
	// ������ɫ���������
	// ����Ƭ����ɫ��
	//  ----------------------
	// ����һ��Ƭ����ɫ������
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// ����Ƭ����ɫ���Ĵ���
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// ����Ƭ����ɫ��
	glCompileShader(fragmentShader);
	// �жϱ�����
	glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//  -----------------------
	// Ƭ����ɫ���������
	// ������ɫ��������󣬲���������ɫ����Ƭ����ɫ�����ӵ���ɫ���������
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// ������ɫ��
	glLinkProgram(shaderProgram);
	// �ж����ӽ��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// ��������ɫ����Ƭ����ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// ---------------------------------------
	// ��ɫ��������󴴽����


	// ���Ӷ�������--����GPU���Ͷ������ݵķ���
	// ----------------------------------------
	// ������ʼ�Ķ�������
	float vertices[] = {
		// λ��              // ��ɫ
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
	};

	// ����VAO��VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ��VAO
	glBindVertexArray(VAO);
	// ��VBO,���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���ö���λ������ָ��
	// �ô������һ��λ��Ϊλ��ƫ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ���ö�����ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	// ���ƿ�ֵ�������鵽�����У�Ϊ���Ժ�ȫ�ؽ����
	// ��VAO��VBO���ݵ���λ�þ�����Ϊ��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// --------------------------------
	// �����������

	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ����������
		glUseProgram(shaderProgram);
		// ֻ��һ��VAO�����Բ���Ҫÿ�ζ�ȥ�󶨣����ǰ󶨿���ʹ�����������
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ����֮��ɾ����ص��ڴ�ռ��
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

