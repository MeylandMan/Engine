#pragma once
#include <glad/glad.h>
#include <renderer/vbo.h>
#include <renderer/VertexBufferLayout.h>

class vao
{
public:
	vao();
	~vao();

	void AddBuffer(vbo& vb, const VertexBufferLayout& layout) const;
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;

private:
	vao CreateVAO() {
		vao vv;
		return vv;
	}
	void deleteVAO() { glDeleteVertexArrays(1, &ID); }
	unsigned int ID;
};