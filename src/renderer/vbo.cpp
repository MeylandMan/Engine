#include <renderer/vbo.h>
#include <iostream>

vbo::vbo(const void* data, unsigned int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vbo::vbo(std::vector<ShortTVertex>* data) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(ShortTVertex), &data[0], GL_STATIC_DRAW);
}

vbo::~vbo() {
	deleteVBO();
}


void vbo::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void vbo::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}