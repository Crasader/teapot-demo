#pragma once
#include "pch.h"

int GLWindow::windowCount = 0;

// Get the Open GL Window
GLFWwindow* GLWindow::GetGLWindow() {

	if (!glWindow) {
		Debug::Log("GL Window was not created.");
		std::terminate();
	}

	return glWindow;
}

// Destroy OpenGL Window
void GLWindow::Destroy() {
	glfwDestroyWindow(glWindow);
	windowCount--;
}

// Create an OpenGL window
GLWindow::GLWindow(int widthInput, int heightInput, std::string nameInput) {
	// Create OpenGL Window
	glWindow = glfwCreateWindow(widthInput, heightInput,
		nameInput.c_str(), nullptr, nullptr);
	
	if (!glWindow) {
		Debug::Log("GL Window was not created.");
		std::terminate();
	}

	glfwMakeContextCurrent(glWindow);
	width = widthInput;
	height = heightInput;
	name = nameInput;
	windowHandle = windowCount;
	windowCount++;
}

GLWindow::~GLWindow() {
}

// Returns width of window
int GLWindow::GetWidth() {
	return width;
}

// Returns height of window
int GLWindow::GetHeight() {
	return height;
}

// Returns name of window
std::string GLWindow::GetName() {
	return name;
}
