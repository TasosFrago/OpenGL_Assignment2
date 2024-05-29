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

// Imgui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "lib/windowGlfw.h"
#include "lib/dbg_assert.h"
#include "lib/shader_utl.h"
#include "lib/vertexArray/vao.h"

#define WIDTH 800
#define HEIGHT 800


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

	uint32_t shader = shaderLoadProgram("./ask3/shaders/VertexShader_13.glsl", "./ask3/shaders/FragmentShader_13.glsl");
	DBG_ASSERT(shader != 0);

	GLfloat vertices[] = {
		//position
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	GLfloat colors[] = {
		//color
		1.0f, 0.0f, 0.0,
		1.0f, 0.0f, 0.0,
		1.0f, 0.0f, 0.0,
		1.0f, 0.0f, 0.0,
		1.0f, 0.0f, 0.0,
		1.0f, 0.0f, 0.0,

		0.0f, 1.0f, 0.0,
		0.0f, 1.0f, 0.0,
		0.0f, 1.0f, 0.0,
		0.0f, 1.0f, 0.0,
		0.0f, 1.0f, 0.0,
		0.0f, 1.0f, 0.0,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,

		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,
		0.0f, 0.0f, 0.5f,

		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f
	};

	VAO_t vao;
	vaoGen(&vao);
	vaoBind(&vao);

	VBO_t *vbo = (VBO_t *)malloc(sizeof(VBO_t) * 2);
	vboGen(&vbo[0], vertices, sizeof(vertices), GL_STATIC_DRAW);
	vboGen(&vbo[1], colors, sizeof(colors), GL_STATIC_DRAW);

	VBLayout_t vbl;
	vbl_new(&vbl, 3 * sizeof(float));
	vbl_push_float(&vbl, 3);
	vbl_push_float(&vbl, 3);

	vaoAddBufferM(&vao, vbo, &vbl);
	DBG_GLCHECKERROR();

	vbl_destroy(&vbl);
	free(vbo);

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while(!glfwWindowShouldClose(window.win_ptr)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Change Colors");
		// ImGui::SeparatorText("Polygon 1");
		// static float R = 0, G = 1.0f, B = 0;
		// ImGui::SliderFloat("R", &R, 0.0f, 1.0f);
		// ImGui::SliderFloat("G", &G, 0.0f, 1.0f);
		// ImGui::SliderFloat("B", &B, 0.0f, 1.0f);

		// ImGui::SeparatorText("Polygon 2");
		// static float R1 = 1.0f, G1 = 0, B1 = 0;
		// ImGui::SliderFloat("R1", &R1, 0.0f, 1.0f);
		// ImGui::SliderFloat("G1", &G1, 0.0f, 1.0f);
		// ImGui::SliderFloat("B1", &B1, 0.0f, 1.0f);
		ImGui::End();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		// vaoBind(&vao);

		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

		// 3D projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(70.0f), 800.0f/600.0f, 0.3f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);


		// Model
		glm::mat4 model;
		model = glm::translate(identity, glm::vec3(0, 0, 0));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window.win_ptr);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	vaoDelete(&vao);
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
