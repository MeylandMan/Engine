#pragma once
#include <glad/glad.h>
#include <vector>
#include<renderer/Vertex.h>

class  vbo
{
public:
	vbo(const void* data, unsigned int size);
	~vbo();

	/*	
	
	*/
	//Delete the copy constructor/assignment.
	vbo(const vbo&) = delete;
	vbo& operator=(const vbo&) = delete;

	vbo(vbo&& other) : ID(other.ID)
	{
		other.ID = NULL;
	}

	vbo& operator=(vbo&& other)
	{
		//ALWAYS check for self-assignment.
		if (this != &other)
		{
			deleteVBO();

			//ID is now 0.
			std::swap(ID, other.ID);
		}
	}
	
	void Bind() const;
	void Unbind() const;
	GLuint ID;
private:
	vbo CreateVBO(const void* data, unsigned int size) {
		vbo vb(data, size);
		return vb;
	}
	void deleteVBO() { glDeleteBuffers(1, &ID); }
};