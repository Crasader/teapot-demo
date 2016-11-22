#pragma once
#include "pch.h"

// Holds color values for objects
class Color4F {
public:
	// Holds color values for objects
	Color4F();
	~Color4F();

	// Holds color values for objects
	Color4F(float inputR, float inputG, float inputB, float inputA = 1.0f);

	// Set color
	void SetColor(float inputR, float inputG, float inputB, float inputA = 1.0f);

	// Set color
	void SetColor(Color4F c);

	// Returns color object
	Color4F GetColor();

	// Red color value. Must be between 0.0f and 1.0f
	float r = 1.0f;

	// Green color value. Must be between 0.0f and 1.0f
	float g = 0.0f;

	// Blue color value. Must be between 0.0f and 1.0f
	float b = 1.0f;

	// Alpha color value. Must be between 0.0f and 1.0f
	float a = 1.0f;
};

