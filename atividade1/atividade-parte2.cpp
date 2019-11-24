#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

struct vertice {
	float x, y, r, g, b;
};

string readFile(string filename) {
  ifstream f(filename);
  stringstream buffer;
  buffer << f.rdbuf();
  return buffer.str();
}

GLuint LoadShaders(string vertex_file_path, string fragment_file_path){
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	string vertexShaderCode = readFile(vertex_file_path);
	char const * vertexSourcePointer = vertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &vertexSourcePointer , NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	string fragmentShaderCode = readFile(fragment_file_path);
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShader);

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShader);
	glAttachShader(ProgramID, fragmentShader);
	glLinkProgram(ProgramID);
	
	glDetachShader(ProgramID, vertexShader);
	glDetachShader(ProgramID, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return ProgramID;
}

int main() {
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow *window = glfwCreateWindow(640, 640, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) return -1;

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint shaderProgram = LoadShaders("vertex.sdr", "fragment.sdr");

	vertice v[] = {
		{ 0.0,  0.0, 1, 1, 1},

		{-0.2,  0.8, 0, 1, 0},
		{ 0.2,  0.8, 0, 0, 1},
		{ 0.0,  0.8, 0, 1, 1},
		{ 0.0,  1.0, 1, 0, 0},

		{-0.2, -0.8, 0, 0, 1},
		{ 0.2, -0.8, 0, 1, 0},
		{ 0.0, -0.8, 0, 1, 1},
		{ 0.0, -1.0, 1, 0, 0},

		{-0.8, -0.2, 0, 1, 0},
		{-0.8,  0.2, 0, 0, 1},
		{-0.8,  0.0, 0, 1, 1},
		{-1.0,  0.0, 1, 0, 0},

		{ 0.8, -0.2, 0, 0, 1},
		{ 0.8,  0.2, 0, 1, 0},
		{ 0.8,  0.0, 0, 1, 1},
		{ 1.0,  0.0, 1, 0, 0}
	};

	unsigned short ind[] = {
		0, 1, 3,
		0, 3, 2,
		3, 1, 4,
		3, 4, 2,

		0, 5, 7,
		0, 7, 6,
		7, 5, 8,
		7, 8, 6,

		0, 9, 11,
		0, 11, 10,
		11, 9, 12,
		11, 12, 10,

		0, 13, 15,
		0, 15, 14,
		15, 13, 16,
		15, 16, 14
	};

	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	GLuint IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)8);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window)) {

		/* Código de renderização OpenGL vai aqui */

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, sizeof(ind), GL_UNSIGNED_SHORT, (void*)0);

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);

		/* Captura e trata eventos do teclado */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
