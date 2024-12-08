#include <renderer/renderer.h>

void Renderer::Draw(const vao& va, const ibo& ib, Shader& shader) const {
	va.Bind();
	ib.Bind();
	shader.bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
} 

void Renderer::DrawModel(Model& model, Shader& shader) const {
	model.Draw(shader);
}

void Renderer::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
