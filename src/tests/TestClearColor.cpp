#include "tests/TestClearColor.h"

namespace test {
	TestClearColor::TestClearColor() : m_ClearColor{ 0.45f, 0.55f, 0.60f, 1.00f } {

	}

	void TestClearColor::onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* camera) {
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		renderer.Clear();
	}

	void TestClearColor::onImGUI() {
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}