#include "pch.h"

Mesh::Mesh(std::vector<Vertex> verticesVectorInput, int drawStyleInput,
	std::vector<unsigned int>indicesVectorInput){

	numberOfVertices = verticesVectorInput.size();
	numberOfIndices = indicesVectorInput.size();
	vertices = verticesVectorInput;
	indices = indicesVectorInput;
	drawStyle = drawStyleInput;

	float centerX = 0.0f;
	float centerY = 0.0f;
	float centerZ = 0.0f;

	float leftMostX = 0.0f;
	float rightMostX = 0.0f;
	float bottomMostY = 0.0f;
	float topMostY = 0.0f;
	float backMostZ = 0.0f;
	float forwardMostZ = 0.0f;

	// Create the array for vertex buffer object
	for (int iii = 0; iii < numberOfVertices; iii++) {

		verticesData.push_back(vertices[iii].position.x);
		verticesData.push_back(vertices[iii].position.y);
		verticesData.push_back(vertices[iii].position.z);

		verticesData.push_back(vertices[iii].color.r);
		verticesData.push_back(vertices[iii].color.g);
		verticesData.push_back(vertices[iii].color.b);

		verticesData.push_back(vertices[iii].textureMap.first);
		verticesData.push_back(vertices[iii].textureMap.second);

		verticesData.push_back(vertices[iii].normal.x);
		verticesData.push_back(vertices[iii].normal.y);
		verticesData.push_back(vertices[iii].normal.z);

		// Find most extreme coordinates
		if (vertices[iii].position.x < leftMostX) {
			leftMostX = vertices[iii].position.x;
		}

		if (vertices[iii].position.x > rightMostX) {
			rightMostX = vertices[iii].position.x;
		}

		if (vertices[iii].position.y < bottomMostY) {
			bottomMostY = vertices[iii].position.y;
		}

		if (vertices[iii].position.y > topMostY) {
			topMostY = vertices[iii].position.y;
		}

		if (vertices[iii].position.z < backMostZ) {
			backMostZ = vertices[iii].position.z;
		}

		if (vertices[iii].position.z > forwardMostZ) {
			forwardMostZ = vertices[iii].position.z;
		}
	}

	boundingBox.left = leftMostX;
	boundingBox.right = rightMostX;
	boundingBox.top = topMostY;
	boundingBox.bottom = bottomMostY;
	boundingBox.back = backMostZ;
	boundingBox.front = forwardMostZ;

	center.x = (leftMostX + rightMostX) / 2.0f;
	center.y = (bottomMostY + topMostY) / 2.0f;
	center.z = (backMostZ + forwardMostZ) / 2.0f;

	BindToGLVAOBuffer();
}

// Get a vector of all mesh vertices
std::vector<Vertex> Mesh::GetVertices() {
	return vertices;
}

// Returns the average position of all vertices
Mesh::Center Mesh::GetCenter() {
	return center;
}

// Returns bounding box for mesh
BoundingBox Mesh::GetBoundingBox() {
	return boundingBox;
}

// Load single mesh from .OBJ flle
Mesh* Mesh::CreateMeshFromFile(std::string filename, int drawStyle) {
	
	// Holds desired contents from file
	std::string content;

	// Stores object file data
	std::ifstream file(filename);

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
	while (std::getline(file, content)) {

		// Read vertex coordinate data, set color to default (magenta)
		if (content[0] == 'v' && content[1] == ' ') {
			PositionCoordinates position;
			sscanf_s(content.c_str(), "v %f %f %f\n", &position.x, &position.y, &position.z);
			posCoord.push_back(position);
		}

		// Read texture coordinate data
		if (content[0] == 'v' && content[1] == 't') {
			TextureCoordinates texture;
			sscanf_s(content.c_str(), "vt %f %f\n", &texture.start, &texture.end);
			textCoord.push_back(texture);
		}

		// Read normal coordinate data
		if (content[0] == 'v' && content[1] == 'n') {
			PositionCoordinates position;
			sscanf_s(content.c_str(), "vn %f %f %f\n", &position.x, &position.y, &position.z);
			normCoord.push_back(position);
		}

		// Read index data for triangle vertices
		// Each set of 3 numbers indexes that vertex index to use, texture index to use, and normal index to use
		// NOTE: Index starts at 1 NOT 0.
		if (content[0] == 'f' && content[1] == ' ') {
			int vertexIndex1;
			int textureIndex1;
			int normalIndex1;
			int vertexIndex2;
			int textureIndex2;
			int normalIndex2;
			int vertexIndex3;
			int textureIndex3;
			int normalIndex3;

			// Store index for Vertex triangle
			int matches = sscanf_s(content.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex1, &textureIndex1, &normalIndex1,
				&vertexIndex2, &textureIndex2, &normalIndex2,
				&vertexIndex3, &textureIndex3, &normalIndex3);

			// Make sure the appropriate exists
			if (matches != 9) {
				Debug::Log("The 3D object file was not in an acceptable format.");
				std::terminate();
			}

			vertices.push_back(Vertex(
				posCoord[vertexIndex1 - 1].x, 
				posCoord[vertexIndex1 - 1].y, 
				posCoord[vertexIndex1 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f, 
				textCoord[textureIndex1 - 1].start,
				textCoord[textureIndex1 - 1].end,
				normCoord[normalIndex1 - 1].x,
				normCoord[normalIndex1 - 1].y,
				normCoord[normalIndex1 - 1].z));

			vertices.push_back(Vertex(
				posCoord[vertexIndex2 - 1].x,
				posCoord[vertexIndex2 - 1].y,
				posCoord[vertexIndex2 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f,
				textCoord[textureIndex2 - 1].start,
				textCoord[textureIndex2 - 1].end,
				normCoord[normalIndex2 - 1].x,
				normCoord[normalIndex2 - 1].y,
				normCoord[normalIndex2 - 1].z));

			vertices.push_back(Vertex(
				posCoord[vertexIndex3 - 1].x,
				posCoord[vertexIndex3 - 1].y,
				posCoord[vertexIndex3 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f,
				textCoord[textureIndex3 - 1].start,
				textCoord[textureIndex3 - 1].end,
				normCoord[normalIndex3 - 1].x,
				normCoord[normalIndex3 - 1].y,
				normCoord[normalIndex3 - 1].z));
		}
	}

	return new Mesh(vertices, drawStyle);
}

// Load collection of meshes from .OBJ flle. Returns all the model's individual triangles
std::vector<Mesh*> Mesh::CreateMeshArrayFromFile(std::string filename, int drawStyle) {

	// Vector for mesh points
	std::vector<Mesh*> meshes;

	// Holds desired contents from file
	std::string content;

	// Stores object file data
	std::ifstream file(filename);

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
	while (std::getline(file, content)) {

		// Read vertex coordinate data, set color to default (magenta)
		if (content[0] == 'v' && content[1] == ' ') {
			PositionCoordinates position;
			sscanf_s(content.c_str(), "v %f %f %f\n", &position.x, &position.y, &position.z);
			posCoord.push_back(position);
		}

		// Read texture coordinate data
		if (content[0] == 'v' && content[1] == 't') {
			TextureCoordinates texture;
			sscanf_s(content.c_str(), "vt %f %f\n", &texture.start, &texture.end);
			textCoord.push_back(texture);
		}

		// Read normal coordinate data
		if (content[0] == 'v' && content[1] == 'n') {
			PositionCoordinates position;
			sscanf_s(content.c_str(), "vn %f %f %f\n", &position.x, &position.y, &position.z);
			normCoord.push_back(position);
		}

		// Read index data for triangle vertices
		// Each set of 3 numbers indexes that vertex index to use, texture index to use, and normal index to use
		// NOTE: Index starts at 1 NOT 0.
		if (content[0] == 'f' && content[1] == ' ') {
			int vertexIndex1;
			int textureIndex1;
			int normalIndex1;
			int vertexIndex2;
			int textureIndex2;
			int normalIndex2;
			int vertexIndex3;
			int textureIndex3;
			int normalIndex3;

			// Store index for Vertex triangle
			int matches = sscanf_s(content.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex1, &textureIndex1, &normalIndex1,
				&vertexIndex2, &textureIndex2, &normalIndex2,
				&vertexIndex3, &textureIndex3, &normalIndex3);

			// Make sure the appropriate exists
			if (matches != 9) {
				Debug::Log("The 3D object file was not in an acceptable format.");
				std::terminate();
			}

			vertices.push_back(Vertex(
				posCoord[vertexIndex1 - 1].x,
				posCoord[vertexIndex1 - 1].y,
				posCoord[vertexIndex1 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f,
				textCoord[textureIndex1 - 1].start,
				textCoord[textureIndex1 - 1].end,
				normCoord[normalIndex1 - 1].x,
				normCoord[normalIndex1 - 1].y,
				normCoord[normalIndex1 - 1].z));

			vertices.push_back(Vertex(
				posCoord[vertexIndex2 - 1].x,
				posCoord[vertexIndex2 - 1].y,
				posCoord[vertexIndex2 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f,
				textCoord[textureIndex2 - 1].start,
				textCoord[textureIndex2 - 1].end,
				normCoord[normalIndex2 - 1].x,
				normCoord[normalIndex2 - 1].y,
				normCoord[normalIndex2 - 1].z));

			vertices.push_back(Vertex(
				posCoord[vertexIndex3 - 1].x,
				posCoord[vertexIndex3 - 1].y,
				posCoord[vertexIndex3 - 1].z,
				1.0f, 0.0f, 1.0f, 1.0f,
				textCoord[textureIndex3 - 1].start,
				textCoord[textureIndex3 - 1].end,
				normCoord[normalIndex3 - 1].x,
				normCoord[normalIndex3 - 1].y,
				normCoord[normalIndex3 - 1].z));

			int vertexCount = vertices.size();
			meshes.push_back(new Mesh(std::vector<Vertex>{vertices[vertexCount - 3], vertices[vertexCount - 2], vertices[vertexCount - 1]}, drawStyle));
		}
	}
	return meshes;
}

// Obtain array of vertices Data. Creates OpenGL object reference to it, generates, binds, and stores buffer.
void Mesh::BindToGLVAOBuffer() {

	GLfloat* vertexData = verticesData.data();

	// If given indices, create element buffer object
	// Bind Vertex Array Object to bind Vertex Buffer Object to

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Store reference to mesh's vertex array object
	VAO_ID = VAO;
	glBindVertexArray(VAO);
		
		GLuint VBO;
		glGenBuffers(1, &VBO);

		// Store reference to mesh vertex buffer object
		VBO_ID = VBO;
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Need to convert to equivalent GLfloat array size (GLfloat byte size * elements in vector)
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesData.size(), vertexData, drawStyle);

		// If given indices, create element buffer object
		if (numberOfIndices > 0) {
			GLuint EBO;
			glGenBuffers(1, &EBO);
			EBO_ID = EBO;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numberOfIndices, indices.data(), drawStyle);
		}

		// Set up vertex attribute pointer and array for coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Set up vertex attribute pointer and array for colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Set up vertex attribute pointer and array for textures
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		// Set up vertex attribute pointer and array for normal coordinates
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GL_FLOAT), (GLvoid*)(8 * sizeof(GLfloat)));
		glEnableVertexAttribArray(3);

		// Unbind VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);
}

// Bind to OpenGL Renderer Context for draw calls
void Mesh::BindToGLRenderer(Shader* shader) {
	glBindVertexArray(VAO_ID);
	std::string sz;
	char textureName[13];

	// Bind all textures sequentially, set location for shader
	for (int iii = 0; iii < activeTextures; iii++) {
		sprintf_s(textureName, "textureData%d", iii);
		glActiveTexture(GL_TEXTURE0 + iii);
		glBindTexture(GL_TEXTURE_2D, texture_IDs[iii]);
		GLuint texture = glGetUniformLocation(shader->Get_ID(), textureName);
		glUniform1i(texture, iii);
	}
	Camera* camera = Camera::GetCurrentCamera();

	// Perform transformations if any chang has occured
	if (transform.HasChanged() || (camera && camera->transform.HasChanged())) {
		transform.Update(shader);
	}
}

// Unbind object from OpenGL Renderer
void Mesh::UnbindFromGLRenderer() {

	for (int iii = 0; iii < activeTextures; iii++) {
		glActiveTexture(GL_TEXTURE0 + iii);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// Set texture map coordinates for mesh
void Mesh::SetTextureMap(std::vector<std::pair<float, float>> map) {

	textureMap.clear();

	// There must be equal number of map coordinates to vertices
	if (map.size() != numberOfVertices) {
		Debug::Log("Number of texture map coordinates must equal number of mesh vertices.");
		std::terminate();
	}

	textureMap = map;

	// Remap vertices data
	for (int iii = 0; iii < numberOfVertices; iii++) {
		verticesData[iii * 7] = map[iii].first;
		verticesData[iii * 7 + 1] = map[iii].second;
	}

	// Delete outdate object data
	glDeleteBuffers(1, &VBO_ID);
	glDeleteVertexArrays(1, &VAO_ID);

	// Re-initilize buffer objects
	BindToGLVAOBuffer();
}

// Map a texture to the mesh
void Mesh::MapTexture(std::string filename) {
	
	// Must generate and bind texture object first
	GLuint texture;
	glGenTextures(1, &texture);
	texture_IDs[activeTextures] = texture;

	// All texture settings below will now apply to this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	if (!image) {
		Debug::Log("Texture image failed to load properly.");
		std::terminate();
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	activeTextures++;
}

// Remove texture from the mesh
void Mesh::RemoveTexture(int textureID) {
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(texture_IDs[textureID], 0);
}

// Returns two slices from mesh (verties in front and behind depthZ)
std::vector<Mesh*> Mesh::SliceZ(float depthZ) {
	
	std::vector<Vertex> backVertices;
	std::vector<Vertex> frontVertices;

	for (int iii = 0; iii < numberOfVertices; iii += 3) {

		// Use average value. Push entire triangle (3 consecutive vertices) into vector
		float averageZ = (vertices[iii].position.z + vertices[iii + 1].position.z +
			vertices[iii + 2].position.z) / 3.0f;
		if (averageZ <= depthZ) {
			backVertices.push_back(vertices[iii]);
			backVertices.push_back(vertices[iii + 1]);
			backVertices.push_back(vertices[iii + 2]);
		}

		if (averageZ > depthZ) {
			frontVertices.push_back(vertices[iii]);
			frontVertices.push_back(vertices[iii + 1]);
			frontVertices.push_back(vertices[iii + 2]);
		}
	}

	std::vector<Mesh*> newMeshes;
	newMeshes.push_back(new Mesh(backVertices, drawStyle));
	newMeshes.push_back(new Mesh(frontVertices, drawStyle));

	return newMeshes;
}

// Returns two slices from mesh (vertices above and below heightY)
std::vector<Mesh*> Mesh::SliceX(float heightY) {
	
	std::vector<Vertex> bottomVertices;
	std::vector<Vertex> topVertices;

	for (int iii = 0; iii < numberOfVertices; iii += 3) {

		// Use average value. Push entire triangle (3 consecutive vertices) into vector
		float averageY = (vertices[iii].position.y + vertices[iii + 1].position.y +
			vertices[iii + 2].position.y) / 3.0f;
		if (averageY <= heightY) {
			bottomVertices.push_back(vertices[iii]);
			bottomVertices.push_back(vertices[iii + 1]);
			bottomVertices.push_back(vertices[iii + 2]);
		}

		if (averageY > heightY) {
			topVertices.push_back(vertices[iii]);
			topVertices.push_back(vertices[iii + 1]);
			topVertices.push_back(vertices[iii + 2]);
		}
	}

	std::vector<Mesh*> newMeshes;
	newMeshes.push_back(new Mesh(bottomVertices, drawStyle));
	newMeshes.push_back(new Mesh(topVertices, drawStyle));

	return newMeshes;
}

// Returns two slices from  mesh (verices to the left and right of lineX)
std::vector<Mesh*> Mesh::SliceY(float lineX) {
	
	std::vector<Vertex> leftVertices;
	std::vector<Vertex> rightVertices;

	for (int iii = 0; iii < numberOfVertices; iii += 3) {

		// Use average value. Push entire triangle (3 consecutive vertices) into vector
		float averageX = (vertices[iii].position.x + vertices[iii + 1].position.x +
			vertices[iii + 2].position.x) / 3.0f;
		if (averageX <= lineX) {
			leftVertices.push_back(vertices[iii]);
			leftVertices.push_back(vertices[iii + 1]);
			leftVertices.push_back(vertices[iii + 2]);
		}

		if (averageX > lineX) {
			rightVertices.push_back(vertices[iii]);
			rightVertices.push_back(vertices[iii + 1]);
			rightVertices.push_back(vertices[iii + 2]);
		}
	}

	std::vector<Mesh*> newMeshes;
	newMeshes.push_back(new Mesh(leftVertices, drawStyle));
	newMeshes.push_back(new Mesh(rightVertices, drawStyle));

	return newMeshes;
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO_ID);
	glDeleteBuffers(1, &VBO_ID);
}
