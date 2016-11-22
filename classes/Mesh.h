#pragma once
#include "pch.h"

class Renderer;
class Shader;
class Transform;
class BoundingBox;

// Collection of vertices data
class Mesh {
public:

	// Collection of vertices data
	Mesh(std::vector<Vertex> verticesVectorInput, int drawStyleInput, 
		std::vector<unsigned int>indicesVectorInput = std::vector<unsigned int>{});

	// Load mesh from .OBJ flle
	static Mesh* CreateMeshFromFile(std::string filename, int drawStyle);

	static std::vector<Mesh*> CreateMeshArrayFromFile(std::string filename, int drawStyle);

	// Returns two slices from mesh (verties in front and behind depthZ)
	std::vector<Mesh*> SliceZ(float depthZ);

	// Returns two slices from mesh (vertices above and below heightY)
	std::vector<Mesh*> SliceX(float heightY);

	// Returns two slices from  mesh (verices to the left and right of lineX)
	std::vector<Mesh*> SliceY(float lineX);

	struct Center {
		float x;
		float y;
		float z;
	};

	// Get a vector of all mesh vertices
	std::vector<Vertex> GetVertices();

	// Returns the average position of all vertices
	Center GetCenter();

	// Returns bounding box for mesh
	BoundingBox GetBoundingBox();

	// Bind to OpenGL Renderer Context for draw calls
	void BindToGLRenderer(Shader* shader);

	// Unbind object from OpenGL Renderer
	void UnbindFromGLRenderer();

	// Set texture map coordinates for mesh
	void SetTextureMap(std::vector<std::pair<float, float>> map);

	// Map a texture to the mesh
	void MapTexture(std::string filename);

	// Remove texture from the mesh
	void RemoveTexture(int textureID);

	// Performs transform calculations on mesh vertices
	Transform transform;

	~Mesh();

	friend class Renderer;

private:
	Mesh();

	// OpenGL Vertex Buffer Object ID to bind mesh Vertex Buffer Objects
	unsigned int VBO_ID;

	// OpenGL Vertex Array Object ID to bind Vertex Array Objects to Buffer
	unsigned int VAO_ID;

	// OpenGL Texture IDs to bind Texture to Buffer
	unsigned int texture_IDs[16];

	// Number of active textures on object
	unsigned int activeTextures = 0;

	// OpenGL Element Buffer Object ID to bind Element Buffer Object to Buffer
	unsigned int EBO_ID;

	// Total number of vertices in mesh supplied in constructor
	int numberOfVertices;

	// Total number of indices supplied for element buffer object
	int numberOfIndices;

	// OpenGL drawStyle (GL_STAT_DRAW GL_DYNAMIC_DRAW, GL_STREAM_DRAW)
	int drawStyle;

	// How many textures
	// Vector for mesh vertices
	std::vector<Vertex> vertices;

	// Array for mesh vertices positions and colors
	std::vector<float> verticesData;

	// Array of coordinates for texure mapping
	std::vector<std::pair<float, float>> textureMap;

	// Array for indices of overlapping coordinates and draw order
	std::vector<unsigned int> indices;

	// The average position of all vertices
	Center center;

	// Stores bounding box collision data
	BoundingBox boundingBox;

	// Binds mesh to GL_ARRAY_BUFFER
	void BindToGLVAOBuffer();
};

