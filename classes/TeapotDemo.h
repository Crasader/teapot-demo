#pragma once
#include "pch.h"

class TeapotDemo {
public:
	TeapotDemo();
	~TeapotDemo();

#pragma once
#include "pch.h"

	// Send the teapot triangles flying
	void ExplodeTeapot(std::vector<Mesh*> teapot, float dt);

	// Subdivide the source mesh into n divisions. Fill target vector with subdivided parts
	void SubdivideTeapot(Mesh*& source, int divisions, std::vector<Mesh*> copies, std::vector<Mesh*>& target);

	void TurnLeftTeapotOn();

	void TurnRightTeapotOn();

	void TurnMiddleTeapotOn();

	void TurnSlicedTeapotOn();

	void TurnTeapotsOff();

	// Turn left teapot on for rendering
	void TurnLeftTeapotOff();

	// Turn left teapot on for rendering
	void TurnRightTeapotOff();

	void InitDemo();

	void RunDemo();

	void Clean();

	GLContext* glContext = nullptr;
	Mesh* platform = nullptr;
	Mesh* teapotSource = nullptr;
	Light* light = nullptr;
	
	std::vector<Mesh*> tempSlices;
	std::vector<Mesh*> teapotSlices;
	std::vector<Mesh*> teapot25Middle;
	std::vector<Mesh*> teapot25Left;
	std::vector<Mesh*> teapot25Right;

	Shader shader;
	Camera camera;
	
	float groundLevel;

	// Use original teapot origin as reference for center
	float originX;
	float originY;
	float originZ;
	glm::vec3 origin;

	Timer timer;

	float gravityEffect = 0.0002f;;
	float gravityIncrease = 0.00015f;;

	bool renderSlices = false;
	bool renderMiddle = false;
	bool renderLeft = false;
	bool renderRight = false;
};

