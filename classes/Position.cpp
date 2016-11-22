#include "pch.h"

Position::Position() {}
Position::~Position() {}

// Set 3D coordinates for vertex
void Position::SetPosition(float inputX, float inputY, float inputZ) {
	x = inputX;
	y = inputY;
	z = inputZ;
	
	Clamp::ClampRange(x, 0.0f, 1.0f);
	Clamp::ClampRange(y, 0.0f, 1.0f);
	Clamp::ClampRange(z, 0.0f, 1.0f);
}

// Set 3D coordinates for vertex
void Position::SetPosition(Position p) {
	x = p.x;
	y = p.y;
	z = p.z;
	
	Clamp::ClampRange(x, 0.0f, 1.0f);
	Clamp::ClampRange(y, 0.0f, 1.0f);
	Clamp::ClampRange(z, 0.0f, 1.0f);
}