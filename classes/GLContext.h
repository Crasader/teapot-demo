#pragma once
#include "pch.h"

class GLContext {
public:

	// Create the OpenGL Context object. Create OpenGL Window and link to current context
	GLContext(int width, int height, std::string name);

	// Perform any necessary clean-up tasks
	void Clean();

	~GLContext();

	// Returns the abstracted GL Window object
	std::shared_ptr<GLWindow> GetWindow();

	// Returns pointer to OpenGL Window
	GLFWwindow* GetGLWindow();

	// Returns context singleton
	static GLContext* GetContext();

private:

	// Initialize OpenGL Context
	void Init();

	// The OpenGL Window for the program
	std::shared_ptr<GLWindow> glWindow = nullptr;

	void(*BufferOffset)(int);

	static GLContext* context;
};

