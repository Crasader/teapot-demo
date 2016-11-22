#pragma once
#include "pch.h"

Timer::Timer() {}
Timer::~Timer() {}

// Records and updates previousTime, currentTime, and deltaTime
void Timer::Update() {

	auto epoch = std::chrono::steady_clock::now().time_since_epoch();
	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

	// Previous time should now equal the last recorded time
	previousTime = currentTime;
	currentTime = (int)(time);
	deltaTime = currentTime - previousTime;
}

// Returns time spent between most recent loop
int Timer::GetDeltaTime() {
	Update();
	return deltaTime;
}