#pragma once
#include "pch.h"

// Registers, checks, and executes callbacks for conditional triggers
class Event {
public:

	// Registers, checks, and executes callbacks for conditional triggers
	Event();
	~Event();

	// Register a callback
	void Register(void(*callback)());

	// Register multiple callbacks
	void Register(std::vector<void(*)()> callback);

	// Check whether event should trigger
	virtual void CheckConditions();

	// Execute all registered callback functions
	void Execute();

private:

	// Vector of registered callbacks
	std::vector<void(*)()> callbacks;
	
};

