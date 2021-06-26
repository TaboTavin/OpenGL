#include <iostream>
#include <sstream>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"



const char* APP_TITLE = "My OpenGL App";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
bool gFullscreen = false;

// Function prototype that listens to Keyborad input
void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mode);

// Function prototype that show our FPS 
void showFPS(GLFWwindow* window);


int main()
{
	// This verifies if glfw starts correctly 
	if (!glfwInit())
	{
		std::cerr << "GLFW Init failed" << std::endl;
		return -1;
	}

	// We delimit the version of OpenGL that is going to be used in the project
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// We define the type of profile that is going to be used in the project, in this case -> Modern OpenGL (We can NOT use obsolete methods of other versions of OpenGL)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// We define compatibility with other versions of OpenGL
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// We create the apps window and a pointer to refernce the window.
	// We verified if full screen bool is true and if it is, we choose the main monitor to deploy the app on full screen
	GLFWwindow* pWindow = NULL;

	if (gFullscreen)
	{
		GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* pVmode = glfwGetVideoMode(pMonitor);

		if (pVmode != NULL)
		{
			pWindow = glfwCreateWindow(pVmode->width, pVmode->height, APP_TITLE, pMonitor, NULL);
		}

	}

	// If the window is not FullScreen we pass over the Width and Height that we declared
	else
	{
		pWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	}

	// Is the window propertly created ?
	if (pWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	
	// We define our window as our actual window, we need this function to be able to draw on the window
	glfwMakeContextCurrent(pWindow);

	// Function for Keyboard Inputs
	glfwSetKeyCallback(pWindow, glfw_onKey);

	// We define glewExperimental = GL_TRUE so that OpenGL could work  
	glewExperimental = GL_TRUE;

	// We initialize GLEW so that we can acces OpenGL, GLEW retuns a GLEW_OK if this initializes Ok.
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
		return -1;
	}
	
	// glfwWindowShouldClose returns a flag that indicates the windows status
	while (!glfwWindowShouldClose(pWindow))
	{
		// Function that shows the apps FPS
		showFPS(pWindow);

		// Function that waits for an event to manipulate the window 
		glfwPollEvents();

		// Changes background color
		glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Function that swaps buffers, it removes flickers 
		glfwSwapBuffers(pWindow);

	}


	glfwTerminate();

	return 0;
}

// Function that listens to keyboard input 
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// If ESC is pressed we close the app
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	return;
}

// Function that shows the frame count on window
void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // <- Returns the number of seconds since GLFW started, as a double

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text update 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< APP_TITLE << "   "
			<< "FPS: " << fps << "  "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;

	return;
}