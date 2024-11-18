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

#define VECTOR_ZERO glm::vec3(0.f)
#define VECTOR_UNIT glm::vec3(0.f)

#define rad_to_deg(x) ((x) * 57.295754f)
#define deg_to_rad(x) ((x) * 0.0174533f)

#define ERROR_ID if (ID > 4) { std::cout << "Error. size of the array 5. Trying to take data in " << ID << std::endl; return; }

namespace test {
	class TestBasicLights : public Test {
	public:
		struct DirLight {
			glm::vec3 direction = VECTOR_ZERO;

			glm::vec3 ambient = VECTOR_ZERO;
			glm::vec3 diffuse = VECTOR_ZERO;
			glm::vec3 specular = VECTOR_ZERO;
		};

		struct PointLight {
			glm::vec3 position = VECTOR_ZERO;

			glm::vec3 ambient = VECTOR_ZERO;
			glm::vec3 diffuse = VECTOR_ZERO;
			glm::vec3 specular = VECTOR_ZERO;

			float constant = 1.f;
			float linear = 1.f;
			float quadratic = 1.f;
		};

		struct SpotLight {
			glm::vec3 position = VECTOR_ZERO;
			glm::vec3 direction = VECTOR_ZERO;

			glm::vec3 ambient = VECTOR_ZERO;
			glm::vec3 diffuse = VECTOR_ZERO;
			glm::vec3 specular = VECTOR_ZERO;

			float constant = 1.f;
			float linear = 1.f;
			float quadratic = 1.f;
			
			float cutOff = 0.f;
			float outerCutOff = 0.f;
		};
		TestBasicLights();

		DirLight createDirLight(glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular) {
			DirLight dir;
			dir.direction = Direction; dir.ambient = Ambient; dir.diffuse = Diffuse; dir.specular = Specular;
			return dir;
		}
		PointLight createPointLight(glm::vec3 Position, glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float constant, float linear, float quadratic) {
			PointLight point;
			point.position = Position; point.ambient = Ambient; point.diffuse = Diffuse; point.specular = Specular;
			point.constant = constant; point.linear = linear; point.quadratic = quadratic;
			return point;
		}
		SpotLight createSpotLight(glm::vec3 Position, glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular, float constant, float linear, float quadratic, float cutOff, float cutOffRange) {
			SpotLight spot;
			spot.position = Position; spot.direction = Direction; spot.ambient = Ambient; spot.diffuse = Diffuse; spot.specular = Specular;
			spot.constant = constant; spot.linear = linear; spot.quadratic = quadratic; spot.cutOff = cutOff; spot.outerCutOff = cutOffRange;
			return spot;
		}

		void addDirLight(DirLight dirLight);
		void addPointLight(unsigned int ID, PointLight pointLight);
		void addSpotLight(unsigned int ID, SpotLight spotLight);

		void logSpotLightState(unsigned int ID) {
			ERROR_ID
			std::cout << "SpotLight " << ID << " Position : " << m_SpotLights[ID].position.x << ", " << m_SpotLights[ID].position.y << ", " << m_SpotLights[ID].position.z << ", " << std::endl;
			std::cout << "SpotLight " << ID << " Direction : " << m_SpotLights[ID].direction.x << ", " << m_SpotLights[ID].direction.y << ", " << m_SpotLights[ID].direction.z << ", " << std::endl;
			std::cout << "SpotLight " << ID << " Ambient : " << m_SpotLights[ID].ambient.x << ", " << m_SpotLights[ID].ambient.y << ", " << m_SpotLights[ID].ambient.z << ", " << std::endl;
			std::cout << "SpotLight " << ID << " Diffuse : " << m_SpotLights[ID].diffuse.x << ", " << m_SpotLights[ID].diffuse.y << ", " << m_SpotLights[ID].diffuse.z << ", " << std::endl;
			std::cout << "SpotLight " << ID << " Specular : " << m_SpotLights[ID].specular.x << ", " << m_SpotLights[ID].specular.y << ", " << m_SpotLights[ID].specular.z << ", " << std::endl;
			std::cout << "SpotLight " << ID << " constant : " << m_SpotLights[ID].constant << std::endl;
			std::cout << "SpotLight " << ID << " linear : " << m_SpotLights[ID].linear << std::endl;
			std::cout << "SpotLight " << ID << " quadratic : " << m_SpotLights[ID].quadratic << std::endl;
			std::cout << "SpotLight " << ID << " cutOff : " << m_SpotLights[ID].cutOff << std::endl;
			std::cout << "SpotLight " << ID << " outerCutOff : " << m_SpotLights[ID].outerCutOff << std::endl;
			std::cout << "------------------------------------------------------" << std::endl;
		}
		//void onUpdate(float deltaTime) override;
		void onRender(GLFWwindow* window, Renderer renderer, glm::mat4* view, Camera* camera) override;
		void onImGUI() override;
	private:
		DirLight m_DirLight;
		PointLight m_PointLights[5];
		SpotLight m_SpotLights[5];

		bool camera_spot = true;
		float m_Vertices[288] = {
			// POSITION			  TEXTURES COORDS		NORMALS
			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f, // FRONT
			 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		0.0f, 0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f, // BACK
			 0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f, // LEFT
			-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

			 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f, // RIGHT
			 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f, // DOWN
			 0.5f, -0.5f,  0.5f,	1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

			 0.5f,  0.5f, -0.5f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f, // UP
			-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f
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


		vbo m_Vbo;
		ibo m_Ibo;
		glm::mat4 m_Projection;

		VertexBufferLayout m_Layout;
		vao m_ObjVao;
		Shader m_ObjShader;

		unsigned int lightChoice = 0;

		// Light
		vao m_LightVao;
		Shader m_LightShader;
		glm::vec4 LightColor;
		glm::vec3 m_PointLightPosition[2] = {
			glm::vec3(0.7f, 0.2f, 2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
		};
		glm::vec3 m_SpotLightPosition;

		glm::vec3 m_DirLightDirection;
		glm::vec3 m_SpotLightDirection;

		glm::vec3 m_LightScale;
		glm::vec3 m_LightRotation;
		glm::mat4 m_LightModel;


		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;

		glm::vec3 m_LightAmbient;
		glm::vec3 m_LightDiffuse;
		glm::vec3 m_LightSpecular;

		float m_Shininess;

		float constant = 1.f;
		float linear = 0.09f;
		float quadric = 0.032;
		float CutOff = 15.f;

		//Object
		glm::vec4 ObjColor;
		glm::vec3 m_ObjPosition[10] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		glm::vec3 m_ObjScale;
		glm::vec3 m_ObjRotation[10];
		glm::mat4 m_ObjModel;
		Texture m_ObjTexture;
		Texture m_ObjTextureSpecular;
	};
}