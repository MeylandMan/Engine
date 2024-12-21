#pragma once

#include "tests/Test.h"
#include<renderer/model.h>
#include<backends/imfilebrowser.h>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 100.0f
#define DEFAULT_FOV 60.0f

#define VECTOR_ZERO glm::vec3(0.f)
#define VECTOR_UNIT glm::vec3(1.f)

#define rad_to_deg(x) ((x) * 57.295754f)
#define deg_to_rad(x) ((x) * 0.0174533f)

using namespace std;

namespace test {
	class TestLoadModel : public Test {
	public:
		TestLoadModel();

		void onUpdate(float deltaTime) override;
		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		ImGui::FileBrowser fileDialog;
		string m_ModelPath = RESOURCES_PATH "objects/Toon Link/Toon Link.obj";
		Shader m_Shader;
		Model m_Model = Model(m_ModelPath);

		glm::mat4 m_ModelMatrix;
		glm::mat4 m_Projection;

		glm::vec3 m_ModelPosition = VECTOR_ZERO;
		glm::vec3 m_ModelRotation = VECTOR_ZERO;
		glm::vec3 m_ModelScale = glm::vec3(1.f);

		bool m_PolygonMode = false;
		bool m_NegateYCoordinate = false;
		bool m_PreviousCheck = false;
	};

}