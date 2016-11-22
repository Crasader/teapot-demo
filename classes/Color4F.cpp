#include "pch.h"

Color4F::Color4F() {
	r = 1.0f;
	g = 0.0f;
	b = 1.0f;
	a = 1.0f;
}
Color4F::~Color4F() {}

// Holds color values for objects
Color4F::Color4F(float inputR, float inputG, float inputB, float inputA) {
	SetColor(inputR, inputG, inputB, inputA);
}

// Set color for vertex
void Color4F::SetColor(float inputR, float inputG, float inputB,
	float inputA) {
	r = inputR;
	g = inputG;
	b = inputB;
	a = inputA;
	
	Clamp::ClampRange(r, 0.0f, 1.0f);
	Clamp::ClampRange(g, 0.0f, 1.0f);
	Clamp::ClampRange(b, 0.0f, 1.0f);
	Clamp::ClampRange(a, 0.0f, 1.0f);
}

// Set color for vertex
void Color4F::SetColor(Color4F color) {
	r = color.r;
	g = color.g;
	b = color.b;
	a = color.a;
	
	Clamp::ClampRange(r, 0.0f, 1.0f);
	Clamp::ClampRange(g, 0.0f, 1.0f);
	Clamp::ClampRange(b, 0.0f, 1.0f);
	Clamp::ClampRange(a, 0.0f, 1.0f);
}

// Get color
Color4F Color4F::GetColor() {
	return *this;
}