#pragma once

#include <renderer/renderer.h>
#include <functional>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <Camera.h>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {}
		virtual void onImGUI() {}
	};

	class Testmenu : public Test {
	public:
		Testmenu(Test*& currentTestPointer);

		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;

		template<typename T>
		void RegisterTest(const std::string& name) {
			std::cout << "Registering test : " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T; }));
		}

		void clear() {
			std::cout << "clearing the list : " << std::endl;
			m_Tests.clear();
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}