#pragma once
#include "pch.h"

// Initialize EventManager singleton to null
EventManager* EventManager::eventManager(nullptr);

EventManager::EventManager() {
	eventManager = this;
}
// Returns EventManager singleton
EventManager* EventManager::GetInstance() {
	if (!eventManager) {
		Debug::Log("Event manager did not initialize properly.");
		std::terminate();
	}
	return eventManager;
}

EventManager::~EventManager() {
}

