#pragma once
#include <glad/glad.h>
#include <vector>
class  vbo
{
public:
	vbo(const void* data, unsigned int size);
	~vbo();

	void Bind() const;
	void Unbind() const;
	GLuint ID;
	
};