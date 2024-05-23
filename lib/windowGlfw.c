#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include "windowGlfw.h"
#include "dbg_assert.h"


void FrameBufferSizeCallback(GLFWwindow *, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// Closs Window with ESC
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void error_callback(int error, const char *description)
{
	DBG_LOG_VAR(description, ERROR);
}

void createWindow(window_t *window)
{
	window->win_ptr = 0;
	DBG_ASSERT(window->width > 100 && window->height >100);

	if(!glfwInit()) {
		DBG_LOG("Failed to initialize glfw.\n", ERROR);
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window->win_ptr = glfwCreateWindow(window->width, window->height, "Conway's Game of Life", NULL, NULL);

	if(!window) {
		DBG_LOG("Failed to initialize window.\n", ERROR);
		exit(-1);
	}

	glfwMakeContextCurrent(window->win_ptr);

	glfwSetFramebufferSizeCallback(window->win_ptr, FrameBufferSizeCallback);

	if(glewInit() != GLEW_OK) {
		DBG_LOG("Failed to initialize glew.\n", ERROR);
		glfwTerminate();
		exit(-1);
	}

	glfwSetKeyCallback(window->win_ptr, key_callback);
	glfwSetErrorCallback(error_callback);
}

void destroyWindow(window_t *window)
{
	if(window) {
		glfwDestroyWindow(window->win_ptr);
		glfwTerminate();
		free(window);
	}
}
