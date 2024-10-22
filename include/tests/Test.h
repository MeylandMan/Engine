#pragma once

#include <renderer/renderer.h>
#include <functional>
#include <iostream>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender(GLFWwindow* window, Renderer renderer, mat4* view) {}
		virtual void onImGUI() {}
	};

	class Testmenu : public Test {
	public:
		Testmenu(Test*& currentTestPointer);
		~Testmenu();

		void onUpdate(float deltaTime) override;
		void onRender(GLFWwindow* window, Renderer renderer, mat4* view) override;
		void onImGUI() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test : " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}