#pragma once
#include "pch.h"

class Timer {
public:
	Timer();
	~Timer();

	// Records and updates previousTime, currentTime, and deltaTime
	void Update();

	// Returns time spent between most recent loop
	int GetDeltaTime();

private:

	// Timestamp at previous loop
	int previousTime = 0;

	// Timestamp at current loop
	int currentTime = 0;

	// Time spent between previous and current loop
	int deltaTime = 0;
};

