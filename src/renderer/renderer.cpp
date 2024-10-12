#include <renderer/renderer.h>

void Renderer::Draw(const vao& va, const ibo& ib, Shader& shader) const {
	shader.bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
void Renderer::AddMesh(mesh &msh){
	Push(msh);
}

void Renderer::RemoveMesh() const {

}
void Renderer::RemoveAllMeshes() {
	ClearAll();
}
*/
