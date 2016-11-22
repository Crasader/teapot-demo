#pragma once
#include "pch.h"

// Logs message to output window
void Debug::Log(std::string message) {
	message += "\n";
	OutputDebugString(message.c_str());
}


