#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <drivers/opengl_context.h>
#include <iostream>
#include <algorithm>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "../src/tests/TestList.h"

#define USE_GPU_ENGINE 0

#define DEFAULT_FOV 72.f
#define DEFAULT_ZNEAR 0.1f
#define DEFAULT_ZFAR 1000.f

#define MAX_PITCH 90.0f


#define CAMERA_UP vec3(0.0f, 1.0f, 0.0f)
#define CAMERA_DOWN vec3(0.0f, -1.0f, 0.0f)
#define CAMERA_FRONT vec3(0.0f, 0.0f, -1.0f)
#define CAMERA_BACK vec3(0.0f, 0.0f, 1.0f)
#define CAMERA_RIGHT vec3(1.0f, 0.0f, 0.0f)
#define CAMERA_LEFT vec3(-1.0f, 0.0f, 0.0f)

extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}

vec3 cameraPos;
vec3 cameraTarget;

namespace camera {
	vec3 position;
	vec3 Target;

	mat4 view;
	mat4 proj;
}

