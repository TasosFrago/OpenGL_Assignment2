#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstring>

#ifndef GLEW_GUARD_H
#define GLEW_GUARD_H
#include <GL/glew.h>
#endif // GLEW_GUARD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "polygon.h"

#include "lib/windowGlfw.h"
#include "lib/dbg_assert.h"
#include "lib/shader_utl.h"
#include "lib/vertexArray/vao.h"

#define WIDTH 800
#define HEIGHT 800

#define AM 58633
#define U (AM % 6)


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


int main()
{
	window_t window = {
		.width=WIDTH,
		.height=HEIGHT
	};
	createWindow(&window, key_callback);
	DBG_ASSERT(window.win_ptr != NULL);

	// Set Window state for toogling tab key
	bool isPressed = false;
	glfwSetWindowUserPointer(window.win_ptr, (void *)&isPressed);
	glfwSetKeyCallback(window.win_ptr, key_callback);

	struct PolygonIDs ids = getPolygonTypes(U);

	// uint32_t shader = shaderLoadProgram("./shaders/testVertexShader.glsl", "./shaders/testFragmentShader.glsl");
	uint32_t shader = shaderLoadProgram("./ask1/shaders/VertexShader_11.glsl", "./ask1/shaders/FragmentShader_11.glsl");
	DBG_ASSERT(shader != 0);

	VAO_t vao[2];

	// First Polygon
	vaoGen(&vao[0]);
	vaoBind(&vao[0]);

	int len1;
	float *polygon1Verts = genPolygonVerts({ .x=0.5f, .y=0.5f, .radius=0.3f }, ids.ID1, &len1);
	float *polygon1Colors = genPolygonColors(len1, 1.0f, 0, 0);

	VBO_t *vbo1 = (VBO_t *)malloc(sizeof(VBO_t) * 2);
	// VBO_t *vbo1 = new VBO_t[3];
	vboGen(&vbo1[0], polygon1Verts, sizeof(float) * len1, GL_STATIC_DRAW);
	vboGen(&vbo1[1], polygon1Colors, sizeof(float) * len1, GL_STATIC_DRAW);

	free(polygon1Verts);
	free(polygon1Colors);

	VBLayout_t vbl1;
	vbl_new(&vbl1, 3 * sizeof(float));
	vbl_push_float(&vbl1, 3);
	vbl_push_float(&vbl1, 3);

	vaoAddBufferM(&vao[0], vbo1, &vbl1);
	DBG_GLCHECKERROR();

	free(vbo1);
	vbl_destroy(&vbl1);

	// Second Polygon
	vaoGen(&vao[1]);
	vaoBind(&vao[1]);

	int len2;
	float *polygon2Verts = genPolygonVerts({ .x=-0.5f, .y=-0.5f, .radius=0.3f }, ids.ID2, &len2);
	float *polygon2Colors = genPolygonColors(len2, 0, 0, 1.0f);

	VBO_t *vbo2 = (VBO_t *)malloc(sizeof(VBO_t) * 2);
	vboGen(&vbo2[0], polygon2Verts, sizeof(float) * len2, GL_STATIC_DRAW);
	vboGen(&vbo2[1], polygon2Colors, sizeof(float) * len2, GL_STATIC_DRAW);

	free(polygon2Verts);
	free(polygon2Colors);

	VBLayout_t vbl2;
	vbl_new(&vbl2, 3 * sizeof(float));
	vbl_push_float(&vbl2, 3);
	vbl_push_float(&vbl2, 3);

	vaoAddBufferM(&vao[1], vbo2, &vbl2);
	DBG_GLCHECKERROR();

	free(vbo2);
	vbl_destroy(&vbl2);

	// VAO_t vao;
	// vaoGen(&vao);
	// vaoBind(&vao);
	// VBO_t vbo;
	// vboGen(&vbo, vertices, sizeof(float) * len, GL_STATIC_DRAW);

	// free(vertices);

	// VBLayout_t vbl;
	// vbl_new(&vbl, 3 * sizeof(float));
	// vbl_push_float(&vbl, 3);

	// vaoAddBuffer(&vao, &vbo, &vbl);
	// DBG_GLCHECKERROR();

	// vbl_destroy(&vbl);
	//-------

	// uint32_t VBO, VAO;
	// glGenVertexArrays(1, &VAO);
	// glBindVertexArray(VAO);

	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (len), vertices, GL_STATIC_DRAW);

	// free(vertices);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);
	// glEnableVertexAttribArray(0);


	while(!glfwWindowShouldClose(window.win_ptr)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		// Polygon 1
		vaoBind(&vao[0]);
		DBG_GLCHECKERROR();

		glUniform3f(glGetUniformLocation(shader, "overideColor"), 0, 1.0f, 0);
		glDrawArrays(GL_TRIANGLES, 0, len1);
		DBG_GLCHECKERROR();


		// Polygon 2
		vaoBind(&vao[1]);
		DBG_GLCHECKERROR();

		glUniform3f(glGetUniformLocation(shader, "overideColor"), 1.0f, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, len2);
		DBG_GLCHECKERROR();

		glfwSwapBuffers(window.win_ptr);
		glfwPollEvents();
	}
	vaoDelete(&vao[0]);

	destroyWindow(&window);

	return 0;
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		// Get the globall state of the <TAB> key
		bool *isPressed;
		isPressed = (bool *)glfwGetWindowUserPointer(window);
		if(*isPressed) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			*isPressed = !(*isPressed);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			*isPressed = !(*isPressed);
		}
		glfwSetWindowUserPointer(window, (void *)isPressed);
	}
	// Closs Window with ESC
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}
