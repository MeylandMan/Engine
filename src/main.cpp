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
#include "tests/TestCubeDrawing.h"
#include "tests/TestBasicLight.h"
#include "tests/TestBasicLights.h"
#include "tests/TestLightCasters.h"
#include "tests/TestLightingMap.h"
#include "tests/TestLoadModel.h"
#include "tests/TestMaterials.h"

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

	mat4 view;
	Renderer renderer;

	bool show_another_window = false;

	test::Test* CurrentTest = nullptr;

	test::Testmenu* menuTest = new test::Testmenu(CurrentTest);

	CurrentTest = menuTest;

	//BasicMenuTest->RegisterTest<test::TestClearColor>("Clear Color");
	//BasicMenuTest->RegisterTest<test::TestCubeDrawing>("Drawing a Cube");
	
	short menu_index = 0;

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

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{

			
			if (CurrentTest) {
				CurrentTest->onUpdate(1/io.Framerate);
				CurrentTest->onRender(window, renderer, &view);

				ImGui::Begin("Test");

				ImGui::Text("Camera Position : Vector3(%.1f, %.1f, %.1f)", Camera.x, Camera.y, Camera.z);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				switch (menu_index) {
				case 0:
					if (ImGui::Button("Basic")) {
						menuTest->RegisterTest<test::TestClearColor>("Clear Color");
						menuTest->RegisterTest<test::TestCubeDrawing>("Drawing a Cube");
						menuTest->RegisterTest<test::TestBasicLight>("Basic Lighting");
						menuTest->RegisterTest<test::TestMaterials>("Materials");
						menuTest->RegisterTest<test::TestLightingMap>("Lighting maps");
						menuTest->RegisterTest<test::TestLightCasters>("Light Casters");
						menuTest->RegisterTest<test::TestLoadModel>("Loading Models");

						CurrentTest = menuTest;
						menu_index = 1;
					}
					else if (ImGui::Button("Advanced")) {
						//Do nothing for now
					}
					else if (ImGui::Button("Lighting")) {
						//Do nothing for now
					}
					else if (ImGui::Button("Shadow")) {
						//Do nothing for now
					}
					else if (ImGui::Button("VFX")) {
						//Do nothing for now
					}
					break;
				case 1:
					if (ImGui::Button("<-")) {
						if (CurrentTest == menuTest) {
							menu_index = 0;
							menuTest->clear();
						}
						else {
							delete CurrentTest;
							CurrentTest = menuTest;
						}
					}
					CurrentTest->onImGUI();
					break;
				}

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
	if (CurrentTest != menuTest)
		delete menuTest;
	return 0;
}
