#pragma once
#include "pch.h"

Vertex::Vertex(Position p, Color4F c) {
	position = p;
	color.SetColor(c);
}

Vertex::Vertex(float inputX, float inputY, float inputZ, float inputR, 
	           float inputG, float inputB, float inputA, float textureMapX, float textureMapY,
	float normalX, float normalY, float normalZ) {
	position.x = inputX;
	position.y = inputY; 
	position.z = inputZ;
	
	normal.x = normalX;
	normal.y = normalY;
	normal.z = normalZ;

	color.SetColor(inputR, inputG, inputB, inputA);
	textureMap = { textureMapX, textureMapY };
}

Vertex::~Vertex() {}

