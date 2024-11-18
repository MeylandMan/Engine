#include "tests/TestBasicLights.h"

namespace test {
	TestBasicLights::TestBasicLights() : m_ObjVao(vao()), m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))), m_Ibo(ibo(indices, sizeof(indices))),
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

		m_DirLight = createDirLight(glm::vec3(0.f, -0.5f, -1.f), VECTOR_ZERO, VECTOR_UNIT, VECTOR_UNIT);
	}
	/*
	void TestBasicLights::onUpdate(float deltaTime) {
		m_LightDiffuse = glm::vec3(LightColor.x, LightColor.y, LightColor.z) * glm::vec3(0.5f, 0.5f, 0.5f);
		m_LightAmbient = m_LightDiffuse * glm::vec3(0.2f, 0.2f, 0.2f);
	}
	*/
	

	void TestBasicLights::addDirLight(DirLight dirLight) { m_DirLight = dirLight; }

	void TestBasicLights::addPointLight() { 
		PointLight pointLight;
		for (unsigned int i = 0; i < 5; i++) {
			if (m_PointLights[i].is_on == false) {
				pointLight.is_on = true;
				pointLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
				pointLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
				pointLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
				pointLight.constant = 1.f;
				pointLight.linear = 0.09f;
				pointLight.quadratic = 0.032f;
				m_PointLights[i] = pointLight;
				break;
			}
			
		}
		
	}
	void TestBasicLights::addSpotLight() { 
		SpotLight spotLight;
		for (unsigned int i = 1; i < 5; i++) {
			if (m_SpotLights[i].is_on == false) {
				spotLight.is_on = true;
				spotLight.direction = glm::vec3(0.f, 0.f, -1.f);
				spotLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
				spotLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
				spotLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
				spotLight.constant = 1.f;
				spotLight.linear = 0.09f;
				spotLight.quadratic = 0.032f;

				spotLight.cutOff = 12.5f;
				spotLight.outerCutOff = 15.f;
				m_SpotLights[i] = spotLight;
				break;
			}

		}
	}

	void TestBasicLights::removePointLight(unsigned int ID) {
		PointLight pointLight;
		pointLight.is_on = false;
		pointLight.position = VECTOR_ZERO;
		pointLight.ambient = VECTOR_ZERO;
		pointLight.diffuse = VECTOR_ZERO;
		pointLight.specular = VECTOR_ZERO;
		pointLight.constant = 1.f;
		pointLight.linear = 1.f;
		pointLight.quadratic = 1.f;
		m_PointLights[ID] = pointLight;
	}
	void TestBasicLights::removeSpotLight(unsigned int ID) {
		SpotLight spotLight;
		spotLight.is_on = false;
		spotLight.position = VECTOR_ZERO;
		spotLight.direction = VECTOR_ZERO;
		spotLight.ambient = VECTOR_ZERO;
		spotLight.diffuse = VECTOR_ZERO;
		spotLight.specular = VECTOR_ZERO;
		spotLight.constant = 1.f;
		spotLight.linear = 1.f;
		spotLight.quadratic = 1.f;

		spotLight.cutOff = 0.f;
		spotLight.outerCutOff = 0.f;
		m_SpotLights[ID] = spotLight;
	}
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

			/*
			m_ObjShader.setUniform3f("pointLights[0].position", m_PointLightPosition[0]);
			m_ObjShader.setUniform3f("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
			m_ObjShader.setUniform3f("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
			m_ObjShader.setUniform3f("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
			m_ObjShader.setUniform1f("pointLights[0].constant", 1.0f);
			m_ObjShader.setUniform1f("pointLights[0].linear", 0.09f);
			m_ObjShader.setUniform1f("pointLights[0].quadratic", 0.032f);
			*/
			
			// point light 2
			

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

			for (unsigned int i = 0; i < 5; i++) {

				std::string temp = std::format("pointLights[{}].position", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_PointLights[i].position);
				temp = std::format("pointLights[{}].ambient", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_PointLights[i].ambient);
				temp = std::format("pointLights[{}].diffuse", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_PointLights[i].diffuse);
				temp = std::format("pointLights[{}].specular", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_PointLights[i].specular);
				temp = std::format("pointLights[{}].constant", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_PointLights[i].constant);
				temp = std::format("pointLights[{}].linear", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_PointLights[i].linear);
				temp = std::format("pointLights[{}].quadratic", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_PointLights[i].quadratic);

				temp = std::format("spotLights[{}].position", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_SpotLights[i].position);
				temp = std::format("spotLights[{}].direction", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_SpotLights[i].direction);
				temp = std::format("spotLights[{}].ambient", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_SpotLights[i].ambient);
				temp = std::format("spotLights[{}].diffuse", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_SpotLights[i].diffuse);
				temp = std::format("spotLights[{}].specular", i);
				m_ObjShader.setUniform3f(temp.c_str(), m_SpotLights[i].specular);
				temp = std::format("spotLights[{}].constant", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_SpotLights[i].constant);
				temp = std::format("spotLights[{}].linear", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_SpotLights[i].linear);
				temp = std::format("spotLights[{}].quadratic", i);
				m_ObjShader.setUniform1f(temp.c_str(), m_SpotLights[i].quadratic);
				temp = std::format("spotLights[{}].cutOff", i);
				m_ObjShader.setUniform1f(temp.c_str(), glm::cos(glm::radians(m_SpotLights[i].cutOff)));
				temp = std::format("spotLights[{}].outerCutOff", i);
				m_ObjShader.setUniform1f(temp.c_str(), glm::cos(glm::radians(m_SpotLights[i].outerCutOff)));
			}
			


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

		for (unsigned int i = 0; i < 5; i++) {

			if (m_PointLights[i].is_on) {
				m_LightModel = glm::mat4(1.0f);
				m_LightModel = glm::translate(m_LightModel, m_PointLights[i].position);
				m_LightModel = glm::rotate(m_LightModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
				m_LightModel = glm::scale(m_LightModel, glm::vec3(0.1f));
				m_LightShader.setUniformMatrix4f("u_Model", m_LightModel);

				renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
			}
			

			if (m_SpotLights[i].is_on) {
				m_LightModel = glm::mat4(1.0f);
				m_LightModel = glm::translate(m_LightModel, m_SpotLights[i].position);
				m_LightModel = glm::rotate(m_LightModel, glm::radians(0.f), glm::vec3(1.0f, 0.3f, 0.5f));
				m_LightModel = glm::scale(m_LightModel, glm::vec3(0.1f));
				m_LightShader.setUniformMatrix4f("u_Model", m_LightModel);

				renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
			}
			
		}
	}

	void  TestBasicLights::onImGUI() {
		if (ImGui::Button("Add Point Light")) { addPointLight(); }
		
		if (ImGui::Button("Add Spot Light")) { addSpotLight(); }
		

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

		// Point Lights
		ImGui::Begin("Point Lights");
		for (unsigned int i = 0; i < 5; i++) {
			if (m_PointLights[i].is_on == false)
				continue;
			ImGui::Text("Point Light %.0f", (float)i);
			ImGui::SliderFloat3("position :", &m_PointLights[i].position.x, -10.f, 10.f);
			ImGui::SliderFloat3("ambient :", &m_PointLights[i].ambient.x, 0.f, 1.f);
			ImGui::SliderFloat3("diffuse :", &m_PointLights[i].diffuse.x, 0.f, 1.f);
			ImGui::SliderFloat3("specular :", &m_PointLights[i].specular.x, 0.f, 1.f);

			ImGui::SliderFloat("constant :", &m_PointLights[i].constant, 0.1f, 1.f);
			ImGui::SliderFloat("linear :", &m_PointLights[i].linear, 0.1f, 1.f);
			ImGui::SliderFloat("quadratic :", &m_PointLights[i].quadratic, 0.1f, 1.f);
			if (ImGui::Button("remove")) {
				removePointLight(i);
				std::cout << "Removed the Point Light " << i << std::endl;
			}
				
		}
		ImGui::End();

		// Spot Lights
		ImGui::Begin("Spot Lights");
		for (unsigned int i = 0; i < 5; i++) {
			if (m_SpotLights[i].is_on == false || i == 0)
				continue;
			ImGui::Text("Spot Light %.0f", (float)i);
			ImGui::SliderFloat3("position :", &m_SpotLights[i].position.x, -10.f, 10.f);
			ImGui::SliderFloat3("direction :", &m_SpotLights[i].direction.x, -1.f, 1.f);
			ImGui::SliderFloat3("ambient :", &m_SpotLights[i].ambient.x, 0.f, 1.f);
			ImGui::SliderFloat3("diffuse :", &m_SpotLights[i].diffuse.x, 0.f, 1.f);
			ImGui::SliderFloat3("specular :", &m_SpotLights[i].specular.x, 0.f, 1.f);

			ImGui::SliderFloat("constant :", &m_SpotLights[i].constant, 0.1f, 1.f);
			ImGui::SliderFloat("linear :", &m_SpotLights[i].linear, 0.1f, 1.f);
			ImGui::SliderFloat("quadratic :", &m_SpotLights[i].quadratic, 0.1f, 1.f);

			ImGui::SliderFloat("cutOff :", &m_SpotLights[i].cutOff, 0.f, 90.f);
			ImGui::SliderFloat("outerCutOff :", &m_SpotLights[i].outerCutOff, 0.f, 90.f);

			if (ImGui::Button("remove")) {
				removeSpotLight(i);
				std::cout << "Removed the Spoit Light " << i << std::endl;
			}
				
		}
		ImGui::End();
	}
}