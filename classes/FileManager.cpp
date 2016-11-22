#include "pch.h"

// Read contents of file and return a string containing results.
std::string FileManager::ReadFile(std::string filename) {

	// String to read one line at a time
	std::string line;

	// Store contents of file in string
	std::string content;

	// Make sure file opens properly
	std::ifstream file(filename);
	if (!file.is_open()) {
		Debug::Log("File did not open properly.");
		std::terminate();
	}

	while (std::getline(file, line)) {
		content += (line + "\n");
	}

	file.close();

	return content;
}

/*
Get data all at once. Not consisently faster.

// Stores contents of file as char array
	char* contentBuffer;

// Get length of file (go to end, get position, return to beginning)
file.seekg(0, file.end);
length = file.tellg();
file.seekg(0, file.beg);

// Read entire file into content
contentBuffer = new char[length];
file.read(contentBuffer, length);
file.close();

// Copy buffer into string. Release buffer to memory
content.append(contentBuffer);
delete[] contentBuffer;
*/