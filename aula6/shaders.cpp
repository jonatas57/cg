#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

string readFile(string filename) {
  ifstream f(filename);
  stringstream buffer;
  buffer << f.rdbuf();
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

  return 0;
}
