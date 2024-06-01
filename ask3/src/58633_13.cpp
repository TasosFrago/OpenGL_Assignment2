#include <iostream>
#include <cstdint>
#include <string>

#ifndef GLEW_GUARD_H
#define GLEW_GUARD_H
#include <GL/glew.h>
#endif // GLEW_GUARD_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

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

glm::mat4 updateModelTrans1(float speed1, float speed2, bool rotation1, bool rotation2, float deltaTime, float radius, glm::mat4 &rotationTrans, glm::mat4 &spinTrans)
{
	glm::mat4 identity(1.0f);
	glm::mat4 model2Spin = glm::rotate(identity, speed2 * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 model2Rotation = glm::rotate(identity, speed1 * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 model2Trans = glm::translate(identity, glm::vec3(radius, 0.0f, 0.0f));
	glm::mat4 model2Scale = glm::scale(identity, glm::vec3(0.5f, 0.5f, 0.5f));

	if(rotation1) {
		rotationTrans = model2Rotation * rotationTrans;
	}
	if(rotation2) {
		spinTrans = model2Spin * spinTrans;
	}
	return (model2Scale * rotationTrans * model2Trans * spinTrans);
}


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

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	glm::mat4 model1, model2 = identity, rotation1;
	float modelSpeed[5] = { 2.4f, 2.4f, 2.4f, 2.4f, 2.4f};
	bool rotation[5] = { 1, 1, 1, 1, 1 };
	float radius12 = 5.0f;
	float radius23 = 0.1f;
	glm::mat4 currentTrans = identity;
	glm::mat4 currentTrans2 = identity;
	glm::mat4 currentTrans3 = identity;
	glm::mat4 currentTrans4 = identity;

	glm::mat4 currTrans2;
	glm::mat4 model2Tmp;
	glm::mat4 model2Trans1 = identity;
	glm::mat4 model2Trans2 = identity;

	while(!glfwWindowShouldClose(window.win_ptr)) {
		glfwPollEvents();

		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// ImGui Configuration
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Options");
			ImGui::SliderFloat("radius12", &radius12, 0.2f, 6.0f);
			ImGui::SliderFloat("radius23", &radius23, 0.2f, 6.0f);
			ImGui::SeparatorText("Speed and Rotation");
			for(int i = 0; i < 5; i++) {
				std::string label1 = "Speed" + std::to_string(i);
				std::string label2 = "Rotation" + std::to_string(i);
				ImGui::SliderFloat(label1.c_str(), &modelSpeed[i], 1.0f, 15.0f);
				ImGui::SameLine();
				ImGui::Checkbox(label2.c_str(), &rotation[i]);
			}
			ImGui::End();
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		vaoBind(&vao);


		glm::mat4 view;
		view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

		// 3D projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(90.0f), (float)(WIDTH)/(float)(HEIGHT), 0.1f, 100.0f);

		// 2D projection
		// projection = glm::ortho(-5.0f, 5.0f, -6.0f, 6.0f, -15.0f, 18.0f); // the values were chosen to fit the cube positions in each axis
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);


		// Model1
		glm::mat4 model1Trans = glm::translate(identity, glm::vec3(0, 0, 0));
		glm::mat4 model1Spin = glm::rotate(identity, modelSpeed[0] * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 model1Scale = glm::scale(identity, glm::vec3(0.5f, 0.5f, 0.5f));

		if(rotation[0]) {
			model1 = model1Scale * model1Spin * model1Trans;
		} else {
			model1 = model1Scale * model1Trans;
		}

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model1[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));

		//******Model 2******
		model2 = updateModelTrans1(modelSpeed[1], modelSpeed[2], rotation[1], rotation[2], deltaTime, radius12, currentTrans, currentTrans2);

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model2[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));

		model2Tmp = updateModelTrans1(modelSpeed[1], modelSpeed[2], rotation[1], 0, deltaTime, radius12, model2Trans1, model2Trans2);

		glm::mat4 model3 = model2Tmp * updateModelTrans1(modelSpeed[3], modelSpeed[4], rotation[3], rotation[4], deltaTime, radius23, currentTrans3, currentTrans4);

		// glm::mat4 model3 = model2Tmp * model3Scale * currentTrans3 * model3Trans * currentTrans4;

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model3[0][0]);

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

                // glm::mat4 model3Spin = glm::rotate(identity, modelSpeed[3] * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// glm::mat4 model3Rotation = glm::rotate(identity, modelSpeed[4] * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// glm::mat4 model3Trans = glm::translate(identity, glm::vec3(radius23, 0.0f, 0.0f));
		// glm::mat4 model3Scale = glm::scale(identity, glm::vec3(0.5f, 0.5f, 0.5f));

		// if(rotation[3]) {
		// 	currentTrans3 = model3Rotation * currentTrans3;
		// }
		// if(rotation[4]) {
		// 	currentTrans4 = model3Spin * currentTrans4;
		// }
		// model3 = model3Scale * currentTrans3 * model3Trans * currentTrans4 * glm::translate(model2, glm::vec3(2.0f, 0.0f, 0.0f));

		// glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model3[0][0]);
		// glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));
		// Model 3
		// model3Trans1 = glm::translate((model2), glm::vec3(2.0f, 0.0f, 0.0f));
		// model3Spin = glm::rotate(identity , modelSpeed[3] * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// model3Trans2 = glm::translate(identity, glm::vec3(radius23, 0.0f, 0.0f));
		// model3Rotation = glm::rotate(identity, modelSpeed[4] * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// model3Scale = glm::scale(identity, glm::vec3(0.5f, 0.5f, 0.5f));

		// model3 = glm::translate(model2, glm::vec3(2.0f, 0.0f, 0.0f));
		// model3 = glm::rotate(model3, modelSpeed[3] * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// model3 = glm::translate(model3, glm::vec3(radius23, 0.0f, 0.0f));
		// model3 = glm::rotate(model3, modelSpeed[4] * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
		// model3 = glm::scale(model3, glm::vec3(0.5f, 0.5f, 0.5f));

		// model3 = model3Scale * model3Rotation * model3Trans2 * model3Spin * model3Trans1;
