#include "tests/TestBasicLight.h"

namespace test {
	TestBasicLight::TestBasicLight() : m_Ibo(ibo(indices, sizeof(indices))),
		m_Vbo(vbo(m_Vertices, sizeof(m_Vertices))) {

		m_LightPosition = vec3(0.5f, 1.f, 0.f);
		LightColor = vec4(1.f, 1.f, 1.f, 1.f);
		m_LightScale = vec3(0.2f, 0.2f, 0.2f);

		ObjColor = vec4(1.f, 0.5f, 0.31f, 1.f);
		m_ObjScale = vec3(1.f, 1.f, 1.f);

		m_Shader.loadShaderProgramFromFile(SHADERS_PATH "BasicLight" VERTEX_SHADER, SHADERS_PATH "BasicLight" FRAGMENT_SHADER);
		m_Shader.bind();

		m_Layout.PushShort<float>(3,0);
		m_Layout.PushShort<float>(3,0);
		m_ObjVao.AddBuffer(m_Vbo, m_Layout);


		m_Shader.setUniform4f("u_LightColor", LightColor.x, LightColor.y, LightColor.z, LightColor.w);
		m_Shader.setUniform4f("u_ObjectColor", ObjColor.x, ObjColor.y, ObjColor.z, ObjColor.w);
	}

	void TestBasicLight::onRender(GLFWwindow* window, Renderer renderer, mat4* view) {
		int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glClearColor(0.11f, 0.113f, 0.12f, 1.f);

		m_Projection = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);

		m_Shader.setUniformMatrix4f("u_View", *view);
		m_Shader.setUniformMatrix4f("u_Proj", m_Projection);

		//Light
		{
			m_Shader.setUniform4f("u_LightColor", LightColor.x, LightColor.y, LightColor.z, LightColor.w);
			m_Shader.setUniform4f("u_ObjectColor", 1.f, 1.f, 1.f, 1.f);
			m_Shader.setUniform1i("u_IsLight", 1);

			m_LightModel = Transform(m_LightScale, m_LightRotation, m_LightPosition);
			m_Shader.setUniformMatrix4f("u_Model", m_LightModel);

			renderer.Draw(m_ObjVao, m_Ibo, m_Shader);
		}

		//Object
		{
			m_Shader.setUniform4f("u_ObjectColor", ObjColor.x, ObjColor.y, ObjColor.z, ObjColor.w);
			m_ObjModel = Transform(m_ObjScale, m_ObjRotation, m_ObjPosition);
			m_Shader.setUniformMatrix4f("u_Model", m_ObjModel);
			m_Shader.setUniform1i("u_IsLight", 0);

			renderer.Draw(m_ObjVao, m_Ibo, m_Shader);
		}
	}

	void TestBasicLight::onImGUI() {
		
	}
}