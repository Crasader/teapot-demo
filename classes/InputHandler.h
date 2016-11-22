#pragma once
#include "pch.h"

class InputHandler {
public:
	InputHandler();
	~InputHandler();

	// Listen for key presses and releases
	static void keyboardListener(GLFWwindow* glWindow, int key, int scancode, int action, int mods);

private:

	// Increase number of particles
	static void IncreaseParticles();

	// Decrease number of particles
	static void DecreaseParticles();

	// Set explosion to radial or normal
	static void ToggleRadialExplosion(bool value);

	// Increase slow motion factor
	static void IncreaseSlowMoFactor();

	// Decrease slow motion factor
	static void DecreaseSlowMoFactor();


};

