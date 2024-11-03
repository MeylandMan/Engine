#include "tests/TestMaterials.h"
/*
	Might be useful if I use a Normal Matrix for better realism. Might cause your pc to blow up though...
*/
namespace test {
	TestMaterials::TestMaterials() : m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))), m_Ibo(ibo(indices, sizeof(indices))),
		m_Ambient(vec3(1.f, 0.5f, 0.31f)), m_Diffuse(vec3(1.f, 0.5f, 0.31f)), m_Specular(vec3(0.5f, 0.5f, 0.5f)), m_Shininess(32.f), 
		m_LightAmbient(vec3(0.2f, 0.2f, 0.2f)), m_LightDiffuse(vec3(0.5f, 0.5f, 0.5f)), m_LightSpecular(vec3(1.0f, 1.0f, 1.0f)) {

		m_LightPosition = vec3(0.5f, 1.f, 0.f);
		LightColor = vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = vec3(0.2f, 0.2f, 0.2f);

		ObjColor = vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = vec3(1.f, 1.f, 1.f);

		m_ObjShader.loadShaderProgramFromFile(SHADERS_PATH "Materials/Cube.vert", SHADERS_PATH "Materials/Cube.frag");
		m_LightShader.loadShaderProgramFromFile(SHADERS_PATH "Materials/LightCube.vert", SHADERS_PATH "Materials/LightCube.frag");

		m_Layout.PushShort<float>(3, 0);
		m_Layout.PushShort<float>(3, 0);

		m_ObjVao.AddBuffer(m_Vbo, m_Layout);
		m_LightVao.AddBuffer(m_Vbo, m_Layout);
	}

	void TestMaterials::onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* camera) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.11f, 0.113f, 0.12f, 1.f);

		m_Projection = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);

		

		// Object
		{
			m_ObjShader.bind();

			
			m_ObjShader.setUniformMatrix4f("u_View", *view);
			m_ObjShader.setUniformMatrix4f("u_Proj", m_Projection);

			m_ObjShader.setUniform3f("u_LightPosition", m_LightPosition);
			m_ObjShader.setUniform4f("u_LightColor", LightColor);

			m_ObjShader.setUniform3f("u_ViewPosition", camera->getPosition());

			m_ObjShader.setUniform3f("material.ambient", m_Ambient);
			m_ObjShader.setUniform3f("material.diffuse", m_Diffuse);
			m_ObjShader.setUniform3f("material.specular", m_Specular);
			m_ObjShader.setUniform1f("material.shininess", m_Shininess);

			m_ObjShader.setUniform3f("light.ambient", m_LightAmbient);
			m_ObjShader.setUniform3f("light.diffuse", m_LightDiffuse); // darkened
			m_ObjShader.setUniform3f("light.specular", m_LightSpecular);

			m_ObjModel = Transform(m_ObjScale, m_ObjRotation, m_ObjPosition);
			m_ObjShader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_ObjVao, m_Ibo, m_ObjShader);
		}

		// Light
		{
			m_LightShader.bind();

			m_LightShader.setUniformMatrix4f("u_View", *view);
			m_LightShader.setUniformMatrix4f("u_Proj", m_Projection);

			m_ObjModel = Transform(m_LightScale, m_LightRotation, m_LightPosition);
			m_LightShader.setUniformMatrix4f("u_Model", m_ObjModel);

			renderer.Draw(m_LightVao, m_Ibo, m_LightShader);
		}
	}

	void TestMaterials::onImGUI() {
		ImGui::ColorEdit4("Light Color", &LightColor.x);
		ImGui::SliderFloat3("Light position", &m_LightPosition.x, -10.f, 10.f);

		
		ImGui::SliderFloat3("ambiant strength", &m_Ambient.x, 0.f, 1.f);
		ImGui::SliderFloat3("diffuse strength", &m_Diffuse.x, 0.f, 1.f);
		ImGui::SliderFloat3("specular strength", &m_Specular.x, 0.f, 1.f);
		ImGui::SliderFloat("shininess", &m_Shininess, 0.f, 64.f);
	}
}