#include <iostream>
#include <cstdint>
#include <cstring>

#ifndef GLEW_GUARD_H
#define GLEW_GUARD_H
#include <GL/glew.h>
#endif // GLEW_GUARD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "./ask1/src/polygon.h"

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
	createWindow(&window);
	glfwSetKeyCallback(window.win_ptr, key_callback);
	DBG_ASSERT(window.win_ptr != NULL);

	struct PolygonIDs ids = getPolygonTypes(U);

	// uint32_t shader = shaderLoadProgram("./shaders/testVertexShader.glsl", "./shaders/testFragmentShader.glsl");
	uint32_t shader = shaderLoadProgram("./ask2/shaders/VertexShader_12.glsl", "./ask2/shaders/FragmentShader_12.glsl");
	DBG_ASSERT(shader != 0);

	VAO_t vao;

	// First Polygon
	// ------------
	vaoGen(&vao);
	vaoBind(&vao);

	int len1;
	float radius = 0.3f;
	float *polygon1Verts = genPolygonVerts({ .x=0, .y=0, .radius=radius }, ids.ID1, &len1);

	VBO_t vbo1;
	vboGen(&vbo1, polygon1Verts, sizeof(float) * len1, GL_STATIC_DRAW);

	free(polygon1Verts);

	VBLayout_t vbl1;
	vbl_new(&vbl1, 3 * sizeof(float));
	vbl_push_float(&vbl1, 3);

	vaoAddBufferM(&vao, &vbo1, &vbl1);
	DBG_GLCHECKERROR();

	vbl_destroy(&vbl1);

	glm::vec3 posisition(0.0f, 0.0f, 0.0f);
	float speed = 0.025f;
	static float R = 0, G = 0;

	while(!glfwWindowShouldClose(window.win_ptr)) {
		glfwPollEvents();


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		// Polygon 1
		vaoBind(&vao);
		DBG_GLCHECKERROR();

		if(glfwGetKey(window.win_ptr, GLFW_KEY_W) == GLFW_PRESS)
			if(posisition.y < 1 - radius)
				posisition.y += speed;
		if(glfwGetKey(window.win_ptr, GLFW_KEY_S) == GLFW_PRESS)
			if(posisition.y > -1 + radius)
				posisition.y -= speed;
		if(glfwGetKey(window.win_ptr, GLFW_KEY_D) == GLFW_PRESS)
			if(posisition.x < 1 - radius - 0.01f)
				posisition.x += speed;
		if(glfwGetKey(window.win_ptr, GLFW_KEY_A) == GLFW_PRESS)
			if(posisition.x > -1 + radius + 0.01f)
				posisition.x -= speed;
		R = (posisition.x + 1)/2;
		G = (posisition.y + 1)/2;

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), posisition);

		glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
		glUniform3f(glGetUniformLocation(shader, "overideColor"), R, G, 0);
		glDrawArrays(GL_TRIANGLES, 0, len1);
		DBG_GLCHECKERROR();


		glfwSwapBuffers(window.win_ptr);
	}
	vaoDelete(&vao);
	destroyWindow(&window);

	return 0;
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// Closs Window with ESC
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}
