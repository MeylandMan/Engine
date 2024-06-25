#pragma once

#include<imgui.h>
#include <vector>
#include <functional>
#include <string>

#include <drivers/opengl_context.h>
#include <GLFW/glfw3.h>

namespace test {
	class Test {
	public:
		Test() {}

		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender(GLFWwindow* window, mat4 _view, mat4 _proj) {}
		virtual void onImGUIRender() {}


	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPtr);

		void onImGUIRender() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector <std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}