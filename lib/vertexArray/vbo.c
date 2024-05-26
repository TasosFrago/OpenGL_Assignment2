#include "vbo.h"


void vboGen(VBO_t *vbo, const void *data, size_t size, GLenum usage)
{
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void vboBind(VBO_t *vbo)
{
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
}
