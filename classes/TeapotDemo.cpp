#pragma once
#include "pch.h"

TeapotDemo::TeapotDemo() {
	InitDemo();
}

TeapotDemo::~TeapotDemo() {}

// Send the teapot triangles flying
void TeapotDemo::ExplodeTeapot(std::vector<Mesh*> teapot, float dt) {
	
	for (int iii = 0; iii < teapot.size(); iii++) {
		float force = 0.01f * dt;

		float x = teapot[iii]->GetCenter().x;
		float y = teapot[iii]->GetCenter().y;
		float z = teapot[iii]->GetCenter().z;
		glm::vec3 trajectory = glm::normalize(glm::vec3(x, y, z));
		trajectory *= force;
		float back = -1.0f;
		float front = 1.0f;
		float ground = -0.01f;
		float left = -0.5f;
		float right = 0.5f;

		if (!State::closeUp) {
			trajectory.y -= gravityEffect;

			// Stop at "floor"
			if (teapot[iii]->GetBoundingBox().bottom <= ground) {
				trajectory.y = 0;
			}
		}

		if (!State::radial) {

			int xyDirection;
			int yzDirection;

			if (trajectory.z > 0.0f) {
				xyDirection = 1;
			} else {
				xyDirection = -1;
			}

			if (trajectory.x > 0.0f) {
				yzDirection = 1;
			} else {
				yzDirection = -1;
			}

			float rotationFactor = 0.0f;

			if (State::normalSpeed) {
				rotationFactor = 0.5f;
			} else if (State::slowSpeed) {
				rotationFactor = 0.25f;
			} else if (State::slowerSpeed) {
				rotationFactor = 0.1f;
			}

			teapot[iii]->transform.RotateXY(
				(rotationFactor * 500.0f) *
				force * xyDirection * (rand() % 10) /
				State::groupsOfParticles);
			teapot[iii]->transform.RotateYZ(
				(rotationFactor * 500.0f) *
				force * yzDirection * (rand() % 10) / 
				State::groupsOfParticles);
		}
		teapot[iii]->transform.Translate(trajectory.x, trajectory.y, trajectory.z);
		Renderer::Draw(teapot[iii], GL_TRIANGLES, &shader, light);
	}
}

// Subdivide the source mesh into n divisions. Fill target vector with subdivided parts
void TeapotDemo::SubdivideTeapot(Mesh*& source, int divisions, std::vector<Mesh*> copies, std::vector<Mesh*>& target) {

	target.push_back(source);
	bool sliceStart = true;
	bool sliceEnd = false;
	bool sliceX = true;
	bool sliceY = false;
	int start = 0;
	int end = target.size();
	int meshesAdded = 0;

	for (int iii = 0; iii < divisions; iii++) {

		// Slice from edges of vector torward center
		// True after every initial partition has been sliced
		if (start == end || iii == divisions - 1) {

			// Get rid of old meshes
			for (int jjj = 0; jjj < meshesAdded; jjj++) {

				// Make sure not to delete original teapot
				if (target[jjj] != source) {
					target[jjj]->UnbindFromGLRenderer();
					delete target[jjj];
				}
			}

			// Erase unnecessary divisions in beginning of vector (only used to ordering slices)
			target.erase(target.begin(), target.begin() + meshesAdded);

			// Stop cycling after number of required divisions is met
			if (iii == divisions - 1) {
				break;
			}

			start = 0;
			meshesAdded = 0;
			end = target.size();

			// Alternate slice method after slicing all existing groups
			if (sliceX) {
				sliceX = false;
				sliceY = true;
			} else if (sliceY) {
				sliceX = true;
				sliceY = false;
			}
		}

		// Slice all existing groups, alternating between beginning and end of vector towards center

		if (sliceStart) {
			if (sliceY) {
				copies = target[start]->SliceY(target[start]->GetCenter().x);
			}
			if (sliceX) {
				copies = target[start]->SliceX(target[start]->GetCenter().y);
			}
			start++;
			meshesAdded++;
		}

		if (sliceEnd) {
			if (sliceY) {
				copies = target[end - 1]->SliceY(target[end - 1]->GetCenter().x);
			}
			if (sliceX) {
				copies = target[end - 1]->SliceX(target[end - 1]->GetCenter().y);
			}
			end--;
			meshesAdded++;
		}

		// Add new mesh slices to front of vector

		if (copies[0]->GetVertices().size() > 0) {
			target.push_back(copies[0]);
		} else {
			copies[0]->UnbindFromGLRenderer();
			delete copies[0];
			meshesAdded--;
		}

		if (copies[1]->GetVertices().size() > 0) {
			target.push_back(copies[1]);
		} else {
			copies[1]->UnbindFromGLRenderer();
			delete copies[1];
			meshesAdded--;
		}
		copies.clear();

		// Alternate which end of vector to slice
		if (sliceStart) {
			sliceStart = false;
			sliceEnd = true;
		} else if (sliceEnd) {
			sliceEnd = false;
			sliceStart = true;
		}
	}

	for (int iii = 0; iii < target.size(); iii++) {
		target[iii]->transform = source->transform;
	}
}

void TeapotDemo::TurnLeftTeapotOn() {
	for (int iii = 0; iii < teapot25Right.size(); iii++) {
		teapot25Right[iii]->transform = teapotSource->transform;
		teapot25Right[iii]->transform.Translate(0.9f, 0.0f, 0.0f);
		teapot25Right[iii]->transform.RotateXZ(30.0f);
	}
	renderLeft = true;
}

void TeapotDemo::TurnRightTeapotOn() {
	for (int iii = 0; iii < teapot25Right.size(); iii++) {
		teapot25Left[iii]->transform = teapotSource->transform;
		teapot25Left[iii]->transform.Translate(-0.9f, 0.0f, 0.0f);
		teapot25Left[iii]->transform.RotateXZ(-20.0f);
	}
	renderRight = true;
}

void TeapotDemo::TurnMiddleTeapotOn() {
	for (int iii = 0; iii < teapot25Middle.size(); iii++) {
		teapot25Middle[iii]->transform = teapotSource->transform;
	}
	renderMiddle = true;
}

void TeapotDemo::TurnSlicedTeapotOn() {
	for (int iii = 0; iii < teapot25Middle.size(); iii++) {
		teapotSlices[iii]->transform = teapotSource->transform;
	}
	renderSlices = true;
}

void TeapotDemo::TurnTeapotsOff() {
	renderLeft = false;
	renderRight = false;
	renderMiddle = false;
	renderSlices = false;
}

void TeapotDemo::RunDemo() {
	float dt = (float)(timer.GetDeltaTime()) / (State::slowMotionFactor);

	if (State::state == State::INITIALIZING) {

		// CLOSE UP VIEW MODE
		if (State::closeUp) {

			if (State::normalSpeed) {
				State::slowMotionFactor = 10.0f;
			}
			if (State::slowSpeed) {
				State::slowMotionFactor = 100.0f;
			}
			if (State::slowerSpeed) {
				State::slowMotionFactor = 500.0f;
			}

			gravityEffect = 0;
			gravityIncrease = 0;
			camera.transform.MoveTo(0.0f, 0.0f, -1.0f);
			camera.transform.SetRotationYZ(0.0f);

			// NORMAL VIEW MODE
		} else {

			if (State::normalSpeed) {
				State::slowMotionFactor = 1.0f;
			}
			if (State::slowSpeed) {
				State::slowMotionFactor = 50.0f;
			}
			if (State::slowerSpeed) {
				State::slowMotionFactor = 100.0f;
			}

			gravityEffect = 0.000005f / State::slowMotionFactor;
			gravityIncrease = 0.000005f / State::slowMotionFactor;
			camera.transform.MoveTo(0.0f, 0.0f, -3.0f);
			camera.transform.SetRotationYZ(10.0f);
			Renderer::Draw(platform, GL_TRIANGLES, &shader, light);
		}

		// No need to render slices or middle before explosion, since that's the same as source
		Renderer::Draw(teapotSource, GL_TRIANGLES, &shader, light);
		if (renderLeft) {
			for (int iii = 0; iii < teapot25Left.size(); iii++) {
				Renderer::Draw(teapot25Left[iii], GL_TRIANGLES, &shader, light);
			}
		}

		if (renderRight) {
			for (int iii = 0; iii < teapot25Right.size(); iii++) {
				Renderer::Draw(teapot25Right[iii], GL_TRIANGLES, &shader, light);
			}
		}

		// Get one last draw in before loading
		glfwSwapBuffers(glContext->GetGLWindow());
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (State::closeUp) {
			SubdivideTeapot(teapotSource, State::groupsOfParticles, tempSlices, teapotSlices);
		}

		timer.Update();
		State::state = State::EXPLODING;

	} if (State::state == State::EXPLODING) {

		if (!State::closeUp) {
			Renderer::Draw(platform, GL_TRIANGLES, &shader, light);
		}

		if (State::closeUp) {
			ExplodeTeapot(teapotSlices, dt);
		}

		if (State::groupsOfParticles >= 1) {
			ExplodeTeapot(teapot25Middle, dt);
		}

		if (State::groupsOfParticles >= 2) {
			ExplodeTeapot(teapot25Left, dt);
		}

		if (State::groupsOfParticles > 3) {
			ExplodeTeapot(teapot25Right, dt);
		}
		gravityEffect += gravityIncrease;

	} if (State::state == State::RESETTING) {

		// Reset middle teapot, but turn all teapots off
		TurnMiddleTeapotOn();
		TurnTeapotsOff();

		camera.transform.MoveTo(0.0f, 0.0f, -1.5f);
		camera.transform.SetRotationYZ(0.0f);

		for (int iii = 0; iii < teapotSlices.size(); iii++) {

			if (teapotSlices[iii] != teapotSource && teapotSlices[iii]) {
				delete teapotSlices[iii];
				teapotSlices[iii] = nullptr;
			}
		}
		
		tempSlices.clear();
		teapotSlices.clear();
		State::numberOfTeapots = 1;
		State::groupsOfParticles = 25;
		State::radial = true;
		State::closeUp = false;
		State::normalSpeed = true;
		State::slowSpeed = false;
		State::slowerSpeed = false;
		State::state = State::WAITING;

	} if (State::state == State::WAITING) {
		teapotSource->transform.RotateXZ(0.1f);
		Renderer::Draw(teapotSource, GL_TRIANGLES, &shader, light);
		Renderer::Draw(platform, GL_TRIANGLES, &shader, light);

		if (renderLeft) {
			for (int iii = 0; iii < teapot25Left.size(); iii++) {
				teapot25Left[iii]->transform.RotateXZ(-0.1f);
				Renderer::Draw(teapot25Left[iii], GL_TRIANGLES, &shader, light);
			}
		}

		if (renderRight) {
			for (int iii = 0; iii < teapot25Right.size(); iii++) {
				teapot25Right[iii]->transform.RotateXZ(-0.1f);
				Renderer::Draw(teapot25Right[iii], GL_TRIANGLES, &shader, light);
			}
		}
	}
}

// Entry point for program
void TeapotDemo::InitDemo() {

	glContext = GLContext::GetContext();
	shader.CreateProgram("..\\shaders\\simple_vertex_shader3.glsl",
		"..\\shaders\\simple_fragment_shader3.glsl");

	float leftX = -15.0f;
	float rightX = 15.0f;
	float backZ = -2.5f;
	float frontZ = 2.5f;
	float topY = 0.1f;
	float bottomY = -2.5f;
	float r = 0.44f;
	float g = 0.36f;
	float b = 0.26f;

	platform = new Mesh(std::vector<Vertex>{

		// FRONT BOTTOM TRIANGLE
		Vertex(leftX, topY, frontZ, r, g, b, 1.0f, 0.0f, 1.0f), // 0 FRONT Top Left
			Vertex(leftX, bottomY, frontZ, r, g, b, 1.0f, 0.0f, 0.0f), // 1 FRONT Bottom Left
			Vertex(rightX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 2 FRONT Bottom Right

																		// FRONT TOP TRIANGLE
			Vertex(rightX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 3 FRONT Bottom Right
			Vertex(rightX, topY, frontZ, r, g, b, 1.0f, 1.0f, 1.0f), // 4 FRONT Top Right
			Vertex(leftX, topY, frontZ, r, g, b, 1.0f, 0.0f, 1.0f), // 5 FRONT Top Left

																	// BACK BOTTOM TRIANGLE
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 6 BACK Top Left
			Vertex(leftX, bottomY, backZ, r, g, b, 1.0f, 0.0f, 0.0f), // 7 BACK Bottom Left
			Vertex(rightX, bottomY, backZ, r, g, b, 1.0f, 1.0f, 0.0f), // 8 BACK Bottom Right

																	   // BACK TOP TRIANGLE
			Vertex(rightX, bottomY, backZ, r, g, b, 1.0f, 1.0f, 0.0f), // 9 BACK Bottom Right
			Vertex(rightX, topY, backZ, r, g, b, 1.0f, 1.0f, 1.0f), // 10 BACK Top Right
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 11 BACK Top Left

																   // LEFT BOTTOM TRIANGLE
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 12 LEFT Top Left
			Vertex(leftX, bottomY, backZ, r, g, b, 1.0f, 0.0f, 0.0f), // 13 LEFT Bottom Left
			Vertex(leftX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 14 LEFT Bottom Right

																	   // LEFT TOP TRIANGLE
			Vertex(leftX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 15 LEFT Bottom Right
			Vertex(leftX, topY, frontZ, r, g, b, 1.0f, 1.0f, 1.0f), // 16 LEFT Top Right
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 17 LEFT Top Left

																   // RIGHT BOTTOM TRIANGLE
			Vertex(rightX, topY, frontZ, r, g, b, 1.0f, 0.0f, 1.0f), // 18 RIGHT Top Left
			Vertex(rightX, bottomY, frontZ, r, g, b, 1.0f, 0.0f, 0.0f), // 19 RIGHT Bottom Left
			Vertex(rightX, bottomY, backZ, r, g, b, 1.0f, 1.0f, 0.0f), // 20 RIGHT Bottom Right

																	   // RIGHT TOP TRIANLE
			Vertex(rightX, bottomY, backZ, r, g, b, 1.0f, 1.0f, 0.0f), // 21 RIGHT Bottom Right
			Vertex(rightX, topY, backZ, r, g, b, 1.0f, 1.0f, 1.0f), // 22 RIGHT Top Right
			Vertex(rightX, topY, frontZ, r, g, b, 1.0f, 0.0f, 1.0f), // 23 RIGHT Top Left

																	 // TOP BOTTOM TRIANGLE
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 24 TOP Top Left
			Vertex(leftX, topY, frontZ, r, g, b, 1.0f, 0.0f, 0.0f), // 25 TOP Bottom Left
			Vertex(rightX, topY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 26 TOP Bottom Right

																	 // TOP TOP TRIANGLE
			Vertex(rightX, topY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 27 TOP Bottom Right
			Vertex(rightX, topY, backZ, r, g, b, 1.0f, 1.0f, 1.0f), // 28 TOP Top Right
			Vertex(leftX, topY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 29 TOP Top Left

																   // BOTTOM BOTTOM TRIANGLE
			Vertex(leftX, bottomY, backZ, r, g, b, 1.0f, 0.0f, 1.0f), // 30 BOTTOM Top Left
			Vertex(leftX, bottomY, frontZ, r, g, b, 1.0f, 0.0f, 0.0f), // 31 BOTTOM Bottom Left
			Vertex(rightX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 32 BOTTOM Bottom Right

																		// BOTTOM TOP TRIANGLE
			Vertex(rightX, bottomY, frontZ, r, g, b, 1.0f, 1.0f, 0.0f), // 33 BOTTOM Bottom Right
			Vertex(rightX, bottomY, backZ, r, g, b, 1.0f, 1.0f, 1.0f), // 34 BOTTOM Top Right
			Vertex(-leftX, bottomY, backZ, r, g, b, 1.0f, 0.0f, 1.0f) // 35 BOTTOM Top Left

	}, GL_STATIC_DRAW);

	platform->transform.Translate(0.0f, -0.3f, 0.0f);
	camera.SetAsCurrentCamera();
	camera.transform.Translate(0.0f, 0.0f, -1.5f);

	light = new Light(1.0f, 1.0f, 1.0f);
	light->color.SetColor(1.0f, 1.0f, 1.0f);
	light->SetAmbientStrength(0.00f);
	light->transform.Translate(1.5f, 5.0f, 0.5f);

	teapotSource = Mesh::CreateMeshFromFile("..\\models\\teapot-scaled.obj", GL_STATIC_DRAW);
	SubdivideTeapot(teapotSource, 25, tempSlices, teapot25Middle);
	SubdivideTeapot(teapotSource, 25, tempSlices, teapot25Left);
	SubdivideTeapot(teapotSource, 25, tempSlices, teapot25Right);

	// Turn wire-frame on and off. Comment out this line for noral view
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	groundLevel = teapotSource->GetBoundingBox().bottom;

	// Use original teapot origin as reference for center
	originX = teapotSource->GetCenter().x;
	originY = teapotSource->GetCenter().y;
	originZ = teapotSource->GetCenter().z;
	origin = glm::vec3(originX, originY, originZ);

	timer.Update();
}

void TeapotDemo::Clean() {
	delete platform;
	platform = nullptr;
	delete light;
	light = nullptr;

	for (int iii = 0; iii < teapotSlices.size(); iii++) {

		if (teapotSlices[iii] != teapotSource && teapotSlices[iii]) {
			delete teapotSlices[iii];
			teapotSlices[iii] = nullptr;
		}
	}

	for (int iii = 0; iii < teapot25Middle.size(); iii++) {

		if (teapot25Middle[iii] != teapotSource && teapot25Middle[iii]) {
			delete teapot25Middle[iii];
			teapot25Middle[iii] = nullptr;
		}
	}

	for (int iii = 0; iii < teapot25Left.size(); iii++) {

		if (teapot25Left[iii] != teapotSource && teapot25Left[iii]) {
			delete teapot25Left[iii];
			teapot25Left[iii] = nullptr;
		}
	}

	for (int iii = 0; iii < teapot25Right.size(); iii++) {

		if (teapot25Right[iii] != teapotSource && teapot25Right[iii]) {
			delete teapot25Right[iii];
			teapot25Right[iii] = nullptr;
		}
	}

	teapotSlices.clear();
	tempSlices.clear();
	teapot25Middle.clear();
	teapot25Left.clear();
	teapot25Right.clear();
	delete teapotSource;
	teapotSource = nullptr;
}