#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main(void)  {
	GLFWwindow *window;

	/* Inicializa a biblioteca */
	if(!glfwInit()) return-1;

	/* Cria uma janela com contexto OpenGL */
	window = glfwCreateWindow(640,480,"Atividade 00",NULL,NULL);
	if(!window) {
		glfwTerminate();
		return-1;
	}

	/* Ativa o contexto OpenGL na janela */
	glfwMakeContextCurrent(window);

	double x = 0, y = 0;
	double vx = 0.01, vy = 0.005;

	/* Roda até que o usuário feche a janela */
	while(!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0, 0, 1);

		glBegin(GL_TRIANGLES);
			glVertex2f(x - 0.5f, y - 0.5f);
			glVertex2f(x, y + 0.5f);
			glVertex2f(x + 0.5f, y - 0.5f);
		glEnd();

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);
		/* Captura e trata eventos do teclado */
		glfwPollEvents();

		if (x + vx > 0.5 or x + vx < -0.5) vx *= -1;
		if (y + vy > 0.5 or y + vy < -0.5) vy *= -1;
		x += vx;
		y += vy;
	}
	glfwTerminate();
	return 0;
}

