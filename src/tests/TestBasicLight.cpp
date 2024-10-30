#include "tests/TestBasicLight.h"

namespace test {
	TestBasicLight::TestBasicLight() : m_Ibo(ibo(indices, sizeof(indices))),
		m_LightVbo(vbo(m_LightVertices, sizeof(m_LightVertices))) {

		m_LightScale = vec3(1.f, 1.f, 1.f);

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "BasicLight/" VERTEX_SHADER, SHADERS_PATH "BasicLight/" FRAGMENT_SHADER);
		m_Shader.bind();

		m_Layout.Push<float>(3);
		m_Layout.Push<float>(4);
		m_Layout.Push<float>(3);
		m_LightVao.AddBuffer(m_LightVbo, m_Layout);

	}

	void TestBasicLight::onRender(GLFWwindow* window, Renderer renderer, mat4* view) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		m_Projection = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);

		//Light
		{
			m_LightModel = Transform(m_LightScale, m_LightRotation, m_LightPosition);
			m_Shader.setUniformMatrix4f("u_Model", m_LightModel);
		}
		

		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		renderer.Draw(m_LightVao, m_Ibo, m_Shader);
	}

	void TestBasicLight::onImGUI() {
		
	}
}