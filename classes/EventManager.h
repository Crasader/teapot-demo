#pragma once
#include "pch.h"

class EventManager {
public:
	~EventManager();

	// Returns EventManager singleton
	static EventManager* GetInstance(); // ONLY HERE. NOT NEEDED FOR EVENTS

private:

	EventManager();

	// Singleton EventManager
	static EventManager* eventManager;

	// Vector for all events
	std::vector<Event> events;
};

