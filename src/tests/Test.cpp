#include "../src/tests/Test.h"
#include <glad/glad.h>

namespace test {

	TestMenu::TestMenu(Test*& currentTestPtr) : m_CurrentTest(currentTestPtr) {}

	void TestMenu::onImGUIRender() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}
}