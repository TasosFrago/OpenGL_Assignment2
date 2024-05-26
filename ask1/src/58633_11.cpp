#include <iostream>
#include <cmath>
#include <cstdint>

#ifndef GLEW_GUARD_H
#define GLEW_GUARD_H
#include <GL/glew.h>
#endif // GLEW_GUARD_H

#include "lib/windowGlfw.h"
#include "lib/dbg_assert.h"
#include "lib/shader_utl.h"
#include "lib/vertexArray/vao.h"

#define WIDTH 800
#define HEIGHT 600

#define AM 58633
#define U (AM % 6)

typedef enum {
	PENTAGON = 0,
	HEXAGON = 1,
	HEPTAGON = 2,
	OCTAGON = 3,
	NONAGON = 4,
	DECAGON = 5
} Polygon_t;

void generatePolygonVertices(float *vertices, int sides)
{
	float angleInc = 2.0f * M_PI / sides;
	float angle;

	for(int i = 0; i < sides; ++i) {
		angle = i * angleInc;
		vertices[i] = cos(angle);
		vertices[i+1] = sin(angle);
		vertices[i+2] = 0;
	}
}

int main()
{
	window_t window = {
		.width=WIDTH,
		.height=HEIGHT
	};
	createWindow(&window);
	DBG_ASSERT(window.win_ptr != NULL);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	VAO_t vao;
	vaoGen(&vao);
	vaoBind(&vao);
	VBO_t vbo;
	vboGen(&vbo, vertices, sizeof(vertices), GL_STATIC_DRAW);

	VBLayout_t vbl = {};
	vbl_new(&vbl);
	vbl_push_float(&vbl, 3);

	vaoAddBuffer(&vao, &vbo, &vbl);
	DBG_GLCHECKERROR();

	vbl_destroy(&vbl);

	// uint32_t VBO, VAO;
	// glGenVertexArrays(1, &VAO);
	// glBindVertexArray(VAO);

	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t shader = shaderLoadProgram("./shaders/testVertexShader.glsl", "./shaders/testFragmentShader.glsl");
	DBG_ASSERT(shader != 0);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void *)0);
	// glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window.win_ptr)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		// glBindVertexArray(VAO);
		vaoBind(&vao);
		DBG_GLCHECKERROR();

		glDrawArrays(GL_TRIANGLES, 0, 3);
		DBG_GLCHECKERROR();

		glfwSwapBuffers(window.win_ptr);
		glfwPollEvents();
	}
	vaoDelete(&vao);

	destroyWindow(&window);

	return 0;
}
