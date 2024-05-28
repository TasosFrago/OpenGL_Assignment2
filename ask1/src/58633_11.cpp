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

// Imgui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

	// Setub Imgui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Setup Platform backends
	ImGui_ImplGlfw_InitForOpenGL(window.win_ptr, true);
	ImGui_ImplOpenGL3_Init();

	struct PolygonIDs ids = getPolygonTypes(U);

	// uint32_t shader = shaderLoadProgram("./shaders/testVertexShader.glsl", "./shaders/testFragmentShader.glsl");
	uint32_t shader = shaderLoadProgram("./ask1/shaders/VertexShader_11.glsl", "./ask1/shaders/FragmentShader_11.glsl");
	DBG_ASSERT(shader != 0);

	VAO_t vao[2];

	// First Polygon
	// ------------
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
	// ------------
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


	while(!glfwWindowShouldClose(window.win_ptr)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// ImGui::ShowDemoWindow();
		ImGui::SeparatorText("Polygon 1");
		static float R = 0, G = 1.0f, B = 0;
		ImGui::SliderFloat("R", &R, 0.0f, 1.0f);
		ImGui::SliderFloat("G", &G, 0.0f, 1.0f);
		ImGui::SliderFloat("B", &B, 0.0f, 1.0f);

		ImGui::SeparatorText("Polygon 2");
		static float R1 = 1.0f, G1 = 0, B1 = 0;
		ImGui::SliderFloat("R1", &R1, 0.0f, 1.0f);
		ImGui::SliderFloat("G1", &G1, 0.0f, 1.0f);
		ImGui::SliderFloat("B1", &B1, 0.0f, 1.0f);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		// Polygon 1
		vaoBind(&vao[0]);
		DBG_GLCHECKERROR();

		glUniform3f(glGetUniformLocation(shader, "overideColor"), R, G, B);
		glDrawArrays(GL_TRIANGLES, 0, len1);
		DBG_GLCHECKERROR();


		// Polygon 2
		vaoBind(&vao[1]);
		DBG_GLCHECKERROR();

		glUniform3f(glGetUniformLocation(shader, "overideColor"), R1, G1, B1);
		glDrawArrays(GL_TRIANGLES, 0, len2);
		DBG_GLCHECKERROR();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window.win_ptr);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	vaoDelete(&vao[0]);
	vaoDelete(&vao[1]);
	destroyWindow(&window);

	return 0;
}


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_W && action == GLFW_PRESS) {
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
