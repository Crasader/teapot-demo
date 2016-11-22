#pragma once
#include "pch.h"

// Loads, reads, links, and uses shaders in OpenGL context rendering
class Shader {
public:

	// Loads, reads, links, and uses shaders in OpenGL context rendering
	Shader();
	~Shader();

	// Creates shader program for OpenGL rendering loop
	void CreateProgram(std::string vertexFilename, 
		std::string fragmentFilename);

	// Use the shader program during rendering
	void Use();

	// Get Shader Program ID
	int Get_ID();

	// Set a uniform to float value
	void SetUniformFloat(std::string uniformName, float value);

	// Set a uniform int value
	void SetUniformInt(std::string uniformName, int value);

	// Set a uniform bool value
	void SetUniformBool(std::string uniformName, bool value);

	// Set a uniform float Vec2
	void SetUniformVec2Float(std::string uniformName, float valueX, float valueY);

	// Set a uniform int Vec2
	void SetUniformVec2Int(std::string uniformName, int valueX, int valueY);

	// Set a uniform bool Vec2
	void SetUniformVec2Bool(std::string uniformName, bool valueX, bool valueY);

	// Set a uniform float Vec3
	void SetUniformVec3Float(std::string uniformName, float valueX, float valueY, float valueZ);

	// Set a uniform int Vec3
	void SetUniformVec3Int(std::string uniformName, int valueX, int valueY, int valueZ);

	// Set a uniform bool Vec3
	void SetUniformVec3Bool(std::string uniformName, bool valueX, bool valueY, bool valueZ);

	// Set a uniform float Vec4
	void SetUniformVec4Float(std::string uniformName, float valueX, float valueY, float valueZ, float valueW);

	// Set a uniform int Vec4
	void SetUniformVec4Int(std::string uniformName, int valueX, int valueY, int valueZ, int valueW);

	// Set a uniform bool Vec4
	void SetUniformVec4Bool(std::string uniformName, bool valueX, bool valueY, bool valueZ, bool valueW);

private:

	// Returns OpenGL shader object
	int CreateShader(std::string filename, int shaderType, std::string shaderName);
	unsigned int shader_ID;

};

