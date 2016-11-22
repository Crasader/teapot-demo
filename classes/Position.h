#pragma once
#include "pch.h"

// Holds position data for object
class Position {
public:
	Position();
	~Position();

	// X coordinate
	float x = 0.0f;

	// Y coordinate
	float y = 0.0f;

	// Z coordinate
	float z = 0.0f;

	// Set 3D coordinates for vertex
	void SetPosition(float inputX, float inputY, float inputZ);

	// Set 3D coordinates for vertex
	void SetPosition(Position p);
};