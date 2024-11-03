#pragma once

#include "tests/Test.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 100.0f
#define DEFAULT_FOV 60.0f

namespace test {
	class TestMaterials : public Test {
	public:
		TestMaterials();

		void onRender(GLFWwindow* window, Renderer renderer, mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		float m_Vertices[144] = {
			// POSITION				NORMALS
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // FRONT
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // BACK
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f,

			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // LEFT
			-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // RIGHT
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // DOWN
			 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,

			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // UP
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f
		};
		unsigned int indices[36] = {
			// front and back
			0, 3, 2,
			2, 1, 0,

			4, 5, 6,
			6, 7 ,4,
			// left and right
			11, 8, 9,
			9, 10, 11,

			12, 13, 14,
			14, 15, 12,
			// bottom and top
			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};
		
		VertexBufferLayout m_Layout;
		vbo m_Vbo;
		ibo m_Ibo;
		mat4 m_Projection;

		vao m_ObjVao;
		Shader m_ObjShader;

		// Light
		vao m_LightVao;
		Shader m_LightShader;
		vec4 LightColor;
		vec3 m_LightPosition;
		vec3 m_LightScale;
		vec3 m_LightRotation;
		mat4 m_LightModel;

		vec3 m_Ambient;
		vec3 m_Diffuse;
		vec3 m_Specular;

		vec3 m_LightAmbient;
		vec3 m_LightDiffuse;
		vec3 m_LightSpecular;

		float m_Shininess;

		//Object
		vec4 ObjColor;
		vec3 m_ObjPosition;
		vec3 m_ObjScale;
		vec3 m_ObjRotation;
		mat4 m_ObjModel;

	};

}