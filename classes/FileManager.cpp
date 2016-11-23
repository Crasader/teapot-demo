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

void FileManager::CreateMeshFile(std::string source, std::string destination) {
	// Holds desired contents from file
	std::string line;

	// Stores object file data
	std::ifstream file(source);

	// Whether we've checked match conditions in final part of loop
	bool hasCheckedMatchRequirements = false;
	bool hasTexture = false;
	bool hasNormal = false;
	int requiredMatches = 3; // There must be at least 3 vertices per mesh triangle

	if (!file.is_open()) {
		Debug::Log("Mesh object file did not load properly.");
		std::terminate();
	}

	// Stores vertex position data
	struct PositionCoordinates {
		float x;
		float y;
		float z;
	};

	struct TextureCoordinates {
		float start;
		float end;
	};

	std::vector<PositionCoordinates> posCoord;
	std::vector<TextureCoordinates> textCoord;
	std::vector<PositionCoordinates> normCoord;

	std::vector<Vertex> vertices;

	// Check all lines for relevant information
	while (std::getline(file, line)) {

		// Read vertex coordinate data, set color to default (magenta)
		if (line[0] == 'v' && line[1] == ' ') {
			PositionCoordinates position;
			sscanf_s(line.c_str(), "v %f %f %f\n", &position.x, &position.y,
				&position.z);
			posCoord.push_back(position);
		}

		// Read texture coordinate data
		if (line[0] == 'v' && line[1] == 't') {
			TextureCoordinates texture;
			sscanf_s(line.c_str(), "vt %f %f\n", &texture.start, &texture.end);
			textCoord.push_back(texture);
		}

		// Read normal coordinate data
		if (line[0] == 'v' && line[1] == 'n') {
			PositionCoordinates position;
			sscanf_s(line.c_str(), "vn %f %f %f\n", &position.x, &position.y,
				&position.z);
			normCoord.push_back(position);
		}

		// Read index data for triangle vertices
		// Each set of 3 numbers indexes that vertex index to use, texture index to use, and normal index to use
		// NOTE: Index starts at 1 NOT 0.
		if (line[0] == 'f' && line[1] == ' ') {

			if (!hasCheckedMatchRequirements) {

				if (textCoord.size() > 0) {
					hasTexture = true;
					requiredMatches += 3;
				}
				if (normCoord.size() > 0) {
					hasNormal = true;
					requiredMatches += 3;
				}
				hasCheckedMatchRequirements = true;
			}

			int vertexIndex1;
			int textureIndex1;
			int normalIndex1;
			int vertexIndex2;
			int textureIndex2;
			int normalIndex2;
			int vertexIndex3;
			int textureIndex3;
			int normalIndex3;
			int matches = 0;

			if (hasTexture && hasNormal) {
				// Store index for Vertex triangle
				matches = sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex1, &textureIndex1, &normalIndex1,
					&vertexIndex2, &textureIndex2, &normalIndex2,
					&vertexIndex3, &textureIndex3, &normalIndex3);
			}

			if (hasTexture && !hasNormal) {
				// Store index for Vertex triangle
				matches = sscanf_s(line.c_str(), "f %d/%d/ %d/%d/ %d/%d/\n",
					&vertexIndex1, &textureIndex1,
					&vertexIndex2, &textureIndex2,
					&vertexIndex3, &textureIndex3);
			}

			if (!hasTexture && hasNormal) {
				// Store index for Vertex triangle
				matches = sscanf_s(line.c_str(), "f %d//%d %d//%d %d//%d\n",
					&vertexIndex1, &normalIndex1,
					&vertexIndex2, &normalIndex2,
					&vertexIndex3, &normalIndex3);
			}

			if (!hasTexture && !hasNormal) {
				// Store index for Vertex triangle
				matches = sscanf_s(line.c_str(), "f %d// %d// %d//\n",
					&vertexIndex1, &vertexIndex2, &vertexIndex3);
			}

			// Make sure the appropriate data exists
			if (matches != requiredMatches) {
				Debug::Log("The 3D object file was not in an acceptable format.");
				std::terminate();
			}

			PositionCoordinates pos1 = posCoord[vertexIndex1 - 1];
			PositionCoordinates pos2 = posCoord[vertexIndex2 - 1];;
			PositionCoordinates pos3 = posCoord[vertexIndex3 - 1];

			TextureCoordinates text1;
			TextureCoordinates text2;
			TextureCoordinates text3;

			PositionCoordinates norm1;
			PositionCoordinates norm2;
			PositionCoordinates norm3;

			if (hasTexture) {
				text1 = textCoord[textureIndex1 - 1];
				text2 = textCoord[textureIndex2 - 1];
				text3 = textCoord[textureIndex3 - 1];
			} else {
				text1.start = 0.0f;
				text1.end = 0.0f;
				text2.start = 0.0f;
				text2.end = 0.0f;
				text3.start = 0.0f;
				text3.end = 0.0f;
			}

			if (hasNormal) {
				norm1 = normCoord[normalIndex1 - 1];
				norm2 = normCoord[normalIndex2 - 1];
				norm3 = normCoord[normalIndex3 - 1];
			} else {

				norm1.x = 0.0f;
				norm1.y = 1.0f;
				norm1.z = 0.0f;

				norm2.x = 0.0f;
				norm2.y = 1.0f;
				norm2.z = 0.0f;

				norm3.x = 0.0f;
				norm3.y = 1.0f;
				norm3.z = 0.0f;
			}

			vertices.push_back(Vertex(
				pos1.x, pos1.y, pos1.z,
				1.0f, 0.0f, 1.0f, 1.0f,
				text1.start, text1.end,
				norm1.x, norm1.y, norm1.z));

			vertices.push_back(Vertex(
				pos2.x, pos2.y, pos2.z,
				1.0f, 0.0f, 1.0f, 1.0f,
				text2.start, text2.end,
				norm2.x, norm2.y, norm2.z));

			vertices.push_back(Vertex(
				pos3.x, pos3.y, pos3.z,
				1.0f, 0.0f, 1.0f, 1.0f,
				text3.start, text3.end,
				norm3.x, norm3.y, norm3.z));
		}
	}

	std::string content;
	char buffer[512];
	float r = 1.0f;
	float g = 0.0f;
	float b = 1.0f;
	float a = 1.0f;

	// Write the new file
	std::ofstream writer(destination);
	content = "std::vector<Vertex> MESH {\n";
	writer.write(content.c_str(), content.length());
	writer.flush();

	for (int iii = 0; iii < vertices.size(); iii++) {
		sprintf_s(buffer, "Vertex(%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff)",
			vertices[iii].position.x,
			vertices[iii].position.y,
			vertices[iii].position.z,
			r,g,b,a,
			vertices[iii].textureMap.first,
			vertices[iii].textureMap.second,
			vertices[iii].normal.x,
			vertices[iii].normal.y,
			vertices[iii].normal.z);

		content = buffer;
		if (iii == vertices.size() - 1) {
			content += "};\n";
		} else {
			content += ",\n";
		}
		writer.write(content.c_str(), content.size());
		writer.flush();
	}
	return;
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