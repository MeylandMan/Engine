#include "tests/TestLoadModel.h"

namespace test {
	TestLoadModel::TestLoadModel() : m_Model(Model(m_ModelPath)) {
		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "LoadingModel/Model.vert", SHADERS_PATH "LoadingModel/Model.frag");
	}

	void TestLoadModel::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);

		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);

		// draw in wireframe
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_Shader.bind();

		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(1.f));
		m_Shader.setUniformMatrix4f("u_Model", m_ModelMatrix);
		m_Model.Draw(m_Shader);
	}

	void TestLoadModel::onImGUI() {
		
	}
}