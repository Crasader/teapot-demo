#pragma once
#include "pch.h"

void ExplodeTeapot(Mesh* teapot) {

}

void function() {
	std::cout << "Callback success" << std::endl;
}

// Subdivide the source mesh into n divisions. Fill target vector with subdivided parts
void SubdivideTeapot(Mesh*& source, int divisions, std::vector<Mesh*> copies, std::vector<Mesh*>& target) {

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

// Entry point for program
int main() {

	GLContext glContext(1920, 1080, "Collabera Teapot Demo");
	
	// Some shaders to play around with
	Shader shaderGreen;
	shaderGreen.CreateProgram("..\\shaders\\simple_vertex_shader.glsl",
		"..\\shaders\\simple_fragment_shader_green.glsl");

	Shader shaderRed;
	shaderRed.CreateProgram("..\\shaders\\simple_vertex_shader.glsl",
		"..\\shaders\\simple_fragment_shader_red.glsl");

	Shader shaderCustom;
	shaderCustom.CreateProgram("..\\shaders\\simple_vertex_shader.glsl",
		"..\\shaders\\simple_fragment_shader_custom_color.glsl");
	shaderCustom.SetUniformVec4Float("colorInput", 1.0f, 1.0f, 1.0f, 1.0f);

	Shader shaderColoredVertex;
	shaderColoredVertex.CreateProgram("..\\shaders\\simple_vertex_shader2.glsl",
		"..\\shaders\\simple_fragment_shader2.glsl");

	Shader shaderTexture;
	shaderTexture.CreateProgram("..\\shaders\\simple_vertex_shader3.glsl",
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

	Mesh platform = Mesh(std::vector<Vertex>{

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
	platform.MapTexture("..\\textures\\container.jpg");
	platform.transform.Translate(0.0f, -0.3f, 0.0f);

	// Scene assets
	InputHandler inputHandler;
	Camera camera;
	camera.SetAsCurrentCamera();
	camera.transform.Translate(0.0f, 0.0f, -1.5f);

	Light light(1.0f, 1.0f, 1.0f);
	light.color.SetColor(1.0f, 1.0f, 1.0f);
	light.SetAmbientStrength(0.00f);
	light.transform.Translate(1.5f, 5.0f, 0.5f);

	Mesh* teapotSource = Mesh::CreateMeshFromFile("..\\models\\teapot-scaled.obj", GL_STATIC_DRAW);
	std::vector<Mesh*> tempSlices;
	std::vector<Mesh*> teapotSlices;
	std::vector<Mesh*> teapot25;

	// Turn wire-frame on and off. Comment out this line for noral view
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float groundLevel = teapotSource->GetBoundingBox().bottom;

	// Use original teapot origin as reference for center
	float originX = teapotSource->GetCenter().x;
	float originY = teapotSource->GetCenter().y;
	float originZ = teapotSource->GetCenter().z;
	glm::vec3 origin(originX, originY, originZ);

	Timer timer;
	timer.Update();
	
	float gravityEffect = 0.0002f;
	float gravityIncrease = 0.00015f;

	int magnitude1 = rand() % 10;
	int magnitude2 = rand() % 10;
	int magnitude3 = rand() % 10;

	while (!glfwWindowShouldClose(glContext.GetGLWindow())) {
		float dt = (float)(timer.GetDeltaTime()) / (State::slowMotionFactor);

		Renderer::ResetDrawCount();
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (State::state == State::INITIALIZING) {

			if (State::closeUp) {
				gravityEffect = 0;
				gravityIncrease = 0;
				camera.transform.MoveTo(0.0f, 0.0f, -1.0f);
				camera.transform.SetRotationYZ(0.0f);
			} else {
				gravityEffect = 0.000005f / State::slowMotionFactor;
				gravityIncrease = 0.000005f / State::slowMotionFactor;
				camera.transform.MoveTo(0.0f, 0.0f, -3.0f);
				camera.transform.SetRotationYZ(10.0f);
				Renderer::Draw(&platform, GL_TRIANGLES, &shaderTexture, &light);
			}

			Renderer::Draw(teapotSource, GL_TRIANGLES, &shaderTexture, &light);

			// Get one last draw in before loading
			glfwSwapBuffers(glContext.GetGLWindow());
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			SubdivideTeapot(teapotSource, State::groupsOfParticles, tempSlices, teapotSlices);
			timer.Update();
			State::state = State::EXPLODING;

		} if (State::state == State::EXPLODING) {
			
			for (int iii = 0; iii < teapotSlices.size(); iii++) {
				float force = 0.01f * dt;

				float x = teapotSlices[iii]->GetCenter().x;
				float y = teapotSlices[iii]->GetCenter().y;
				float z = teapotSlices[iii]->GetCenter().z;
				glm::vec3 trajectory = glm::normalize(glm::vec3(x, y, z));
				trajectory *= force;
				int random = rand() % 250;
				magnitude1 = rand() % 250;
				magnitude2 = rand() % 250;
				float back = -1.0f;
				float front = 1.0f;
				float ground = -0.01f;
				float left = -0.5f;
				float right = 0.5f;

				if (!State::closeUp) {

					Renderer::Draw(&platform, GL_TRIANGLES, &shaderTexture, &light);
					trajectory.y -= gravityEffect;

					// Stop at "floor"
					if (teapotSlices[iii]->GetBoundingBox().bottom <= ground) {
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

					teapotSlices[iii]->transform.RotateXY(
						(2 * State::slowMotionFactor - 1) *
						force * xyDirection * magnitude1 /
						State::groupsOfParticles);
					teapotSlices[iii]->transform.RotateYZ(
						(2 * State::slowMotionFactor - 1) *
						force * yzDirection * magnitude2 / State::
						groupsOfParticles);
				}

				teapotSlices[iii]->transform.Translate(trajectory.x, trajectory.y, trajectory.z);
				Renderer::Draw(teapotSlices[iii], GL_TRIANGLES, &shaderTexture, &light);	
			}

			gravityEffect += gravityIncrease;

		} if (State::state == State::RESETTING) {

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
			State::state = State::WAITING;

		} if (State::state == State::WAITING) {
			teapotSource->transform.RotateXZ(0.1f);
			Renderer::Draw(teapotSource, GL_TRIANGLES, &shaderTexture, &light);
			Renderer::Draw(&platform, GL_TRIANGLES, &shaderTexture, &light);
			// CHANGE SLOW MO EFFECT, GROUPS OF PARTICLES, COLOR, RADIAL, HERE
		}
		glfwSwapBuffers(glContext.GetGLWindow());
	}

	delete teapotSource;
	teapotSource = nullptr;
	std::cin.get();
	glContext.Clean();
	glfwTerminate();

	return 1;
}


// SOME SHAPES TO PLAY WITH ANOTHER DAY 

/*
std::vector<GLuint> GLIndicesSquare{
0, 1, 2, // 0 Bottom Left Triangle
0, 3, 2  // 1 Top Right Triangle
};

std::vector<GLuint> GLIndicesTriangle{
0, 1, 2, // 0 Bottom Left Triangle
};

// Only useful for non-textured cube
std::vector<GLuint> GLIndicesCube{
0, 1, 2, 2, 3, 0, // 0 Front
4, 5, 6, 6, 7, 4, // 1 Back
8, 9, 10, 10, 11, 9, // 2 Left
12, 13, 14, 14, 15, 12, // 3 Right
16, 17, 18, 18, 19, 16, // 4 Top
20, 21, 22, 22, 23, 20  // 5 Bottom
};

Mesh cube = Mesh(std::vector<Vertex>{

// FRONT BOTTOM TRIANGLE
Vertex(-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 0 FRONT Top Left
Vertex(-0.25f, -0.25f, 0.25f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 1 FRONT Bottom Left
Vertex(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 2 FRONT Bottom Right

// FRONT TOP TRIANGLE
Vertex(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 3 FRONT Bottom Right
Vertex(0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f), // 4 FRONT Top Right
Vertex(-0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 5 FRONT Top Left

// BACK BOTTOM TRIANGLE
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 6 BACK Top Left
Vertex(-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 7 BACK Bottom Left
Vertex(0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 8 BACK Bottom Right

// BACK TOP TRIANGLE
Vertex(0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 9 BACK Bottom Right
Vertex(0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 10 BACK Top Right
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 11 BACK Top Left

// LEFT BOTTOM TRIANGLE
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 12 LEFT Top Left
Vertex(-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 13 LEFT Bottom Left
Vertex(-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 14 LEFT Bottom Right

// LEFT TOP TRIANGLE
Vertex(-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 15 LEFT Bottom Right
Vertex(-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 16 LEFT Top Right
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 17 LEFT Top Left

// RIGHT BOTTOM TRIANGLE
Vertex(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 18 RIGHT Top Left
Vertex(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 19 RIGHT Bottom Left
Vertex(0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 20 RIGHT Bottom Right

// RIGHT TOP TRIANLE
Vertex(0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 21 RIGHT Bottom Right
Vertex(0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 22 RIGHT Top Right
Vertex(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 23 RIGHT Top Left

// TOP BOTTOM TRIANGLE
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 24 TOP Top Left
Vertex(-0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 25 TOP Bottom Left
Vertex(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 26 TOP Bottom Right

// TOP TOP TRIANGLE
Vertex(0.25f, 0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 27 TOP Bottom Right
Vertex(0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 28 TOP Top Right
Vertex(-0.25f, 0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 29 TOP Top Left

// BOTTOM BOTTOM TRIANGLE
Vertex(-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f), // 30 BOTTOM Top Left
Vertex(-0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 31 BOTTOM Bottom Left
Vertex(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 32 BOTTOM Bottom Right

// BOTTOM TOP TRIANGLE
Vertex(0.25f, -0.25f, 0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 33 BOTTOM Bottom Right
Vertex(0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f), // 34 BOTTOM Top Right
Vertex(-0.25f, -0.25f, -0.25f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f) // 35 BOTTOM Top Left

}, GL_STREAM_DRAW);

cube.MapTexture("..\\textures\\wall.jpg");
cube.MapTexture("..\\textures\\container.jpg");

Mesh square = Mesh(std::vector<Vertex>{
Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 0 Top Left Front
Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 1 Bottom Left Front
Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 2 Bottom Right Front
Vertex(0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f) // 3 Top Right Front
}, GL_STATIC_DRAW, GLIndicesSquare);

square.MapTexture("..\\textures\\wall.jpg");
square.MapTexture("..\\textures\\container.jpg");

// Two triangles next to each other, same vertex array
Mesh twoTriangle(std::vector<Vertex>{

// LEFT TRIANGLE
Vertex(-0.25f, -0.25f, 0.0f, 1.0f), // 0 Bottom Left Front
Vertex(0.0f, -0.25f, 0.0f, 0.0f, 1.0f), // 1 Bottom Right Front
Vertex(0.0f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f), // 2 Top Right Front

// RIGHT TRIANGLE
Vertex(0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f), // 3 Bottom Left Front
Vertex(0.5f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f), // 4 Bottom Right Front
Vertex(0.5f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f) // 5 Top Right Front
}, GL_STATIC_DRAW);

// This holdes meshes for a cube. However, this results in multiple draw calls
std::vector<Mesh*> squares;
int count = 6;
for (int iii = 0; iii < count; iii++) {

squares.push_back(new Mesh(std::vector<Vertex>{
Vertex(-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), // 0 Top Left Front
Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f), // 1 Bottom Left Front
Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f), // 2 Bottom Right Front
Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f) // 3 Top Right Front
}, GL_STATIC_DRAW, GLIndicesSquare));
squares[iii]->MapTexture("..\\textures\\wall.jpg");
squares[iii]->MapTexture("..\\textures\\container.jpg");

}

// These make a cube
squares[0]->transform.Translate(0.0f, 0.0f, 0.5f); // FRONT
squares[1]->transform.Translate(0.0f, 0.0f, -0.5f); // BACK
squares[2]->transform.RotateYZ(90.0f);
squares[2]->transform.Translate(0.0f, 0.5f, 0.0f); // TOP
squares[3]->transform.RotateYZ(90.0f);
squares[3]->transform.Translate(0.0f, -0.5f, 0.0f); // BOTTOM
squares[4]->transform.RotateXZ(90.0f);
squares[4]->transform.Translate(0.5f, 0.0f, 0.0f); // RIGHT
squares[5]->transform.RotateXZ(90.0f);
squares[5]->transform.Translate(-0.5f, 0.0f, 0.0f); // LEFT

// Use this to change values of a shader program from here
float value = 0.0f;
float change = 0.005f;

std::vector<Mesh*> teapotTriangles = Mesh::CreateMeshArrayFromFile("..\\models\\teapot-scaled.obj", GL_STREAM_DRAW);

*/

/*
int particlesInGroup = teapotTriangles.size() / groupsOfParticles;
int totalTriangles = teapotTriangles.size();
*/

/* OLD, SLOWER WAY -- USING INDIVIDUAL TRIANGLES
for (int iii = 0; iii < totalTriangles; iii += particlesInGroup) {
int random = rand() % 20;
float amount = 0.005f;
float x = teapotTriangles[iii]->GetCenter().x;
float y = teapotTriangles[iii]->GetCenter().y;
float z = teapotTriangles[iii]->GetCenter().z;
glm::vec3  trajectory = glm::normalize(glm::vec3(x, y, z));
trajectory *= (amount);

int limit;
if (iii + particlesInGroup > totalTriangles) {
limit = iii + (totalTriangles % iii);
} else {
limit = iii + particlesInGroup;
}
for (int jjj = iii; jjj < limit; jjj++) {
teapotTriangles[jjj]->transform.RotateXZ(random);
teapotTriangles[jjj]->transform.RotateYZ(random);
teapotTriangles[jjj]->transform.Translate(trajectory.x, trajectory.y, trajectory.z);
//	Renderer::Draw(teapotTriangles[jjj], GL_TRIANGLES, &shaderTexture);
}
}
*/