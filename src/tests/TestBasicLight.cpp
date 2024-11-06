#include "tests/TestBasicLight.h"
/*
	Might be useful if I use a Normal Matrix for better realism. Might cause your pc to blow up though...
*/
namespace test {
	TestBasicLight::TestBasicLight() : m_Ibo(ibo(indices, sizeof(indices))),
		m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))),
		specularStrength(0.5f), ambiantStrength(0.1f) {

		m_LightPosition = glm::vec3(0.5f, 1.f, 0.f);
		LightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = glm::vec3(0.2f, 0.2f, 0.2f);

		ObjColor = glm::vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = glm::vec3(1.f, 1.f, 1.f);

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "BasicLight" VERTEX_SHADER, SHADERS_PATH "BasicLight" FRAGMENT_SHADER);
		m_Shader.bind();

		m_Layout.PushShort<float>(3,0);
		m_Layout.PushShort<float>(3,0);
		m_ObjVao.AddBuffer(m_Vbo, m_Layout);


		m_Shader.setUniform3f("u_LightPosition", m_LightPosition.x, m_LightPosition.y, m_LightPosition.z);
		m_Shader.setUniform4f("u_LightColor", LightColor.x, LightColor.y, LightColor.z, LightColor.w);
		m_Shader.setUniform4f("u_ObjectColor", ObjColor.x, ObjColor.y, ObjColor.z, ObjColor.w);
	}

	void TestBasicLight::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.11f, 0.113f, 0.12f, 1.f);

		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_WIDTH, 0.1f, 100.f);

		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		//Light
		{
			m_Shader.setUniform3f("u_LightPosition", m_LightPosition);
			m_Shader.setUniform4f("u_LightColor", LightColor);
			m_Shader.setUniform4f("u_ObjectColor", 1.f, 1.f, 1.f, 1.f);

			m_Shader.setUniform1f("specularStrength", specularStrength);
			m_Shader.setUniform1f("ambiantStrength", ambiantStrength);

			m_Shader.setUniform3f("u_ViewPosition", camera->Position);

			m_LightModel = glm::mat4(1.0f);
			m_LightModel = glm::translate(m_LightModel, m_LightPosition);
			m_LightModel = glm::rotate(m_LightModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
			m_Shader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_ObjVao, m_Ibo, m_Shader);
		}

		//Object
		{
			m_Shader.setUniform4f("u_ObjectColor", ObjColor);

			m_ObjModel = glm::mat4(1.0f);
			m_ObjModel = glm::translate(m_ObjModel, m_ObjPosition);
			m_ObjModel = glm::rotate(m_ObjModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
			m_Shader.setUniformMatrix4f("u_Model", m_ObjModel);

			renderer.Draw(m_ObjVao, m_Ibo, m_Shader);
		}
	}

	void TestBasicLight::onImGUI() {
		ImGui::ColorEdit4("Light Color", &LightColor.x);
		ImGui::SliderFloat3("Light position", &m_LightPosition.x, -10.f, 10.f);

		ImGui::SliderFloat("specular strength", &specularStrength, 0.f, 1.f);
		ImGui::SliderFloat("ambiant strength", &ambiantStrength, 0.f, 1.f);
	}
}