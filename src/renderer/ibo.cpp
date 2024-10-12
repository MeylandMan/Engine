#include <renderer/ibo.h>
#include <iostream>

ibo::ibo(const unsigned int* data, unsigned int count) : m_Count(count)  {
	_ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ibo::~ibo() { glDeleteBuffers(1, &ID); }


void ibo::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void ibo::Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }