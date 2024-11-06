#include <renderer/shader.h>
#include <iostream>
#include <fstream>

//path is used for error reporting
GLint createShaderFromData(const char *data, GLenum shaderType, const char *path = 0)
{
	GLuint shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &data, nullptr);
	glCompileShader(shaderId);

	GLint rezult = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &rezult);

	if (!rezult)
	{
		char *message = 0;
		int   l = 0;

		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &l);

		if (l)
		{
			message = new char[l];

			glGetShaderInfoLog(shaderId, l, &l, message);

			message[l - 1] = 0;

			std::cout << "error compiling shader: ";
			if (path) { std::cout << path; }
			std::cout << "\n" << message << "\n";
			delete[] message;
		}
		else
		{
			if (path) { std::cout << path << " "; }
			std::cout<< "unknown error while compiling shader :(\n";
		}

		glDeleteShader(shaderId);

		shaderId = 0;
		return shaderId;
	}

	return shaderId;
}


GLint createShaderFromFile(const char *name, GLenum shaderType)
{
	std::ifstream f(name);
	std::string str;

	if (!f.is_open())
	{
		std::cout << "Error opening file: " + std::string(name) << "\n";
		return 0;
	}

	f.seekg(0, std::ios::end);
	str.reserve(f.tellg());
	f.seekg(0, std::ios::beg);

	if (str.capacity() <= 0) 
	{
		std::cout << "Error opening file: " + std::string(name) << "\n";
		return 0; 
	}

	str.assign((std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());

	
	auto rez = createShaderFromData(str.c_str(), shaderType, name);

	return rez;
}

bool Shader::loadShaderProgramFromData(const char *vertexShaderData, const char *fragmentShaderData)
{
	auto vertexId = createShaderFromData(vertexShaderData, GL_VERTEX_SHADER);
	auto fragmentId = createShaderFromData(fragmentShaderData, GL_FRAGMENT_SHADER);

	if (vertexId == 0 || fragmentId == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);

	glLinkProgram(id);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		char *message = 0;
		int   l = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);

		message = new char[l];

		glGetProgramInfoLog(id, l, &l, message);

		std::cout << std::string("Link error: ") + message << "\n";

		delete[] message;

		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

bool Shader::loadShaderProgramFromData(const char *vertexShaderData, const char *geometryShaderData, const char *fragmentShaderData)
{
	auto vertexId = createShaderFromData(vertexShaderData, GL_VERTEX_SHADER);
	auto geometryId = createShaderFromData(geometryShaderData, GL_GEOMETRY_SHADER);
	auto fragmentId = createShaderFromData(fragmentShaderData, GL_FRAGMENT_SHADER);

	if (vertexId == 0 || fragmentId == 0 || geometryId == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertexId);
	glAttachShader(id, geometryId);
	glAttachShader(id, fragmentId);

	glLinkProgram(id);

	glDeleteShader(vertexId);
	glDeleteShader(geometryId);
	glDeleteShader(fragmentId);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		char *message = 0;
		int   l = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);

		message = new char[l];

		glGetProgramInfoLog(id, l, &l, message);

		std::cout << std::string("Link error: ") + message << "\n";

		delete[] message;

		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

bool Shader::loadShaderProgramFromFile(const char *vertexShader, const char *fragmentShader)
{

	auto vertexId = createShaderFromFile(vertexShader, GL_VERTEX_SHADER);
	auto fragmentId = createShaderFromFile(fragmentShader, GL_FRAGMENT_SHADER);


	if (vertexId == 0 || fragmentId == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertexId);
	glAttachShader(id, fragmentId);

	glLinkProgram(id);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		char *message = 0;
		int   l = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);

		message = new char[l];

		glGetProgramInfoLog(id, l, &l, message);

		std::cout << std::string("Link error: ") + message << "\n";

		delete[] message;

		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

bool Shader::loadShaderProgramFromFile(const char *vertexShader, const char *geometryShader, const char *fragmentShader)
{
	auto vertexId = createShaderFromFile(vertexShader, GL_VERTEX_SHADER);
	auto geometryId = createShaderFromFile(geometryShader, GL_GEOMETRY_SHADER);
	auto fragmentId = createShaderFromFile(fragmentShader, GL_FRAGMENT_SHADER);

	if (vertexId == 0 || fragmentId == 0 || geometryId == 0)
	{
		return 0;
	}

	id = glCreateProgram();

	glAttachShader(id, vertexId);
	glAttachShader(id, geometryId);
	glAttachShader(id, fragmentId);

	glLinkProgram(id);

	glDeleteShader(vertexId);
	glDeleteShader(geometryId);
	glDeleteShader(fragmentId);

	GLint info = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &info);

	if (info != GL_TRUE)
	{
		char *message = 0;
		int   l = 0;

		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);

		message = new char[l];

		glGetProgramInfoLog(id, l, &l, message);

		std::cout << std::string("Link error: ") + message << "\n";

		delete[] message;

		glDeleteProgram(id);
		id = 0;
		return 0;
	}

	glValidateProgram(id);

	return true;
}

void Shader::bind()
{
	glUseProgram(id);
}

void Shader::clear()
{
	glDeleteProgram(id);
	id = 0;
}

GLint Shader::getUniform(const char *name)
{
	return ::getUniform(this->id, name);
}

GLint getUniform(GLuint shaderId, const char *name)
{
	GLint uniform = glGetUniformLocation(shaderId, name);
	if (uniform == -1)
	{
		std::cout << "uniform error " + std::string(name);
	}
	return uniform;
}

// ---- Modifying a Uniform
void Shader::setUniform1f(const char* name, float arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform1f(location, arg1);
}

void Shader::setUniform2f(const char* name, float arg1, float arg2) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform2f(location, arg1, arg2);
}

void Shader::setUniform2f(const char* name, vec2 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform2f(location, arg.x, arg.y);
}

void Shader::setUniform2f(const char* name, glm::vec2 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform2f(location, arg.x, arg.y);
}

void Shader::setUniform3f(const char* name, float arg1, float arg2, float arg3) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform3f(location, arg1, arg2, arg3);
}

void Shader::setUniform3f(const char* name, vec3 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform3f(location, arg.x, arg.y, arg.z);
}

void Shader::setUniform4f(const char* name, float arg1, float arg2, float arg3, float arg4) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform4f(location, arg1, arg2, arg3, arg4);
}

void Shader::setUniform4f(const char* name, vec4 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform4f(location, arg.x, arg.y, arg.z, arg.w);
}

void Shader::setUniform3f(const char* name, glm::vec3 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform3f(location, arg.x, arg.y, arg.z);
}

void Shader::setUniform4f(const char* name, glm::vec4 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform4f(location, arg.x, arg.y, arg.z, arg.w);
}

void setUniform1f(GLuint shaderId, const char* name, float arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform1f(location, arg1);
}

void setUniform2f(GLuint shaderId, const char* name, float arg1, float arg2) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform2f(location, arg1, arg2);
}

void setUniform3f(GLuint shaderId, const char* name, float arg1, float arg2, float arg3) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform3f(location, arg1, arg2, arg3);
}

void setUniform4f(GLuint shaderId, const char* name, float arg1, float arg2, float arg3, float arg4) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform4f(location, arg1, arg2, arg3, arg4);
}

void setUniform2f(GLuint shaderId, const char* name, vec2 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform2f(location, arg.x, arg.y);
}

void setUniform3f(GLuint shaderId, const char* name, vec3 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform3f(location, arg.x, arg.y, arg.z);
}

void setUniform4f(GLuint shaderId, const char* name, vec4 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform4f(location, arg.x, arg.y, arg.z, arg.w);
}

void setUniform2f(GLuint shaderId, const char* name, glm::vec2 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform2f(location, arg.x, arg.y);
}

void setUniform3f(GLuint shaderId, const char* name, glm::vec3 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform3f(location, arg.x, arg.y, arg.z);
}

void setUniform4f(GLuint shaderId, const char* name, glm::vec4 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform4f(location, arg.x, arg.y, arg.z, arg.w);
}

void Shader::setUniform1i(const char* name, int arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform1i(location, arg1);
}

void Shader::setUniform2i(const char* name, int arg1, int arg2) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform2i(location, arg1, arg2);
}

void Shader::setUniform3i(const char* name, int arg1, int arg2, int arg3) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform3i(location, arg1, arg2, arg3);
}

void Shader::setUniform4i(const char* name, int arg1, int arg2, int arg3, int arg4) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform4i(location, arg1, arg2, arg3, arg4);
}

void Shader::setUniform1iv(const char* name, int count, int* arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform1iv(location, count, arg1);

}

void Shader::setUniform2iv(const char* name, int count, int* arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform2iv(location, count, arg1);
}

void Shader::setUniform3iv(const char* name, int count, int* arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform3iv(location, count, arg1);
}

void Shader::setUniform4iv(const char* name, int count, int* arg1) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniform4iv(location, count, arg1);
}


void setUniform1i(GLuint shaderId, const char* name, int arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform1i(location, arg1);
}

void setUniform2i(GLuint shaderId, const char* name, int arg1, int arg2) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform2i(location, arg1, arg2);
}

void setUniform3i(GLuint shaderId, const char* name, int arg1, int arg2, int arg3) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform3i(location, arg1, arg2, arg3);
}

void setUniform4i(GLuint shaderId, const char* name, int arg1, int arg2, int arg3, int arg4) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform4i(location, arg1, arg2, arg3, arg4);
}

void setUniform1iv(GLuint shaderId, const char* name, int count, int* arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform1iv(location, count, arg1);

}

void setUniform2iv(GLuint shaderId, const char* name, int count, int* arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform2iv(location, count, arg1);
}

void setUniform3iv(GLuint shaderId, const char* name, int count, int* arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform3iv(location, count, arg1);
}

void setUniform4iv(GLuint shaderId, const char* name, int count, int* arg1) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniform4iv(location, count, arg1);
}

// ------ END ------
void Shader::setUniformMatrix4f(const char* name, mat4 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniformMatrix4fv(location, 1, GL_TRUE, arg.asArray);
}

void Shader::setUniformMatrix4f(const char* name, glm::mat4 arg) {
	int location = getUniform(name);
	_ASSERT(location != -1);
	glUniformMatrix4fv(location, 1, GL_TRUE, &arg[0][0]);
}

void setUniformMatrix4f(GLuint shaderId, const char* name, mat4 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniformMatrix4fv(location, 1, GL_TRUE, arg.asArray);
}

void setUniformMatrix4f(GLuint shaderId, const char* name, glm::mat4 arg) {
	int location = getUniform(shaderId, name);
	_ASSERT(location != -1);
	glUniformMatrix4fv(location, 1, GL_TRUE, &arg[0][0]);
}