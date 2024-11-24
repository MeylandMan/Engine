#include <renderer/renderer.h>

void Renderer::Draw(const vao& va, const ibo& ib, Shader& shader) const {
	va.Bind();
	ib.Bind();
	shader.bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawMesh(Mesh* mesh, Shader& shader) const {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	std::vector<Texture> textures = mesh->getTextures();

	shader.bind();
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i].Bind(i);
		std::string number;
		std::string name = textures[i].getType();
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		shader.setUniform1i(("material." + name + number).c_str(), i);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	mesh->getVao().Bind();
	mesh->getIbo().Bind();

	glDrawElements(GL_TRIANGLES, mesh->getIbo().GetCount(), GL_UNSIGNED_INT, nullptr);
	mesh->getVao().Unbind();
}

void Renderer::Clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
