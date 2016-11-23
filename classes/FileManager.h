#pragma once
#include "pch.h"

// Handles reading and writing of files
static class FileManager {
public:
	
	// Read contents of file and return a string containing results.
	static std::string ReadFile(std::string filename);

	static void CreateMeshFile(std::string source, std::string destination);

};

