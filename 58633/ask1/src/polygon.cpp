#include <cstdlib>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "polygon.h"


struct PolygonIDs getPolygonTypes(int U)
{
	struct PolygonIDs ids;
	switch(U) {
	case 0:
		ids = { .ID1=PENTAGON, .ID2=HEPTAGON };
		break;
	case 1:
		ids = { .ID1=HEXAGON, .ID2=OCTAGON };
		break;
	case 2:
		ids = { .ID1=HEPTAGON, .ID2=NONAGON };
		break;
	case 3:
		ids = { .ID1=OCTAGON, .ID2=DECAGON };
		break;
	case 4:
		ids = { .ID1=NONAGON, .ID2=PENTAGON };
		break;
	case 5:
		ids = { .ID1=DECAGON, .ID2=HEXAGON };
		break;
	}
	return ids;
}

float *genPolygonVerts(struct coordinates coords, int vCount, int *len)
{
	float angle = 360.0f / vCount;

	int triangleCount = vCount - 2;

	float *tmp = (float *)calloc(sizeof(float) * vCount, 3);
	// positions
	for (int i = 0; i < vCount; i++) {
		float currentAngle = angle * i;
		float x = coords.x + (coords.radius * cos(glm::radians(currentAngle)));
		float y = coords.y + (coords.radius * sin(glm::radians(currentAngle)));
		float z = 0.0f;

		tmp[(i * 3)] = x;
		tmp[(i * 3) + 1] = y;
		tmp[(i * 3) + 2] = z;
	}
	*len = (triangleCount * 3 * 3);
	float *verts = (float *)malloc(sizeof(float) * (*len));

	// triangles
	for (int i = 0; i < triangleCount; i++) {
		verts[(i * 9)] = tmp[0];
		verts[(i * 9) + 1] = tmp[1];
		verts[(i * 9) + 2] = tmp[2];

		verts[(i * 9) + 3] = tmp[(i * 3) + 3];
		verts[(i * 9) + 3 + 1] = tmp[(i * 3) + 3 + 1];
		verts[(i * 9) + 3 + 2] = tmp[(i * 3) + 3 + 2];

		verts[(i * 9) + 6] = tmp[(i * 3) + 6];
		verts[(i * 9) + 6 + 1] = tmp[(i * 3) + 6 + 1];
		verts[(i * 9) + 6 + 2] = tmp[(i * 3) + 6 + 2];

	}
	free(tmp);
	return verts;
}

float *genPolygonColors(int len, float r, float g, float b)
{
	float *colors = (float *)calloc(len, sizeof(float));
	for(int i = 0; i < len/3; i++) {
		colors[(i * 3)] = r;
		colors[(i * 3) + 1] = g;
		colors[(i * 3) + 2] = b;
	}
	return colors;
}
