#ifndef POLYGON_H
#define POLYGON_H

typedef enum {
	PENTAGON = 5,
	HEXAGON = 6,
	HEPTAGON = 7,
	OCTAGON = 8,
	NONAGON = 9,
	DECAGON = 10
} Polygon_t;

struct PolygonIDs {
	int ID1;
	int ID2;
};

struct PolygonIDs getPolygonTypes(int U);

struct coordinates {
	float x;
	float y;
	float radius;
};

float *genPolygonVerts(struct coordinates coords, int vCount, int *len);
float *genPolygonColors(int len, float r, float g, float b);

#endif // POLYGON_H
