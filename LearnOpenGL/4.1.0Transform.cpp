#include "Common.h"
#include "Shader.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Texture/stb_image.h"



// ���ô��ڵĴ�С
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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

	// ʹ��Shader���ȡ��ɫ��
	Shader ourShader("shader/VertexShader/Triangle.vs", "shader/FragShader/Triangle.fs");


	// ��������������id
	unsigned int texture;
	glGenTextures(1, &texture);
	// ������
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ��������
	int width, height, nrChannels;
	unsigned char* data = stbi_load("../Resource/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// ��������
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// ���ɽ�������
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Load texture succeed!!!" << std::endl;
	}
	else
		std::cout << "Failed to load texture" << std::endl;

	// �ͷż��������ڴ�
	stbi_image_free(data);

	// ���Ӷ�������--����GPU���Ͷ������ݵķ���
	// ----------------------------------------
	// ������ʼ�Ķ�������
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	// ����VAO��VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// ��VAO
	glBindVertexArray(VAO);
	// ��VBO,���ƶ������鵽�����й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ����ͼ
	glBindTexture(GL_TEXTURE_2D, texture);
	// ���ö���λ������ָ��
	// �ô������һ��λ��Ϊλ��ƫ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ���ö�����ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// �������������ָ��
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// ���ƿ�ֵ�������鵽�����У�Ϊ���Ժ�ȫ�ؽ����
	// ��VAO��VBO���ݵ���λ�þ�����Ϊ��
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	// --------------------------------
	// �����������

	/*�����任����
		glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
		glm::mat4 trans;
		// ��Ҫ��ʼ�������������Ϊ��Сֵ
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
		vec = trans * vec;
		std::cout << "vec.x: " << vec.x << "  vec.y: " << vec.y << "  vec.z: " << vec.z << std::endl;
	*/


	// ��ת������
	/*
		glm::mat4 trans=glm::mat4(1.0f);
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	*/


	// ��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		float timeValue = glfwGetTime();
		//float greenValue = sin(timeValue);

		//ourShader.setFloat("xOffset", greenValue);
		glBindTexture(GL_TEXTURE_2D, texture);

		// transform and rotate
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));


		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



		// ����������
		ourShader.use();
		// ֻ��һ��VAO�����Բ���Ҫÿ�ζ�ȥ�󶨣����ǰ󶨿���ʹ�����������
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ����֮��ɾ����ص��ڴ�ռ��
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//ɾ��shader��program���ڴ�ռ��
	ourShader.deleteProgram();

	glfwTerminate();
	return 0;
}

