#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <renderer/renderer.h>
#include <renderer/openglDebug.h>
#include <renderer/shader.h>
#include <Camera.h>
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


Camera cam(glm::vec3(0.f, 0.f, 3.f));
//vec3 Camera;
//vec3 TargetTo;

int WINDOW_WIDTH = 0, WINDOW_HEIGHT = 0;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool firstMouse = true;
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;

bool is_locked = false;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (is_locked) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cam.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cam.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cam.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cam.ProcessKeyboard(RIGHT, deltaTime);
	}
	

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (is_locked) {
		cam.ProcessMouseMovement(xoffset, yoffset);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.ProcessMouseScroll(static_cast<float>(yoffset));
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		is_locked = !is_locked;
	}

	if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
		// FullScreen
	}
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Maber", NULL, NULL); //Maber stand for Magical Number
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	glm::mat4 view;
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

		processInput(window);
		glfwPollEvents();
		if (is_locked) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

		view = cam.GetViewMatrix();
		deltaTime = 1/io.Framerate;
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			
			
			if (CurrentTest) {
				CurrentTest->onUpdate(deltaTime);

				
				renderer.Clear();
				CurrentTest->onRender(window, renderer, &view, &cam);

				ImGui::Begin("Test");

				ImGui::Text("Camera Position : Vector3(%.1f, %.1f, %.1f)", cam.Position.x, cam.Position.y, cam.Position.z);
				ImGui::Text("Camera Direction : Vector3(%.1f, %.1f, %.1f)", cam.Front.x, cam.Front.y, cam.Front.z);
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
						menuTest->RegisterTest<test::TestBasicLights>("Multiple lights");
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
