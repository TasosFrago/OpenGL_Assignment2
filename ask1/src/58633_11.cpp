#include <iostream>
#include <cmath>

#include "../../lib/windowGlfw.h"
#include "../../lib/dbg_assert.h"

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

	while(!glfwWindowShouldClose(window.win_ptr)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window.win_ptr);
		glfwPollEvents();
	}

	destroyWindow(&window);

	return 0;
}
