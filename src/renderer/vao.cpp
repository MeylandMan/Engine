#include <renderer/vao.h>

vao::vao() {

	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

vao::~vao() {
	deleteVAO();
}

void vao::AddBuffer(vbo& vb, const VertexBufferLayout& layout) const {

	Bind();

	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {

		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void vao::Bind() const {
	glBindVertexArray(ID);
}

void vao::Unbind() const {
	glBindVertexArray(0);
}

unsigned int vao::GetID() const {
	return ID;
}