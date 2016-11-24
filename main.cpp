#pragma once
#include "pch.h"

int main() {

	GLContext glContext(1920, 1080, "Teapot Demo");
	InputHandler inputHandler;
	TeapotDemo demo;

	while (!glfwWindowShouldClose(glContext.GetGLWindow())) {
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		demo.RunDemo();
		glfwSwapBuffers(glContext.GetGLWindow());
	}

	demo.Clean();
	glContext.Clean();
	glfwTerminate();
	return 0;
}