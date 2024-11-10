#include "tests/TestLightCasters.h"

/*
	Might be useful if I use a Normal Matrix for better realism. Might cause your pc to blow up though...
*/
namespace test {
	TestLightCasters::TestLightCasters() : m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))), m_Ibo(ibo(indices, sizeof(indices))),
		m_Ambient(glm::vec3(1.f, 0.5f, 0.31f)), m_Diffuse(glm::vec3(1.f, 0.5f, 0.31f)), m_Specular(glm::vec3(0.5f, 0.5f, 0.5f)), m_Shininess(32.f),
		m_LightAmbient(glm::vec3(0.2f, 0.2f, 0.2f)), m_LightDiffuse(glm::vec3(0.5f, 0.5f, 0.5f)), m_LightSpecular(glm::vec3(1.0f, 1.0f, 1.0f)),
		m_ObjTexture("container2.png"), m_ObjTextureSpecular("container2_specular.png") {


		m_LightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
		m_LightPosition = glm::vec3(0.5f, 1.f, 0.f);
		LightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = glm::vec3(0.2f, 0.2f, 0.2f);

		ObjColor = glm::vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = glm::vec3(1.f, 1.f, 1.f);

		m_LightShader.loadShaderProgramFromFile(SHADERS_PATH "LightCasters/LightCube.vert", SHADERS_PATH "LightCasters/LightCube.frag");
		m_ObjShader[0].loadShaderProgramFromFile(SHADERS_PATH "LightCasters/Cube.vert", SHADERS_PATH "LightCasters/DirectionalLight.frag");
		m_ObjShader[1].loadShaderProgramFromFile(SHADERS_PATH "LightCasters/Cube.vert", SHADERS_PATH "LightCasters/PointLight.frag");
		m_ObjShader[2].loadShaderProgramFromFile(SHADERS_PATH "LightCasters/Cube.vert", SHADERS_PATH "LightCasters/SpotLight.frag");

		m_Layout.PushShort<float>(3, 1);
		m_Layout.PushShort<float>(2, 1);
		m_Layout.PushShort<float>(3, 1);
		m_ObjVao.AddBuffer(m_Vbo, m_Layout);

		m_LightVao.AddBuffer(m_Vbo, m_Layout);
	}

	void TestLightCasters::onUpdate(float deltaTime) {
		m_LightDiffuse = glm::vec3(LightColor.x, LightColor.y, LightColor.z) * glm::vec3(0.5f, 0.5f, 0.5f);
		m_LightAmbient = m_LightDiffuse * glm::vec3(0.2f, 0.2f, 0.2f);
	}

	void TestLightCasters::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);

		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);



		// Object
		{
			m_ObjShader[lightChoice].bind();

			m_ObjTexture.Bind();
			m_ObjTextureSpecular.Bind(1);

			m_ObjShader[lightChoice].setUniformMatrix4f("u_Model", glm::mat4(1.f));
			m_ObjShader[lightChoice].setUniformMatrix4f("u_View", *view);
			m_ObjShader[lightChoice].setUniformMatrix4f("u_Proj", m_Projection);

			m_ObjShader[lightChoice].setUniform3f("light.position", m_LightPosition);
			m_ObjShader[lightChoice].setUniform3f("light.direction", m_LightDirection);

			m_ObjShader[lightChoice].setUniform4f("light.color", LightColor);
			m_ObjShader[lightChoice].setUniform3f("light.ambient", m_LightAmbient);
			m_ObjShader[lightChoice].setUniform3f("light.diffuse", m_LightDiffuse); // darkened
			m_ObjShader[lightChoice].setUniform3f("light.specular", m_LightSpecular);

			m_ObjShader[lightChoice].setUniform1f("light.constant", constant);
			m_ObjShader[lightChoice].setUniform1f("light.linear", linear);
			m_ObjShader[lightChoice].setUniform1f("light.quadratic", quadric);

			m_ObjShader[lightChoice].setUniform1i("material.diffuse", 0);
			m_ObjShader[lightChoice].setUniform1i("material.specular", 1);
			m_ObjShader[lightChoice].setUniform1f("material.shininess", m_Shininess);

			m_ObjShader[lightChoice].setUniform3f("u_ViewPosition", camera->Position);

			if (lightChoice == 2) {

				m_ObjShader[2].setUniform3f("light.position", camera->Position);
				m_ObjShader[2].setUniform3f("light.direction", camera->Front);
				m_ObjShader[2].setUniform1f("light.cutOff", std::cosf(deg_to_rad(CutOff)));
				m_ObjShader[2].setUniform1f("light.outerCutOff", std::cosf(deg_to_rad(CutOff+5.f)));
			}

			for (unsigned int i = 0; i < 10; i++)
			{
				m_ObjModel = glm::mat4(1.0f);
				m_ObjModel = glm::translate(m_ObjModel, m_ObjPosition[i]);
				float angle = 20.0f * i;
				m_ObjModel = glm::rotate(m_ObjModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				m_ObjModel = glm::scale(m_ObjModel, glm::vec3(1.f));
				m_ObjShader[lightChoice].setUniformMatrix4f("u_Model", m_ObjModel);
				renderer.Draw(m_ObjVao, m_Ibo, m_ObjShader[lightChoice]);
			}

			m_ObjTexture.Unbind();
			m_ObjTextureSpecular.Unbind();
		}

		// Light
		if(lightChoice == 1) {
			m_LightShader.bind();

			m_LightShader.setUniformMatrix4f("u_View", *view);
			m_LightShader.setUniformMatrix4f("u_Proj", m_Projection);
			m_LightShader.setUniform4f("u_LightColor", LightColor);

			m_LightModel = glm::mat4(1.0f);
			m_LightModel = glm::translate(m_LightModel, m_LightPosition);
			m_LightModel = glm::rotate(m_LightModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
			m_LightModel = glm::scale(m_LightModel, glm::vec3(0.1f));
			m_LightShader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
		}
	}

	void TestLightCasters::onImGUI() {

		if (ImGui::Button("Directional Light"))
			lightChoice = 0;
		else if (ImGui::Button("Point Light")) {
			m_LightPosition = glm::vec3();
			lightChoice = 1;
		}
		else if (ImGui::Button("Spot Light")) {
			m_LightPosition = glm::vec3();
			lightChoice = 2;
		}
			

		switch (lightChoice) {
		case 0:
			ImGui::SliderFloat3("Light Direction", &m_LightDirection.x, -10.f, 10.f);
			break;
		case 1:
			ImGui::SliderFloat3("Light position", &m_LightPosition.x, -20.f, 20.f);
			ImGui::SliderFloat("Light constant", &constant, 0.1f, 1.f);
			ImGui::SliderFloat("Light linear", &linear, 0.1f, 1.f);
			ImGui::SliderFloat("Light quadric", &quadric, 0.1f, 1.f);
			break;
		case 2:
			ImGui::SliderFloat("Light constant", &constant, 0.1f, 1.f);
			ImGui::SliderFloat("Light linear", &linear, 0.1f, 1.f);
			ImGui::SliderFloat("Light quadric", &quadric, 0.1f, 1.f);
			ImGui::SliderFloat("Light CutOff", &CutOff, 15.f, 90.f);
			break;
		}
	}
}