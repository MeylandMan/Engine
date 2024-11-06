#pragma once

#include "tests/Test.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 100.0f
#define DEFAULT_FOV 60.0f

namespace test {
	class TestCubeDrawing : public Test {
	public:
		TestCubeDrawing();

		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		/*
		float m_Vertices[312] = {
			// POSITION					  COLOR				TEXTURES COORDS		TEXTURE INDEX
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.0f,				0.f,		0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				0.f,		0.0f, 0.0f, 0.0f, // FRONT
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				0.f,		0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				0.f,		0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 0.0f,				1.f,		0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				1.f,		0.0f, 0.0f, 0.0f, // BACK
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				1.f,		0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				1.f,		0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f, // LEFT
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,

			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f, // RIGHT
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				4.f,		0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				4.f,		0.0f, 0.0f, 0.0f, // DOWN
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				4.f,		0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				4.f,		0.0f, 0.0f, 0.0f,

			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				3.f,		0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				3.f,		0.0f, 0.0f, 0.0f, // UP
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				3.f,		0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				3.f,		0.0f, 0.0f, 0.0f,
		};
		*/

		float m_Vertices[312] = {
			// POSITION					  COLOR				TEXTURES COORDS		TEXTURE INDEX
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // FRONT
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,	0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // BACK
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // LEFT
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // RIGHT
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // DOWN
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // UP
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		};
		unsigned int indices[36] = {
			// front and back
			0, 3, 2,
			2, 1, 0,

			4, 5, 6,
			6, 7 ,4,
			// left and right
			11, 8, 9,
			9, 10, 11,

			12, 13, 14,
			14, 15, 12,
			// bottom and top
			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};
		Shader m_Shader;
		vao m_Vao;
		vbo m_Vbo;
		VertexBufferLayout m_Layout;
		ibo m_Ibo;
		Texture m_Texture;

		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;

		glm::mat4 m_Model;
		glm::mat4 m_Projection;
	};
}