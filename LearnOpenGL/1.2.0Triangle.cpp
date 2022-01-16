

#include "Common.h"

// ���ô��ڵĴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// ������ɫ��--�о�����д��ɵ
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n";

// Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
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
		-0.5f,-0.5f,0.0f,//left
		0.5f,-0.5f,0.0f,//right
		0.0f,0.5f,0.0f//top
	};

	// ����VAO��VBO
	// VBO ��Ŀ����Ϊ���еĶ������ݴ�����һ���ڴ棬�������ڴ�ĵ�ַ
	// VAO ��VBO�д洢�����ݽ��з��飬ȷ��ÿ�����ݵı�ʾ���ݣ���������Ӧ���ڴ��ַ
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// ��VAO
	glBindVertexArray(VAO);
	// ��VBO,���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
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

