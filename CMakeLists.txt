cmake_minimum_required(VERSION 3.26.0)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") #we want to use the static runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project(myengine)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw-3.3.2)			#window oppener
add_subdirectory(thirdparty/glad)				#opengl loader
add_subdirectory(thirdparty/stb_image)			#image loader
add_subdirectory(thirdparty/stb_truetype)		#ttf files loader
add_subdirectory(thirdparty/glm)				#math
add_subdirectory(thirdparty/imgui-docking)		#ui
add_subdirectory(thirdparty/assimp-5.4.3)		#Model Loader
add_subdirectory(thirdparty/fastgltf-0.8.0)		

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 23)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the game

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADERS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC VERTEX_SHADER="/vertex.vert")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC FRAGMENT_SHADER="/fragment.frag")

#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC SHADERS_PATH="./shaders/")
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC VERTEX_SHADER="./vertex.vert")
#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC FRAGMENT_SHADER="./fragment.frag")

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})


if(MSVC) # If using the VS compiler...

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)

	#remove console
	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

endif()


target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw 
	glad stb_image stb_truetype imgui assimp fastgltf )

