#include <GLFW/glfw3.h> 
#include <iostream> usingnamespacestd;
intmain(void)  {
	GLFWwindow*window;
	/* Inicializa a biblioteca */
	if(!glfwInit()) return-1;
	/* Criaumajanela com contexto OpenGL */
	window =glfwCreateWindow(640,480,"Hello World",NULL,NULL);
	if(!window) {
		glfwTerminate();
		return-1;
	}
	/* Ativa o contexto OpenGL najanela */
	glfwMakeContextCurrent(window);
	/* Rodaatéque o usuáriofeche a janela */
	while(!glfwWindowShouldClose(window)){
		/* Código de renderizaçãoOpenGL vai aqui */
		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);
		/* Captura e trataeventos do teclado */
		glfwPollEvents();
	}
	glfwTerminate();
	return0;
}

