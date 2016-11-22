#include "pch.h"

// Registers, checks, and executes callbacks for conditional triggers
Event::Event() {}
Event::~Event() {}

// Register a callback
void Event::Register(void(*callback)()) {
	callbacks.push_back(callback);
}

// Register multiple callbacks
void Event::Register(std::vector<void(*)()> callback) {
	for (int iii = 0; iii < callback.size(); iii++) {
		callbacks.push_back(callback[iii]);
	}
}

// Execute all registered callback functions
void Event::Execute() {
	for (int iii = 0; iii < callbacks.size(); iii++) {
		callbacks[iii]();
	}
}

// Check whether event should trigger
void Event::CheckConditions() {

}