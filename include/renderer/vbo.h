#pragma once
#include <glad/glad.h>
#include <vector>
#include<renderer/Vertex.h>

class  vbo
{
public:
	vbo(const void* data, unsigned int size);
	vbo(std::vector<ShortTVertex>* data);

	~vbo();

	void Bind() const;
	void Unbind() const;
	GLuint ID;

};