#include "../src/tests/TestClearColor.h"
#include <drivers/opengl_context.h>

namespace test {

	TestClearColor::TestClearColor() : m_ClearColor{0.2f, 0.3f, 0.8f, 1.f} {

	}

	TestClearColor::~TestClearColor() {

	}

	void TestClearColor::onUpdate(float deltaTime) {

	}

	void TestClearColor::onRender(GLFWwindow* window, mat4 _view, mat4 _proj) {
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::onImGUIRender() {
		ImGui::ColorEdit4("Clear color", m_ClearColor);
	}
}