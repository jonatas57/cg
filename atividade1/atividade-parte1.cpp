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
	
	GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) return -1;

	vertice v[] = {
		{ 0.0,  0.5, 1, 0, 0},
		{-0.5, -0.5, 0, 1, 0},
		{ 0.5, -0.5, 0, 0, 1}
	};

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
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);

		/* Captura e trata eventos do teclado */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
