#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

struct vertice {
	float x, y, r, g, b;
};
#include <iostream>
string readFile(string filename) {
  ifstream f(filename);
  stringstream buffer;
  buffer << f.rdbuf();
	cerr << buffer.str() << endl;
  return buffer.str();
}

int main() {
	if (!glfwInit()) return -1;
	
	GLFWwindow *window = glfwCreateWindow(600, 600, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) return -1;

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

	GLuint myIBO;
	glGenBuffers(1, &myIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertice), (void*)8);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

  auto vertexShaderText = readFile("vertex.sdr").c_str();
  auto fragmentShaderText = readFile("fragment.sdr").c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
  glCompileShader(fragmentShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window)) {

		/* Código de renderização OpenGL vai aqui */

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, (GLvoid*)0);

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);

		/* Captura e trata eventos do teclado */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
