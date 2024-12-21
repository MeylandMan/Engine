#pragma once
#include <glad/glad.h>
#include <renderer/vbo.h>
#include <renderer/VertexBufferLayout.h>


class vao
{
public:
	vao();
	~vao();

	/*
	
	*/

	//Delete the copy constructor/assignment.
	vao(const vao&) = delete;
	vao& operator=(const vao&) = delete;

	vao(vao&& other) : ID(other.ID)
	{
		other.ID = 0;
	}
	vao& operator=(vao&& other)
	{
		//ALWAYS check for self-assignment.
		if (this != &other)
		{
			deleteVAO();
			//ID is now 0.
			std::swap(ID, other.ID);
		}
	}
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