#pragma once
#include "pch.h"

// Stores data on object's collision boundaries
class BoundingBox {
public:

	// Stores data on object's collision boundaries
	BoundingBox();
	~BoundingBox();

	// Bottom of mesh bounding box
	float bottom;

	// Top of mesh bounding box
	float top;

	// Front of mesh bounding box
	float front;

	// Back of mesh bounding box
	float back;

	// Left of mesh bounding box
	float left;

	// Right of mesh bounding box
	float right;
};

