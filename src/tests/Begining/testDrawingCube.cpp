#include "../src/tests/Begining/testDrawingCube.h"
#include <imgui.h>

namespace test {

	testDrawingCube::testDrawingCube() {
		
		m_VAO.Bind();

		m_VBO.Bind();

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);

		m_VAO.AddBuffer(m_VBO, layout);

		m_VBO.Unbind();

		m_EBO.Bind();

		m_Shader.loadShaderProgramFromFile(TEST_RESOURCES_PATH "shaders/Default.vert", TEST_RESOURCES_PATH "shaders/Default.frag");

		m_Shader.bind();
		m_TextureVBO.Bind();
		
		m_Shader.setUniform1i("u_Texture", 0);
	}

	testDrawingCube::~testDrawingCube() {
		m_VAO.~vao();
		m_VBO.~vbo();
		m_EBO.~ebo();
		m_Shader.clear();
		m_TextureVBO.~Texture();
	}

	void testDrawingCube::onUpdate(float deltaTime) {

	}

	void testDrawingCube::onRender(GLFWwindow* window, mat4 _view, mat4 _proj) {

		int width, height;
		// Getting the width and height of the window
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Clearing the window frame buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		// Matrices upgrades

		mat4 model = Transform(m_Scale, m_Rotation, m_Position);
		mat4 view = _view;
		mat4 proj = _proj;

		m_Shader.setUniformMatrix4f("u_Model", model);
		m_Shader.setUniformMatrix4f("u_View", _view);
		m_Shader.setUniformMatrix4f("u_Proj", _proj);

		// Rendering

		m_Shader.bind();
		m_VAO.Bind();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, m_EBO.GetCount(), GL_UNSIGNED_INT, nullptr);
		//glDrawArrays(GL_TRIANGLES, 0, 36);
		
	}

	void testDrawingCube::onImGUIRender() {
		ImGui::SliderFloat3("Position", &m_Position[0], -10.f, 10.f);
		ImGui::SliderFloat3("Scale", &m_Scale[0], 1.f, 10.f);
		ImGui::SliderFloat3("Rotation", &m_Rotation[0], 0.f, 360.f);
	}
}