#include "tests/TestLoadModel.h"

namespace test {
	TestLoadModel::TestLoadModel() : m_Model(new Model("")) {
		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "LoadingModel/Model.vert", SHADERS_PATH "LoadingModel/Model.frag");

		// (optional) set browser properties
		fileDialog.SetTitle("Model file explorer");
		fileDialog.SetTypeFilters(
			{ 
				".obj", ".fbx", ".3ds", ".dae", ".ply", ".stl", ".x", ".gltf", ".glb", ".ma", ".wire", ".blend",
				".md2", ".md3", ".md5"
			}
		);

	}
	void TestLoadModel::onUpdate(float deltaTime) {
		if (m_NegateYCoordinate != m_PreviousCheck) {
			m_PreviousCheck = m_NegateYCoordinate;
			m_Model->negateTexCoordY(m_ModelPath, m_NegateYCoordinate);
		}
	}
	void TestLoadModel::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);

		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);

		// draw in wireframe
		if(m_PolygonMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_Shader.bind();

		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_ModelPosition);

		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_ModelRotation.z), glm::vec3(0.f, 0.f, 1.f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_ModelRotation.x), glm::vec3(1.f, 0.f, 0.f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_ModelRotation.y), glm::vec3(0.f, 1.f, 0.f));

		m_ModelMatrix = glm::scale(m_ModelMatrix, m_ModelScale);
		m_Shader.setUniformMatrix4f("u_Model", m_ModelMatrix);
		renderer.DrawModel(*m_Model, m_Shader);
		//m_Model.Draw(m_Shader);
	}

	void TestLoadModel::onImGUI() {
		if (ImGui::Button("Choose Model"))
			fileDialog.Open();

		fileDialog.Display();
		if (fileDialog.HasSelected())
		{
			delete m_Model;
			m_ModelPath = fileDialog.GetSelected().string();
			for (char& c : m_ModelPath) {
				if (c == '\\') {
					c = '/';
				}
			}
			m_Model = new Model(m_ModelPath);
			fileDialog.ClearSelected();
		}

		ImGui::Checkbox("Draw edges", &m_PolygonMode);
		ImGui::Checkbox("Negate TexCoord Y coordinate", &m_NegateYCoordinate);
		ImGui::SliderFloat3("Position", &m_ModelPosition.x, -10.f, 10.f);
		ImGui::SliderFloat3("Rotation", &m_ModelRotation.x, -90.f, 90.f);
		ImGui::SliderFloat3("Scale", &m_ModelScale.x, 0.1f, 2.f);
	}
}