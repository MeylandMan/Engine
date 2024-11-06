#pragma once
#include <glad/glad.h>
#include <math/matrices.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Shader
{
	GLuint id = 0;

	bool loadShaderProgramFromData(const char* vertexShaderData, const char* fragmentShaderData);
	bool loadShaderProgramFromData(const char* vertexShaderData,
		const char* geometryShaderData, const char* fragmentShaderData);

	bool loadShaderProgramFromFile(const char* vertexShader, const char* fragmentShader);
	bool loadShaderProgramFromFile(const char* vertexShader,
		const char* geometryShader, const char* fragmentShader);

	void bind();

	void clear();

	GLint getUniform(const char* name);

	void setUniform1f(const char* name, float arg1);
	void setUniform2f(const char* name, float arg1, float arg2);
	void setUniform3f(const char* name, float arg1, float arg2, float arg3);
	void setUniform4f(const char* name, float arg1, float arg2, float arg3, float arg4);

	void setUniform1i(const char* name, int arg1);
	void setUniform2i(const char* name, int arg1, int arg2);
	void setUniform3i(const char* name, int arg1, int arg2, int arg3);
	void setUniform4i(const char* name, int arg1, int arg2, int arg3, int arg4);

	void setUniform1iv(const char* name, int count, int* arg1);
	void setUniform2iv(const char* name, int count, int* arg1);
	void setUniform3iv(const char* name, int count, int* arg1);
	void setUniform4iv(const char* name, int count, int* arg1);

	void setUniformMatrix4f(const char* name, mat4 arg);

	void setUniform2f(const char* name, vec2 arg);
	void setUniform3f(const char* name, vec3 arg);
	void setUniform4f(const char* name, vec4 arg);

	void setUniformMatrix4f(const char* name, glm::mat4 arg);

	void setUniform2f(const char* name, glm::vec2 arg);
	void setUniform3f(const char* name, glm::vec3 arg);
	void setUniform4f(const char* name, glm::vec4 arg);
};

void setUniform1f(GLuint shaderId, const char* name, float arg1);
void setUniform2f(GLuint shaderId, const char* name, float arg1, float arg2);
void setUniform3f(GLuint shaderId, const char* name, float arg1, float arg2, float arg3);
void setUniform4f(GLuint shaderId, const char* name, float arg1, float arg2, float arg3, float arg4);

void setUniform1i(GLuint shaderId, const char* name, int arg1);
void setUniform2i(GLuint shaderId, const char* name, int arg1, int arg2);
void setUniform3i(GLuint shaderId, const char* name, int arg1, int arg2, int arg3);
void setUniform4i(GLuint shaderId, const char* name, int arg1, int arg2, int arg3, int arg4);

void setUniform1iv(GLuint shaderId, const char* name, int count, int* arg1);
void setUniform2iv(GLuint shaderId, const char* name, int count, int* arg1);
void setUniform3iv(GLuint shaderId, const char* name, int count, int* arg1);
void setUniform4iv(GLuint shaderId, const char* name, int count, int* arg1);

void setUniformMatrix4f(GLuint shaderId, const char* name, mat4 arg);

void setUniform2f(const char* name, vec2 arg);
void setUniform3f(const char* name, vec3 arg);
void setUniform4f(const char* name, vec4 arg);

void setUniformMatrix4f(GLuint shaderId, const char* name, glm::mat4 arg);

void setUniform2f(const char* name, glm::vec2 arg);
void setUniform3f(const char* name, glm::vec3 arg);
void setUniform4f(const char* name, glm::vec4 arg);

GLint getUniform(GLuint shaderId, const char* name);
