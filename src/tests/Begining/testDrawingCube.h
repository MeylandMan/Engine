#include "../src/tests/Test.h"
#include <math/math_main.h>


namespace test {

	class testDrawingCube : public Test {

	public:
		testDrawingCube();
		~testDrawingCube();

		void onUpdate(float deltaTime) override;
		void onRender(GLFWwindow* window, mat4 _view, mat4 _proj) override;
		void onImGUIRender() override;
	private:
		float m_Vertices[216] = {
			// POSITION					  COLOR				TEXTURES COORDS
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f
		};

		unsigned int m_Indices[36] = {
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
		std::string path = TEST_RESOURCES_PATH "textures/orange_wool.png";

		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale = vec3(1.f, 1.f, 1.f);

		Shader m_Shader;
		vao m_VAO;
		vbo m_VBO = vbo(m_Vertices, sizeof(m_Vertices));
		ebo m_EBO = ebo(m_Indices, sizeof(m_Indices));
		Texture m_TextureVBO = Texture(path);
	};

}