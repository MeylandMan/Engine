#pragma once
#include <glad/glad.h>
#include<vector>
#include <algorithm>

class ibo
{
public:
	ibo(const unsigned int* data, unsigned int count);
	~ibo();
	/*
	
	*/
	//Delete the copy constructor/assignment.
	ibo(const ibo&) = delete;
	ibo& operator=(const ibo&) = delete;

	ibo(ibo&& other) : ID(other.ID)
	{
		other.ID = 0; //Use the "null" texture for the old object.
	}

	ibo& operator=(ibo&& other)
	{
		//ALWAYS check for self-assignment.
		if (this != &other)
		{
			deleteEBO();
			//obj_ is now 0.
			std::swap(ID, other.ID);
		}
	}

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return m_Count; }

private:
	ibo CreateEBO(const unsigned int* data, unsigned int count) {
		ibo ib(data, count);
		return ib;
	}
	void deleteEBO() {
		glDeleteBuffers(1, &ID);
	}
	unsigned int ID;
	unsigned int m_Count = 0;
};