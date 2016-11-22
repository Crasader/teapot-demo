#pragma once
#include "pch.h"

class Transform;

class Camera {
public:
	Camera();
	~Camera();

	// Returns the current rendering camera
	static Camera* GetCurrentCamera();

	// Sets the camera as the current rendering camera
	void SetAsCurrentCamera();

	// Updates camera's transformation matrix
	void Update();

	// Transform matrix for camera
	Transform transform;

private:

	static Camera* currentCamera;

};

