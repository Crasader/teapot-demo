#include "pch.h"

InputHandler::InputHandler() {
	glfwSetKeyCallback(GLContext::GetContext()->GetGLWindow(), keyboardListener);
}
InputHandler::~InputHandler() {}

void InputHandler::keyboardListener(GLFWwindow* glWindow, int key, int scancode, int action, int mods) {
	
	switch (key) {
	case GLFW_KEY_ENTER:
		if (action == GLFW_PRESS && State::state == State::WAITING) {
			State::state = State::INITIALIZING;
		} else if (action == GLFW_PRESS && State::state == State::EXPLODING) {
			State::state = State::RESETTING;
		}
	}
}

// Increase number of particles
void InputHandler::IncreaseParticles() {
	State::groupsOfParticles++;
	Clamp::ClampRange(State::groupsOfParticles, 2, 500);
}

// Decrease number of particles
void InputHandler::DecreaseParticles() {
	State::groupsOfParticles--;
	Clamp::ClampRange(State::groupsOfParticles, 2, 500);
}

// Set explosion to radial or normal
void ToggleRadialExplosion(bool value) {
	State::radial = value;
}

// Increase slow motion factor
void InputHandler::IncreaseSlowMoFactor() {
	State::slowMotionFactor++;
	Clamp::ClampRange(State::slowMotionFactor, 1.0f, 100.0f);
}

// Decrease slow motion factor
void InputHandler::DecreaseSlowMoFactor() {
	State::slowMotionFactor--;
	Clamp::ClampRange(State::slowMotionFactor, 1.0f, 100.0f);
}