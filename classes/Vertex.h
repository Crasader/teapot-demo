#pragma once
#include "pch.h"

class Position;

class Vertex {
public:

	// Store 3D coordinates of vertex
	Position position;

	// Data for normal of vertex
	Position normal;

	// Stores color values of vertex
	Color4F color;

	Vertex(Position p, Color4F c);
	Vertex(float inputX = 0.0f, float inputY = 0.0f, float inputZ = 0.0f,
		float inputR = 1.0f, float inputG = 0.0f, float inputB = 1.0f,
		float inputA = 1.0f, float textureMapX = 0.0f, float textureMapY = 0.0f,
		float normalX = 0.0f, float normalY = 1.0f, float normalZ = 0.0f);
	~Vertex();
	
	// Texture map coordinates for vector
	std::pair<float, float> textureMap;
};

