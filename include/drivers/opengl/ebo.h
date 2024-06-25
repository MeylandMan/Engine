#pragma once
#include <glad/glad.h>

class ebo
{
public:
	ebo(const unsigned int* data, unsigned int count);
	~ebo();

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int ID;
	unsigned int m_Count;
};