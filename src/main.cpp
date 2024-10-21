#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <renderer/renderer.h>
#include <renderer/openglDebug.h>
#include <renderer/shader.h>
#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "tests/TestClearColor.h"

#define USE_GPU_ENGINE 0

//imgui_impl_glfw.h

#define GLFW_INCLUDE_NONE
#define USE_GPU_ENGINE 0

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 100.0f
#define DEFAULT_FOV 60.0f

#define SENSITIVITY 10.0f

#define MAX_PITCH 90.0f

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}

float view_y = 0.0f;

vec3 Camera;
vec3 TargetTo;

float vertices[312] = {
	// POSITION					  COLOR				TEXTURES COORDS		TEXTURE INDEX
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.0f,				0.f,		0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				0.f,		0.0f, 0.0f, 0.0f, // FRONT
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				0.f,		0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				0.f,		0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,	1.0f, 0.0f,				1.f,		0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				1.f,		0.0f, 0.0f, 0.0f, // BACK
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				1.f,		0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				1.f,		0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f, // LEFT
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,

	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f, // RIGHT
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				2.f,		0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				2.f,		0.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				4.f,		0.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				4.f,		0.0f, 0.0f, 0.0f, // DOWN
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				4.f,		0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				4.f,		0.0f, 0.0f, 0.0f,

	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,				3.f,		0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,				3.f,		0.0f, 0.0f, 0.0f, // UP
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,				3.f,		0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,				3.f,		0.0f, 0.0f, 0.0f,
};

unsigned int indices[] = {
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

int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;
float look_dir, look_pitch;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool is_locked = false;

void centerCursorPosition(GLFWwindow* window) {
	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void cursor_position(GLFWwindow* window) {
	double xx, yy;
	glfwGetCursorPos(window, &xx, &yy);

	look_dir -= (xx - WINDOW_WIDTH / 2) / 10;

	look_pitch += (yy - WINDOW_HEIGHT / 2) / 10;
	look_pitch = std::clamp(look_pitch, -MAX_PITCH, MAX_PITCH);
}

void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		is_locked = !is_locked;
	}

	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
		// FullScreen
	}
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	float spd = 5.f * deltaTime;

	if (is_locked) {
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			Camera.y += spd;
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			Camera.y -= spd;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // LEFT
			Camera.z -= sin(deg_to_rad(look_dir)) * spd;
			Camera.x -= cos(deg_to_rad(look_dir)) * spd;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // DOWN
			Camera.z += sin(deg_to_rad(look_dir)) * spd;
			Camera.x += cos(deg_to_rad(look_dir)) * spd;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // RIGHT
			Camera.z += cos(deg_to_rad(look_dir)) * spd;
			Camera.x -= sin(deg_to_rad(look_dir)) * spd;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // UP
			Camera.z -= cos(deg_to_rad(look_dir)) * spd;
			Camera.x += sin(deg_to_rad(look_dir)) * spd;
		}
	}

}

void getMatrix4String(mat4 mat) {
	float j = 0;
	for (int i = 0; i < 16; ++i) {
		if (j > 3) {
			j = 0;
			std::cout << std::endl;
		}
		std::cout << "[" << mat.asArray[i] << "]";

		j++;
	}
	std::cout << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

#pragma region report opengl errors to std
	//enable opengl debugging output.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping


	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Maber", NULL, NULL); //Maber stand for Magical Number
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 410 core");

	// Depth render
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

#pragma region report opengl errors to std
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion
	
	vec3 pos;
	vec3 scl(1.f, 1.f, 1.f);
	vec3 RT;

	mat4 model;
	mat4 view;
	mat4 proj;

	//shader loading example
	Shader s;
	s.loadShaderProgramFromFile(SHADERS_PATH "Default/" VERTEX_SHADER, SHADERS_PATH "Default/" FRAGMENT_SHADER);
	s.bind();

	vao va;
	vbo vb(vertices, sizeof(vertices));

	

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	layout.Push<float>(2);
	layout.Push<float>(1);
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	ibo ib(indices, sizeof(indices));

	Texture tex("Default/textures/dirt.png");
	tex.Bind();

	s.setUniform1i("u_Texture", 0);
	Renderer renderer;

	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	test::Test* CurrentTest = nullptr;
	test::Testmenu* menu = new test::Testmenu(CurrentTest);

	CurrentTest = menu;

	menu->RegisterTest<test::TestClearColor>("Clear Color");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f,0.58f,0.3f,1.f);
		renderer.Clear();

		processInput(window);
		glfwPollEvents();


		//Camera stuffs
		if (is_locked) {
			cursor_position(window);
			centerCursorPosition(window);

			TargetTo.x = Camera.x - cos(deg_to_rad(look_dir));
			TargetTo.y = Camera.y - sin(deg_to_rad(look_pitch));
			TargetTo.z = Camera.z - sin(deg_to_rad(look_dir));
		}


		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		view = LookAt(Camera, TargetTo, vec3(0.0f, 1.0f, 0.0f));
		proj = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);
		model = Transform(scl, RT, pos);

		
		{

			s.setUniform1i("u_Texture", 0);

			s.setUniformMatrix4f("u_Model", model);
			s.setUniformMatrix4f("u_View", view);
			s.setUniformMatrix4f("u_Proj", proj);

		}

		//renderer.Draw(va, ib, s);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{

			
			if (CurrentTest) {
				CurrentTest->onUpdate(1/io.Framerate);
				CurrentTest->onRender(renderer);

				ImGui::Begin("Test");

				ImGui::Text("Camera Position : Vector3(%.1f, %.1f, %.1f)", Camera.x, Camera.y, Camera.z);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				if (CurrentTest != menu && ImGui::Button("<-")) {
					delete CurrentTest;
					CurrentTest = menu;
				}
				CurrentTest->onImGUI();

				ImGui::End();
			}

			
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete CurrentTest;
	if (CurrentTest != menu)
		delete menu;
	return 0;
}
