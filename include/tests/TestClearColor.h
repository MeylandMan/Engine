#pragma once

#include "tests/Test.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor();

		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		float m_ClearColor[4];
	};
	
}