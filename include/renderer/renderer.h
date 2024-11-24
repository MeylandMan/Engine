#pragma once

#include <glad/glad.h>
#include <renderer/vao.h>
#include <renderer/vbo.h>
#include <renderer/ibo.h>
#include <renderer/textures.h>
#include <renderer/openglDebug.h>
#include <renderer/shader.h>
#include <renderer/VertexBufferLayout.h>
#include <vector>
#include <renderer/Vertex.h>
#include<renderer/mesh.h>
#include<string>

class Renderer
{
public:

	void Draw(const vao& va, const ibo& ib, Shader& shader) const;
	void DrawMesh(Mesh* mesh, Shader& shader) const;
	void Clear() const;

private:

};