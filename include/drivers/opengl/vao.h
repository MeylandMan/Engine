#pragma once
#include <glad/glad.h>
#include <drivers/opengl/VertexBufferLayout.h>
#include <drivers/opengl/vbo.h>

class vao
{
public:
	vao();
	~vao();

	void AddBuffer(vbo& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;
private:
	unsigned int ID;
};