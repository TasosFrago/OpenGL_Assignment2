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

// Define AEM
#define A (1.6f)
#define B (1.3f)
#define C (1.3f)

#define SCALE_M(S) glm::vec3(S, S, S)


static GLfloat vertices[] = {
	//position           //color
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0,
	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
	0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0,
	-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0,
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0,

	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0,
	0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0,
	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
	0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0,
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0,
	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0,

	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

	0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 0.5f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.5f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f, 0.5f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
	0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.5f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f,
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,

	-0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

struct CubeRotationAttribs {
	float RotationSpeed;
	float SpinSpeed;
	bool RotationToggle;
	bool SpinToggle;
	float RotationRadius;
	glm::vec3 scaleVec;
};
glm::mat4 updateModelTrans(CubeRotationAttribs attrb, glm::mat4 &rotationTrans, glm::mat4 &spinTrans, float deltaTime)
{
	glm::mat4 identity(1.0f);
	glm::mat4 model2Spin = glm::rotate(identity, attrb.SpinSpeed * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 model2Rotation = glm::rotate(identity, attrb.RotationSpeed * deltaTime, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 model2Trans = glm::translate(identity, glm::vec3(attrb.RotationRadius + 2.0f, 0.0f, 0.0f));
	glm::mat4 model2Scale = glm::scale(identity, attrb.scaleVec);

	if(attrb.RotationToggle) {
		rotationTrans = model2Rotation * rotationTrans;
	}
	if(attrb.SpinToggle) {
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
	createWindow(&window);
	glfwSetKeyCallback(window.win_ptr, key_callback);
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

	VAO_t vao;
	vaoGen(&vao);
	vaoBind(&vao);

	VBO_t vbo;
	vboGen(&vbo, vertices, sizeof(vertices), GL_STATIC_DRAW);

	VBLayout_t vbl;
	vbl_new(&vbl, 6 * sizeof(float));
	vbl_push_float(&vbl, 3);
	vbl_push_float(&vbl, 3);

	vaoAddBuffer(&vao, &vbo, &vbl);
	DBG_GLCHECKERROR();

	vbl_destroy(&vbl);
	// free(vbo);

	glm::mat4 identity = glm::mat4(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float modelSpeed[5] = { 2.4f, 2.4f, 2.4f, 2.4f, 2.4f};
	bool rotation[5] = { 1, 1, 1, 1, 1 };
	float radius12 = 5.0f;
	float radius23 = 0.1f;
	static int cameraPos = 1;
	static float zoom = 90.0f;

	glm::mat4 currentTrans1 = identity;
	glm::mat4 currentTrans2 = identity;
	glm::mat4 currentTrans3 = identity;
	glm::mat4 currentTrans4 = identity;

	glm::mat4 model2Trans1 = identity;
	glm::mat4 model2Trans2 = identity;
	glm::mat4 model1Trans = identity;

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
			ImGui::SeparatorText("Camera");
			ImGui::RadioButton("Orthographic view", &cameraPos, 0);
			ImGui::RadioButton("Projection 1", &cameraPos, 1); ImGui::SameLine();
			ImGui::RadioButton("Projection 2", &cameraPos, 2);
			ImGui::DragFloat("zoom", &zoom, 5.0f, 5.0f, 160.0f);
			ImGui::End();
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderUse(shader);
		DBG_GLCHECKERROR();

		vaoBind(&vao);
		DBG_GLCHECKERROR();

		glm::mat4 view;

		glm::mat4 projection;

		switch(cameraPos) {
		// 2D projection
		case 0:
			// the values were chosen to fit the cube positions in each axis
			view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -13.0f));
			projection = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f, -13.0f, 13.0f);
			break;
		// 3D projection
		case 1:
			view = glm::translate(identity, glm::vec3(0.0f, 0.0f, -13.0f));
			projection = glm::perspective(glm::radians(zoom), (float)(WIDTH)/(float)(HEIGHT), 0.1f, 100.0f);
			break;
		case 2:
			glm::vec3 cameraPos = glm::vec3(-10.0f, 0.0f, 13.0f);
			glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 cameraUp = glm::vec3(1.0f, 0.0f, 0.0f);
			view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
			projection = glm::perspective(glm::radians(zoom), (float)(WIDTH)/(float)(HEIGHT), 0.1f, 100.0f);
			break;
		}

		glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);

		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);


		//******Model-1******
		{
			glm::mat4 tmp(1.0f);
			glm::mat4 model1 = updateModelTrans((CubeRotationAttribs){
								.RotationSpeed=1.0f,
								.SpinSpeed=modelSpeed[0],
								.RotationToggle=false,
								.SpinToggle=rotation[0],
								.RotationRadius=(-2.0f),
								.scaleVec=SCALE_M(A)
							}, tmp, model1Trans, deltaTime);

			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model1[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));
		}

		//******Model-2******
		{
			glm::mat4 model2 = updateModelTrans((CubeRotationAttribs){
								.RotationSpeed=modelSpeed[1],
								.SpinSpeed=modelSpeed[2],
								.RotationToggle=rotation[1],
								.SpinToggle=rotation[2],
								.RotationRadius=radius12,
								.scaleVec=SCALE_M(B)
							}, currentTrans1, currentTrans2, deltaTime);

			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model2[0][0]);
			// Draw the model
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));
		}

		//******Model-3******
		{
			/*
			 * Recompute the matrix of model 2 but with the spin disabled,
			 * and without the scale so it doesn't add up to model3's tansformation
			 */
			glm::mat4 model2Tmp = updateModelTrans((CubeRotationAttribs){
									.RotationSpeed=modelSpeed[1],
									.SpinSpeed=0,
									.RotationToggle=rotation[1],
									.SpinToggle=0,
									.RotationRadius=radius12,
									.scaleVec=SCALE_M(B)
								}, model2Trans1, model2Trans2, deltaTime);
			model2Tmp *= glm::inverse(glm::scale(identity, SCALE_M(B)));

			glm::mat4 model3 = model2Tmp * updateModelTrans((CubeRotationAttribs){
										.RotationSpeed=modelSpeed[3],
										.SpinSpeed=modelSpeed[4],
										.RotationToggle=rotation[3],
										.SpinToggle=rotation[4],
										.RotationRadius=radius23,
										.scaleVec=SCALE_M(C)
									}, currentTrans3, currentTrans4, deltaTime);

			glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model3[0][0]);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(vertices[0]));
		}

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
