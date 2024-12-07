#include "tests/TestCubeDrawing.h"

namespace test {
	TestCubeDrawing::TestCubeDrawing() : m_Ibo(ibo(indices, sizeof(indices))),
		m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))),
		m_Texture(Texture("dirt.png")) {
		m_Scale = glm::vec3(1.f, 1.f, 1.f);

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "DrawingCube" VERTEX_SHADER, SHADERS_PATH "DrawingCube" FRAGMENT_SHADER);
		m_Shader.bind();

		m_Layout.PushShort<float>(3, 1);
		m_Layout.PushShort<float>(2, 1);
		m_Layout.PushShort<float>(3, 1);
		m_Vao.AddBuffer(m_Vbo, m_Layout);

		m_Texture.Bind();

		m_Shader.setUniform1i("u_Texture", 0);
	}

	void TestCubeDrawing::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {

		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		//m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_WIDTH, 0.1f, 100.f);
		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);
		m_Model = glm::mat4(1.0f);

		m_Model = glm::translate(m_Model, m_Position);
		m_Model = glm::rotate(m_Model, glm::radians(0.f), m_Rotation);
		m_Model = glm::scale(m_Model, m_Scale);

		m_Shader.setUniform1i("u_Texture", 0);

		m_Shader.setUniformMatrix4f("u_Model", m_Model);
		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		renderer.Draw(m_Vao, m_Ibo, m_Shader);
	}

	void TestCubeDrawing::onImGUI() {
		ImGui::SliderFloat3("Position : ", &m_Position.x, -10.f, 10.f);
		ImGui::SliderFloat3("Rotation : ", &m_Rotation.x, -90.f, 90.f);
		ImGui::SliderFloat3("Scale : ", &m_Scale.x, 0.f, 5.f);
	}
}