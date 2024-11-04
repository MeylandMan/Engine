#include "tests/TestLightCasters.h"

/*
	Might be useful if I use a Normal Matrix for better realism. Might cause your pc to blow up though...
*/
namespace test {
	TestLightCasters::TestLightCasters() : m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))), m_Ibo(ibo(indices, sizeof(indices))),
		m_Ambient(vec3(1.f, 0.5f, 0.31f)), m_Diffuse(vec3(1.f, 0.5f, 0.31f)), m_Specular(vec3(0.5f, 0.5f, 0.5f)), m_Shininess(32.f),
		m_LightAmbient(vec3(0.2f, 0.2f, 0.2f)), m_LightDiffuse(vec3(0.5f, 0.5f, 0.5f)), m_LightSpecular(vec3(1.0f, 1.0f, 1.0f)),
		m_ObjTexture("container2.png"), m_ObjTextureSpecular("container2_specular.png") {

		for (unsigned int i = 0; i < 10; i++)
		{
			float angle = 20.0f * i * 1.2;
			float z = -1.5f * i;

			float x = std::powf(-1.2f, i) * std::cos(i + 15);
			float y = std::powf(-1.1f, i) * std::sin(i + 37);

			m_ObjRotation[i] = vec3(angle, angle, angle);
			m_ObjPosition[i] = vec3(x, y, z);
		}

		m_LightDirection = vec3(-0.2f, -1.0f, -0.3f);
		m_LightPosition = vec3(0.5f, 1.f, 0.f);
		LightColor = vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = vec3(0.2f, 0.2f, 0.2f);

		ObjColor = vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = vec3(1.f, 1.f, 1.f);

		m_ObjShader.loadShaderProgramFromFile(SHADERS_PATH "LightCasters/Cube.vert", SHADERS_PATH "LightCasters/Cube.frag");
		m_LightShader.loadShaderProgramFromFile(SHADERS_PATH "LightCasters/LightCube.vert", SHADERS_PATH "LightCasters/LightCube.frag");

		m_Layout.PushShort<float>(3, 1);
		m_Layout.PushShort<float>(2, 1);
		m_Layout.PushShort<float>(3, 1);
		m_ObjVao.AddBuffer(m_Vbo, m_Layout);

		m_LightVao.AddBuffer(m_Vbo, m_Layout);
	}

	void TestLightCasters::onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.11f, 0.113f, 0.12f, 1.f);

		m_Projection = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);



		// Object
		{
			m_ObjShader.bind();

			m_ObjTexture.Bind();
			m_ObjTextureSpecular.Bind(1);

			m_ObjShader.setUniformMatrix4f("u_View", *view);
			m_ObjShader.setUniformMatrix4f("u_Proj", m_Projection);

			m_ObjShader.setUniform3f("light.position", m_LightPosition);
			m_ObjShader.setUniform3f("light.direction", m_LightDirection);
			m_ObjShader.setUniform4f("u_LightColor", LightColor);
			m_ObjShader.setUniform1i("u_LightChoice", lightChoice);
			
			m_ObjShader.setUniform3f("u_ViewPosition", camera->getPosition());

			m_ObjShader.setUniform1i("material.diffuse", 0);
			m_ObjShader.setUniform1i("material.specular", 1);
			m_ObjShader.setUniform1f("material.shininess", m_Shininess);

			m_ObjShader.setUniform3f("light.ambient", m_LightAmbient);
			m_ObjShader.setUniform3f("light.diffuse", m_LightDiffuse); // darkened
			m_ObjShader.setUniform3f("light.specular", m_LightSpecular);

			for (unsigned int i = 0; i < 10; i++)
			{
				m_ObjModel = Transform(m_ObjScale, m_ObjRotation[i], m_ObjPosition[i]);
				m_ObjShader.setUniformMatrix4f("u_Model", m_ObjModel);
				renderer.Draw(m_ObjVao, m_Ibo, m_ObjShader);
			}

			m_ObjTexture.Unbind();
			m_ObjTextureSpecular.Unbind();
		}

		// Light
		if(lightChoice != 0) {
			m_LightShader.bind();

			m_LightShader.setUniformMatrix4f("u_View", *view);
			m_LightShader.setUniformMatrix4f("u_Proj", m_Projection);
			m_LightShader.setUniform4f("u_LightColor", LightColor);

			m_LightModel = Transform(m_LightScale, m_LightRotation, m_LightPosition);
			m_LightShader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
		}
	}

	void TestLightCasters::onImGUI() {
		ImGui::ColorEdit4("Light Color", &LightColor.x);
		if (ImGui::Button("Directional Light"))
			lightChoice = 0;
		else if (ImGui::Button("Point Light")) {
			m_LightPosition = vec3(0.f, 0.f, 0.f);
			lightChoice = 1;
		}
		else if (ImGui::Button("Spot Light")) {
			m_LightPosition = vec3(0.f, 0.f, 0.f);
			lightChoice = 2;
		}
			

		switch (lightChoice) {
		case 0:
			ImGui::SliderFloat3("Light Direction", &m_LightDirection.x, -10.f, 10.f);
			break;
		case 1:
			ImGui::SliderFloat3("Light position", &m_LightPosition.x, -10.f, 10.f);
			break;
		case 2:
			ImGui::SliderFloat3("Light position", &m_LightPosition.x, -10.f, 10.f);
			break;
		}
	}
}