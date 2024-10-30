#include "tests/TestCubeDrawing.h"

namespace test {
	TestCubeDrawing::TestCubeDrawing() : m_Ibo(ibo(indices, sizeof(indices))),
		m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))),
		m_Texture(Texture("dirt.png")) {
		m_Scale = vec3(1.f, 1.f, 1.f);

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "Default/" VERTEX_SHADER, SHADERS_PATH "Default/" FRAGMENT_SHADER);
		m_Shader.bind();

		m_Layout.Push<float>(3);
		m_Layout.Push<float>(4);
		m_Layout.Push<float>(2);
		m_Layout.Push<float>(1);
		m_Layout.Push<float>(3);
		m_Vao.AddBuffer(m_Vbo, m_Layout);

		m_Texture.Bind();

		m_Shader.setUniform1i("u_Texture", 0);
	}

	void TestCubeDrawing::onRender(GLFWwindow* window, Renderer renderer, mat4* view) {

		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		m_Projection = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);
		m_Model = Transform(m_Scale, m_Rotation, m_Position);

		m_Shader.setUniform1i("u_Texture", 0);

		m_Shader.setUniformMatrix4f("u_Model", m_Model);
		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		renderer.Draw(m_Vao, m_Ibo, m_Shader);
	}

	void TestCubeDrawing::onImGUI() {
		ImGui::SliderFloat3("Position : ", &m_Position.x, -10.f, 10.f);
		ImGui::SliderFloat3("Rotation : ", &m_Rotation.x, -360.f, 360.f);
		ImGui::SliderFloat3("Scale : ", &m_Scale.x, 0.f, 5.f);
	}
}