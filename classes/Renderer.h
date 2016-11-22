#pragma once
#include "pch.h"

class Mesh;
class Shader;

// Handles OpenGL Draw calls for meshes
static class Renderer {
public:

	// Adds mesh to buffer, performs draw call based on mesh properties, removes mesh from buffer
	static void Draw(Mesh* mesh, int mode, Shader* shader = nullptr, Light* light = nullptr);
	
	// Returns total number of draw calls before reset
	static int GetDrawCount();

	// Resets counted number of draw calls
	static void ResetDrawCount();

private:

	// Total number of draw calls per loop
	static int drawCount;

};

