#pragma once
#include <vector>
#include <glad/glad.h>
#include <renderer/Vertex.h>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}
		_ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout() : m_Stride(0) {}

	template<typename T>
	void Push(unsigned int Count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride = sizeof(Vertex);
	}


	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	template<typename T>
	void PushShort(unsigned int count, unsigned int type) {
		static_assert(false);
	}

	template<>
	void PushShort<float>(unsigned int count, unsigned int type) {
		switch (type) {
		case 0:
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride = sizeof(ShortVertex);
			break;
		case 1:
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride = sizeof(ShortTVertex);
			break;
		case 2:
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride = sizeof(ShortCVertex);
			break;
		}
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};