#include "pch.h"

Camera* Camera::currentCamera = nullptr;

Camera::Camera() {}
Camera::~Camera() {}

void Camera::Update() {
	std::shared_ptr<GLWindow> window = GLContext::GetContext()->GetWindow();
	glm::mat4 projection;
	projection = glm::perspective(45.0f, 
		(GLfloat)(window->GetWidth()) / (GLfloat)(window->GetHeight()), 
		0.1f, 100.0f);
	transform.UpdateMatrix();
	transform.transformMatrix = projection * transform.transformMatrix;
}

// Returns the current rendering camera
Camera* Camera::GetCurrentCamera() {
	return currentCamera;
}

// Sets the camera as the current rendering camera
void Camera::SetAsCurrentCamera() {
	currentCamera = this;
}
