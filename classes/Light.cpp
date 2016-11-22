#include "pch.h"

Light::Light(float r, float g, float b) : Mesh(
	std::vector<Vertex>{
		Vertex(-0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 0 FRONT Top Left
		Vertex(-0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 1 FRONT Bottom Left
		Vertex(0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 2 FRONT Bottom Right
		
		// FRONT TOP TRIANGLE
		Vertex(0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 3 FRONT Bottom Right
		Vertex(0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 4 FRONT Top Right
		Vertex(-0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 5 FRONT Top Left

		// BACK BOTTOM TRIANGLE
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 6 BACK Top Left
		Vertex(-0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 7 BACK Bottom Left
		Vertex(0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 8 BACK Bottom Right

		// BACK TOP TRIANGLE
		Vertex(0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 9 BACK Bottom Right
		Vertex(0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 10 BACK Top Right
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 11 BACK Top Left

		// LEFT BOTTOM TRIANGLE
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 12 LEFT Top Left 
		Vertex(-0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 13 LEFT Bottom Left
		Vertex(-0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 14 LEFT Bottom Right

		// LEFT TOP TRIANGLE
		Vertex(-0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 15 LEFT Bottom Right
		Vertex(-0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 16 LEFT Top Right
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 17 LEFT Top Left 

		// RIGHT BOTTOM TRIANGLE
		Vertex(0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 18 RIGHT Top Left
		Vertex(0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 19 RIGHT Bottom Left
		Vertex(0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 20 RIGHT Bottom Right

		// RIGHT TOP TRIANLE
		Vertex(0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 21 RIGHT Bottom Right
		Vertex(0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 22 RIGHT Top Right
		Vertex(0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 23 RIGHT Top Left

		// TOP BOTTOM TRIANGLE
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 24 TOP Top Left
		Vertex(-0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 25 TOP Bottom Left
		Vertex(0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 26 TOP Bottom Right

		// TOP TOP TRIANGLE
		Vertex(0.1f, 0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 27 TOP Bottom Right
		Vertex(0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 28 TOP Top Right
		Vertex(-0.1f, 0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 29 TOP Top Left

		// BOTTOM BOTTOM TRIANGLE
		Vertex(-0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f), // 30 BOTTOM Top Left
		Vertex(-0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 0.0f, 0.0f), // 31 BOTTOM Bottom Left
		Vertex(0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 32 BOTTOM Bottom Right

		// BOTTOM TOP TRIANGLE
		Vertex(0.1f, -0.1f, 0.1f, r, g, b, 1.0f, 1.0f, 0.0f), // 33 BOTTOM Bottom Right
		Vertex(0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 1.0f, 1.0f), // 34 BOTTOM Top Right
		Vertex(-0.1f, -0.1f, -0.1f, r, g, b, 1.0f, 0.0f, 1.0f) // 35 BOTTOM Top Left

	}, GL_STREAM_DRAW) {
}
Light::~Light() {}

// Set ambient strength of light
void Light::SetAmbientStrength(float strength) {
	Clamp::ClampRange(strength, 0.0f, 1.0f);
	ambientStrength = strength;
}

// Get ambient strength of light
float Light::GetAmbientStrength() {
	return ambientStrength;
}
