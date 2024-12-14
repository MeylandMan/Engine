#pragma once
#include <glad/glad.h>
#include<vector>

class ibo
{
public:
	ibo(const unsigned int* data, unsigned int count);
	ibo(std::vector<unsigned int>* data);
	~ibo();

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
	unsigned int m_Count;
};