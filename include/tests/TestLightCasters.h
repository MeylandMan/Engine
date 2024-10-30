#pragma once

#include "tests/Test.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace test {
	class TestLightCasters : public Test {
	public:
		TestLightCasters();

		void onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* camera) override;
		void onImGUI() override;
	};

}