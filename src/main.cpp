#include <../src/main.h>
#include <GLFW/glfw3.h>

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
			camera::position.y += spd;
		else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera::position.y -= spd;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // LEFT
			camera::position.z -= sin(deg_to_rad(look_dir)) * spd;
			camera::position.x -= cos(deg_to_rad(look_dir)) * spd;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // DOWN
			camera::position.z += sin(deg_to_rad(look_dir)) * spd;
			camera::position.x += cos(deg_to_rad(look_dir)) * spd;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // RIGHT
			camera::position.z += cos(deg_to_rad(look_dir)) * spd;
			camera::position.x -= sin(deg_to_rad(look_dir)) * spd;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // UP
			camera::position.z -= cos(deg_to_rad(look_dir)) * spd;
			camera::position.x += sin(deg_to_rad(look_dir)) * spd;
		}
	}
	
}

int main(void)
{

	if (!glfwInit())
		return -1;


#pragma region report opengl errors to std
	//enable opengl debugging output.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion


	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping



	GLFWwindow *window = window = glfwCreateWindow(1280, 720, "Engine", NULL, NULL);
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

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	ImGui::StyleColorsDark();

#pragma region report opengl errors to std
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<test::TestClearColor>("Clear color");
	testMenu->RegisterTest<test::testDrawingCube>("Drawing Cube");

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		//Camera stuffs
		if (is_locked) {
			cursor_position(window);
			
			centerCursorPosition(window);
			camera::Target.x = camera::position.x - cos(deg_to_rad(look_dir));
			camera::Target.y = camera::position.y - sin(deg_to_rad(look_pitch));
			camera::Target.z = camera::position.z - sin(deg_to_rad(look_dir));
		}

		glfwGetFramebufferSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);

		camera::view = LookAt(camera::position, camera::Target, CAMERA_UP);
		camera::proj = Projection(DEFAULT_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, DEFAULT_ZNEAR, DEFAULT_ZFAR);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest) {

			currentTest->onUpdate(deltaTime);
			currentTest->onRender(window, camera::view, camera::proj);
			

			ImGui::Begin("Tests");
			if (currentTest != testMenu && ImGui::Button("<-")) {
				delete currentTest;
				//currentTest->~Test();
				currentTest = testMenu;
			}
			currentTest->onImGUIRender();
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();

			// Rendering
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

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
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
