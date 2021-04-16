#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

const char* APP_TITLE = "Learning OpenGL";
const int gWindowWidth = 800;
const int gWindowHeight = 600;

int main()
{
	//Verificamos si inicia correctamente glfw
	if (!glfwInit())
	{
		std::cerr << "GLFW Init failed" << std::endl;
		return -1;
	}

	//Delimitamos la version de OpenGl a usar en el projecto
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Definimos el tipo de profile que vamos a utilizar, en este caso -> OpenGL moderno, sin poder hacer uso de metodos no soportados u obsoletos
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Definimos la compatiblidad con otros sistemas
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	//Creamos una ventana y una variable para guardar el pointer de la ventana
	GLFWwindow* pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (pWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Definimos nuestra ventana como la vantana actual sin este metodo no podemos dibujar nada sobre la ventana
	glfwMakeContextCurrent(pWindow);

	//Definimos glewExperimental = GL_TRUE para que funcione OpenGL
	glewExperimental = GL_TRUE;

	//Inicializamos GLEW para poder acceder a OpenGL, glew regresa un GLEW_OK si este inicia bien 
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
		return -1;
	}

	//
	while (!glfwWindowShouldClose(pWindow))
	{
		//Metodo que espera algun tipo de evento para manipular lo que esta en pantalla
		glfwPollEvents();

		//Metodo para hacer un swap de buffers, elimina flickers
		glfwSwapBuffers(pWindow);

	}


	glfwTerminate();
	return 0;
}
