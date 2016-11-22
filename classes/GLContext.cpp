#pragma once
#include "pch.h"

GLContext* GLContext::context = nullptr;

// Initialize OpenGL Context
void GLContext::Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

GLContext::GLContext(int width, int height, std::string name) {
	Init();
	glWindow = std::make_shared<GLWindow>(GLWindow(width, height, name));
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		Debug::Log("GLEW failed to initialize properly.");
		std::terminate();
	}

	int glWidth, glHeight;
	glfwGetFramebufferSize(glWindow->GetGLWindow(), &glWidth, &glHeight);
	glViewport(0, 0, width, height);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context = this;
}

// Perform any necessary clean-up tasks
void GLContext::Clean() {
	glWindow->Destroy();
}

GLContext::~GLContext() {
}

// Returns the abstracted GL Window object
std::shared_ptr<GLWindow> GLContext::GetWindow() {
	if (!glWindow) {
		Debug::Log("GL Window was not created.");
		std::terminate();
	}
	return glWindow;
}

// Returns pointer to OpenGL Window
GLFWwindow* GLContext::GetGLWindow() {
	return GetWindow()->GetGLWindow();
}

// Returns context singleton
GLContext* GLContext::GetContext() {
	if (!context) {
		Debug::Log("The OpenGL context was not created.");
		std::terminate();
	}

	return context;
}
