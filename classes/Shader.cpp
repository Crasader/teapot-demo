#include "pch.h"

// Loads, reads, and links shaders to OpenGL context
Shader::Shader() {}
Shader::~Shader() {
	glDeleteProgram(shader_ID);
}

// Creates shader program for OpenGL rendering loop
void Shader::CreateProgram(std::string vertexFilename, std::string fragmentFilename) {

	GLuint vertexShader = CreateShader(vertexFilename, GL_VERTEX_SHADER, "name");
	GLuint fragmentShader = CreateShader(fragmentFilename, GL_FRAGMENT_SHADER, "name");
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	shader_ID = shaderProgram;
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check that the program linked properly
	GLint success;
	GLchar log;

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		Debug::Log("The OpenGL shader program did not link properly.");
		glGetProgramInfoLog(shaderProgram, 512, nullptr, &log);
		std::terminate();
	}

	// Release objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Returns OpenGL shader object
void Shader::Use() {
	glUseProgram(shader_ID);
}

// Get Shader Program ID
int Shader::Get_ID() {
	return shader_ID;
}

// Returns OpenGL shader object
int Shader::CreateShader(std::string filename, int shaderType, std::string shaderName) {

	std::string content = FileManager::ReadFile(filename);
	const GLchar* source = content.c_str();
	GLuint shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	// Make sure shader compiled properly
	GLint success;
	GLchar log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
		Debug::Log("Shader did not compile properly.");
		Debug::Log(log);
		std::terminate();
	}

	return shader;
}

// Set a uniform to float value
void Shader::SetUniformFloat(std::string uniformName, float value) {
	
	GLfloat x = value;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());

	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform1f(uniformLocation, x);
}

// Set a uniform int value
void Shader::SetUniformInt(std::string uniformName, int value) {
	
	GLint x = value;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform1i(uniformLocation, x);
}

// Set a uniform bool value
void Shader::SetUniformBool(std::string uniformName, bool value) {
	
	GLint x = value;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform1i(uniformLocation, x);
}

// Set a uniform float Vec2
void Shader::SetUniformVec2Float(std::string uniformName, float valueX, float valueY) {

	GLfloat x = valueX;
	GLfloat y = valueY;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform2f(uniformLocation, x, y);
}

// Set a uniform int Vec2
void Shader::SetUniformVec2Int(std::string uniformName, int valueX, int valueY) {

	GLint x = valueX;
	GLint y = valueY;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform2i(uniformLocation, x, y);
}

// Set a uniform bool Vec2
void Shader::SetUniformVec2Bool(std::string uniformName, bool valueX, bool valueY) {

	GLint x = valueX;
	GLint y = valueY;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform2i(uniformLocation, x, y);
}

// Set a uniform float Vec3
void Shader::SetUniformVec3Float(std::string uniformName, float valueX, float valueY, float valueZ) {

	GLfloat x = valueX;
	GLfloat y = valueY;
	GLfloat z = valueZ;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform3f(uniformLocation, x, y, z);
}

// Set a uniform int Vec3
void Shader::SetUniformVec3Int(std::string uniformName, int valueX, int valueY, int valueZ) {

	GLint x = valueX;
	GLint y = valueY;
	GLint z = valueZ;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform3i(uniformLocation, x, y, z);
}

// Set a uniform bool Vec3
void Shader::SetUniformVec3Bool(std::string uniformName, bool valueX, bool valueY, bool valueZ) {

	GLint x = valueX;
	GLint y = valueY;
	GLint z = valueZ;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform3i(uniformLocation, x, y, z);
}

// Set a uniform float Vec4
void Shader::SetUniformVec4Float(std::string uniformName, float valueX, float valueY, float valueZ, float valueW) {
	
	GLfloat x = valueX;
	GLfloat y = valueY;
	GLfloat z = valueZ;
	GLfloat w = valueW;
	
	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform4f(uniformLocation, x, y, z, w);
}

// Set a uniform int Vec4
void Shader::SetUniformVec4Int(std::string uniformName, int valueX, int valueY, int valueZ, int valueW) {
	
	GLint x = valueX;
	GLint y = valueY;
	GLint z = valueZ;
	GLint w = valueW;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform4i(uniformLocation, x, y, z, w);
}

// Set a uniform bool Vec4
void Shader::SetUniformVec4Bool(std::string uniformName, bool valueX, bool valueY, bool valueZ, bool valueW) {
	
	GLint x = valueX;
	GLint y = valueY;
	GLint z = valueZ;
	GLint w = valueW;

	GLint uniformLocation = glGetUniformLocation(shader_ID, uniformName.c_str());
	if (uniformLocation == -1) {
		Debug::Log("Failed to locate the shader uniform variable or variable is not used in shader program.");
		std::terminate();
	}
	glUseProgram(shader_ID);
	glUniform4i(uniformLocation, x, y, z, w);
}