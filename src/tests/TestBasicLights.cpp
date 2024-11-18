#include "tests/TestBasicLights.h"

namespace test {
	TestBasicLights::TestBasicLights() : m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))), m_Ibo(ibo(indices, sizeof(indices))),
		m_Ambient(glm::vec3(1.f, 0.5f, 0.31f)), m_Diffuse(glm::vec3(1.f, 0.5f, 0.31f)), m_Specular(glm::vec3(0.5f, 0.5f, 0.5f)), m_Shininess(32.f),
		m_LightAmbient(glm::vec3(0.2f, 0.2f, 0.2f)), m_LightDiffuse(glm::vec3(0.5f, 0.5f, 0.5f)), m_LightSpecular(glm::vec3(1.0f, 1.0f, 1.0f)),
		m_ObjTexture("container2.png"), m_ObjTextureSpecular("container2_specular.png") {


		m_DirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
		m_SpotLightPosition = glm::vec3(0.f);

		LightColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = glm::vec3(0.2f, 0.2f, 0.2f);

		ObjColor = glm::vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = glm::vec3(1.f, 1.f, 1.f);

		m_LightShader.loadShaderProgramFromFile(SHADERS_PATH "BasicLights/LightCube.vert", SHADERS_PATH "BasicLights/LightCube.frag");
		m_ObjShader.loadShaderProgramFromFile(SHADERS_PATH "BasicLights/Cube.vert", SHADERS_PATH "BasicLights/Cube.frag");

		m_Layout.PushShort<float>(3, 1);
		m_Layout.PushShort<float>(2, 1);
		m_Layout.PushShort<float>(3, 1);
		m_ObjVao.AddBuffer(m_Vbo, m_Layout);

		m_LightVao.AddBuffer(m_Vbo, m_Layout);

		m_DirLight = createDirLight(VECTOR_ZERO, VECTOR_ZERO, VECTOR_ZERO, VECTOR_ZERO);
		addSpotLight(0, createSpotLight(VECTOR_ZERO, VECTOR_ZERO, VECTOR_ZERO, VECTOR_ZERO, VECTOR_ZERO, 0.f, 0.f, 0.f, 0.f, 0.f));
	}
	/*
	void TestBasicLights::onUpdate(float deltaTime) {
		m_LightDiffuse = glm::vec3(LightColor.x, LightColor.y, LightColor.z) * glm::vec3(0.5f, 0.5f, 0.5f);
		m_LightAmbient = m_LightDiffuse * glm::vec3(0.2f, 0.2f, 0.2f);
	}
	*/
	

	void TestBasicLights::addDirLight(DirLight dirLight) { m_DirLight = dirLight; }

	void TestBasicLights::addPointLight(unsigned int ID, PointLight pointLight) { ERROR_ID m_PointLights[ID] = pointLight; }
	void TestBasicLights::addSpotLight(unsigned int ID, SpotLight spotLight) { ERROR_ID m_SpotLights[ID] = spotLight; }

	void TestBasicLights::onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);

		m_Projection = glm::perspective(glm::radians(camera->Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f);

		// Object
		{
			m_ObjShader.bind();
			m_ObjTexture.Bind();
			m_ObjTextureSpecular.Bind(1);
			
			m_ObjShader.setUniformMatrix4f("u_Model", glm::mat4(1.f));
			m_ObjShader.setUniformMatrix4f("u_View", *view);
			m_ObjShader.setUniformMatrix4f("u_Proj", m_Projection);
			m_ObjShader.setUniform3f("u_ViewPosition", camera->Position);

			m_ObjShader.setUniform3f("dirLight.direction", m_DirLight.direction);
			m_ObjShader.setUniform3f("dirLight.ambient", m_DirLight.ambient);
			m_ObjShader.setUniform3f("dirLight.diffuse", m_DirLight.diffuse);
			m_ObjShader.setUniform3f("dirLight.specular", m_DirLight.specular);

			//m_ObjShader.setUniform1i("NR_POINT_LIGHTS", 2);
			//m_ObjShader.setUniform1i("NR_SPOT_LIGHTS", 1);

			// point light 1
			m_ObjShader.setUniform3f("pointLights[0].position", m_PointLightPosition[0]);
			m_ObjShader.setUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
			m_ObjShader.setUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
			m_ObjShader.setUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
			m_ObjShader.setUniform1f("pointLights[0].constant", 1.0f);
			m_ObjShader.setUniform1f("pointLights[0].linear", 0.09f);
			m_ObjShader.setUniform1f("pointLights[0].quadratic", 0.032f);
			// point light 2
			m_ObjShader.setUniform3f("pointLights[1].position", m_PointLightPosition[1]);
			m_ObjShader.setUniform3f("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
			m_ObjShader.setUniform3f("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
			m_ObjShader.setUniform3f("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
			m_ObjShader.setUniform1f("pointLights[1].constant", 1.0f);
			m_ObjShader.setUniform1f("pointLights[1].linear", 0.09f);
			m_ObjShader.setUniform1f("pointLights[1].quadratic", 0.032f);

			// spotLight
			if (camera_spot) {
				m_SpotLights[0].position = camera->Position; m_SpotLights[0].direction = camera->Front;
				m_SpotLights[0].ambient = m_ClProperties[0]; m_SpotLights[0].diffuse = m_ClProperties[1]; m_SpotLights[0].specular = m_ClProperties[2];
				m_SpotLights[0].constant = 1.f; m_SpotLights[0].linear = 0.09f; m_SpotLights[0].quadratic = 0.032f;
				m_SpotLights[0].cutOff = m_ClCutOff[0]; m_SpotLights[0].outerCutOff = m_ClCutOff[1];
			} else {
				m_SpotLights[0].position = VECTOR_ZERO; m_SpotLights[0].direction = VECTOR_ZERO;
				m_SpotLights[0].ambient = VECTOR_ZERO; m_SpotLights[0].diffuse = VECTOR_ZERO; m_SpotLights[0].specular = VECTOR_ZERO;
				m_SpotLights[0].constant = 1.f; m_SpotLights[0].linear = 1.f; m_SpotLights[0].quadratic = 1.f;
				m_SpotLights[0].cutOff = 0.f; m_SpotLights[0].outerCutOff = 0.f;
			}

			m_ObjShader.setUniform3f("spotLights[0].position", m_SpotLights[0].position);
			m_ObjShader.setUniform3f("spotLights[0].direction", m_SpotLights[0].direction);
			m_ObjShader.setUniform3f("spotLights[0].ambient", m_SpotLights[0].ambient);
			m_ObjShader.setUniform3f("spotLights[0].diffuse", m_SpotLights[0].diffuse);
			m_ObjShader.setUniform3f("spotLights[0].specular", m_SpotLights[0].specular);
			m_ObjShader.setUniform1f("spotLights[0].constant", m_SpotLights[0].constant);
			m_ObjShader.setUniform1f("spotLights[0].linear", m_SpotLights[0].linear);
			m_ObjShader.setUniform1f("spotLights[0].quadratic", m_SpotLights[0].quadratic);
			m_ObjShader.setUniform1f("spotLights[0].cutOff", glm::cos(glm::radians(m_SpotLights[0].cutOff)));
			m_ObjShader.setUniform1f("spotLights[0].outerCutOff", glm::cos(glm::radians(m_SpotLights[0].outerCutOff)));

			m_ObjShader.setUniform1i("material.diffuse", 0);
			m_ObjShader.setUniform1i("material.specular", 1);
			m_ObjShader.setUniform1f("material.shininess", m_Shininess);

			for (unsigned int i = 0; i < 10; i++)
			{
				m_ObjModel = glm::mat4(1.0f);
				m_ObjModel = glm::translate(m_ObjModel, m_ObjPosition[i]);
				float angle = 20.0f * i;
				m_ObjModel = glm::rotate(m_ObjModel, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				m_ObjModel = glm::scale(m_ObjModel, glm::vec3(1.f));
				m_ObjShader.setUniformMatrix4f("u_Model", m_ObjModel);
				renderer.Draw(m_ObjVao, m_Ibo, m_ObjShader);
			}
		}

		m_ObjTexture.Unbind();
		m_ObjTextureSpecular.Unbind();
		// Light
		m_LightShader.bind();

		m_LightShader.setUniformMatrix4f("u_View", *view);
		m_LightShader.setUniformMatrix4f("u_Proj", m_Projection);
		m_LightShader.setUniform4f("u_LightColor", LightColor);

		for (unsigned int i = 0; i < 2; i++) {
			m_LightModel = glm::mat4(1.0f);
			m_LightModel = glm::translate(m_LightModel, m_PointLightPosition[i]);
			m_LightModel = glm::rotate(m_LightModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
			m_LightModel = glm::scale(m_LightModel, glm::vec3(0.1f));
			m_LightShader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
		}
	}

	void  TestBasicLights::onImGUI() {
		if(ImGui::Button("Add Point Light")) {}
		ImGui::Begin("Point Lights");
		ImGui::End();
		if (ImGui::Button("Add Spot Light")) {}
		ImGui::Begin("Spot Lights");
		ImGui::End();

		//Camera Spot Light
		ImGui::Checkbox("Camera Spot Light", &camera_spot);
		if (camera_spot) {
			ImGui::Begin("Camera");
			ImGui::SliderFloat3("Ambient :", &m_ClProperties[0].x, 0.f, 1.f);
			ImGui::SliderFloat3("Diffuse :", &m_ClProperties[1].x, 0.f, 1.f);
			ImGui::SliderFloat3("Specular :", &m_ClProperties[2].x, 0.f, 1.f);

			ImGui::SliderFloat("CutOff :", &m_ClCutOff[0], 0.f, 90.f);
			ImGui::SliderFloat("outerCutOff :", &m_ClCutOff[1], 0.f, 90.f);
			ImGui::Text("outerCutOff needs always to be higher than cutOff\nif you want it to work properly");
			ImGui::End();
		}
		// Directional Light
		ImGui::Text("Directional light");
		ImGui::SliderFloat3("Direction :", &m_DirLight.direction.x, -1.f, 1.f);

		ImGui::SliderFloat3("Ambient :", &m_DirLight.ambient.x, 0.f, 1.f);
		ImGui::SliderFloat3("Diffuse :", &m_DirLight.diffuse.x, 0.f, 1.f);
		ImGui::SliderFloat3("Specular :", &m_DirLight.specular.x, 0.f, 1.f);
	}
}