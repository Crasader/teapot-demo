#pragma once
#include "pch.h"

class Light : public Mesh {
public:
	Light(float r = 1.0f, float g = 1.0f, float b = 1.0f);
	~Light();

	// Color of the light source
	Color4F color;

	// Set ambient strength of light
	void SetAmbientStrength(float strength);

	// Get ambient strength of light
	float GetAmbientStrength();

	// Cubic representation of light to help with visualizing source
//	Mesh* lightCube = nullptr;

	// Whether to render cubic representation of light
	bool renderCube = false;

private:

	// Ambient strength of light
	float ambientStrength = 1.0f;

};

