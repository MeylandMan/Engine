#include "tests/Test.h"

namespace test {
	Testmenu::Testmenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {

	}

	Testmenu::~Testmenu() {

	}

	void Testmenu::onUpdate(float deltaTime) {

	}

	void Testmenu::onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* cam) {

	}

	void Testmenu::onImGUI() {
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}
}