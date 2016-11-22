#pragma once
#include "pch.h"

// Forward declarations
struct GLFWwindow;

class GLWindow {
public:

	// Get the Open GL Window
	GLFWwindow* GetGLWindow();

	// Destroy the OpenGL window
	void Destroy();

	// Provide GLContext with access to members / methods
	friend class GLContext;
	
	~GLWindow();

	// Returns width of window
	int GetWidth();

	// Returns height of window
	int GetHeight();
	
	// Returns name of window
	std::string GetName();

private:
	// Create an OpenGL window
	GLWindow(int widthInput, int heightInput, std::string nameInput);
	int width;
	int height;
	int windowHandle;
	static int windowCount;
	std::string name;
	GLFWwindow* glWindow = nullptr;
};

