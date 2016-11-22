#include "pch.h"

// Handles position data for object
Transform::Transform(float inputX, float inputY, float inputZ) {
	_position.x = inputX;
	_position.y = inputY;
	_position.z = inputZ;

	Translate(inputX, inputY, inputZ);
}

Transform::~Transform() {}

// Returns transformation matrix
glm::mat4 Transform::GetTransformMatrix() {
	return transformMatrix; //translationMatrix *rotationMatrix * scaleMatrix;
}

// Returns translation matrix (view / view space)
glm::mat4 Transform::GetTranslationMatrix() {
	return translationMatrix;
}

// Returns rotation matrix (model / world space)
glm::mat4 Transform::GetRotationMatrix() {
	return rotationMatrix;
}

// Returns scale matrix
glm::mat4 Transform::GetScaleMatrix() {
	return scaleMatrix;
}

void Transform::Update(Shader* shader) {

	// Alter mesh's transformation by camera
	Camera* camera = Camera::GetCurrentCamera();
	glm::mat4 cameraMatrix;
	glm::mat4 finalTransformMatrix;

	if (camera) {
		cameraMatrix = Camera::GetCurrentCamera()->transform.GetTransformMatrix();
	}

	// Order of transformations should be Scale, Rotate, Translate. 
	// However, order goes in verse of declare operations (Translate, Rotate, Scale)
	// Finally, transform result by camera transform
	finalTransformMatrix = cameraMatrix * translationMatrix * rotationMatrix * scaleMatrix;

	// Insert into GLSL shader program
	GLint finalTransformLocation = glGetUniformLocation(shader->Get_ID(), "finalTransform");
	glUniformMatrix4fv(finalTransformLocation, 1, GL_FALSE, glm::value_ptr(finalTransformMatrix));
	GLint transformLocation = glGetUniformLocation(shader->Get_ID(), "transform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));

	// Reset changed status
	hasChanged = false;
}

// Updates transformation matrix
void Transform::UpdateMatrix() {
	transformMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

// Returns whether the transform has changed and needs to be recalculated
bool Transform::HasChanged() {
	return hasChanged;
}

// Get position of object
Position Transform::position() {
	return _position;
}

// Move all vertices by given value
void Transform::Translate(float inputX, float inputY, float inputZ) {
	_position.x += inputX;
	_position.y += inputY;
	_position.z += inputZ;

	// Translate
	translationMatrix = glm::translate(translationMatrix, glm::vec3(inputX, inputY, inputZ));
	translation[0] += inputX;
	translation[1] += inputY;
	translation[2] += inputZ;

	hasChanged = true;
}

// Set offset for mesh
void Transform::Offset(float inputX, float inputY, float inputZ) {

	if (translation[0] != inputX || translation[1] != inputY || translation[2] != inputZ) {
		// Prevent translation matrix from continuosly updating
		glm::mat4 reset;
		translationMatrix = reset;
		translationMatrix = glm::translate(translationMatrix, glm::vec3(inputX, inputY, inputZ));
		hasChanged = true;
	}
}

// Move origin to coordinates
void Transform::MoveTo(float inputX, float inputY, float inputZ) {

	// NOTE: THIS IS WRONG, NEEDS TO FIND DISTANCE FROM A GIVEN / DESIGNATED ORIGIN, THEN MOVE ALL VERTICES BY THAT DISTANCE
	// WITH MATRIX
	float distanceX = inputX - _position.x;
	float distanceY = inputY - _position.y;
	float distanceZ = inputZ - _position.z;

	Translate(distanceX, distanceY, distanceZ);

	_position.x = inputX;
	_position.y = inputY;
	_position.z = inputZ;

	hasChanged = true;
}

// Rotate X and Y coordinates about Z axis
void Transform::RotateXY(float rotationInput) {

	// Add rotation amount, but keep below 360 degrees.
	rotation[2] += rotationInput;
	rotation[2] = std::fmod(rotation[0], 360.0f);

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
		glm::vec3(0.0f, 0.0f, 1.0f));

	hasChanged = true;
}

// Rotate X and Z coordinates about Y axis
void Transform::RotateXZ(float rotationInput) {

	// Add rotation amount, but keep below 360 degrees.
	rotation[1] += rotationInput;
	rotation[1] = std::fmod(rotation[0], 360.0f);

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
		glm::vec3(0.0f, 1.0f, 0.0f));

	hasChanged = true;
}

// Rotate Y and Z coordinates about X axis
void Transform::RotateYZ(float rotationInput) {

	// Add rotation amount, but keep below 360 degrees.
	rotation[0] += rotationInput;
	rotation[0] = std::fmod(rotation[0], 360.0f);

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
		glm::vec3(1.0f, 0.0f, 0.0f));

	hasChanged = true;
}

// Set X and Y rotation coordinates about Z axis
void Transform::SetRotationXY(float rotationInput) {

	if (rotation[2] != rotationInput) {
		// Prevent rotation matrix from continuously updating
		glm::mat4 reset;
		rotationMatrix = reset;
		rotation[2] = rotationInput;
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
			glm::vec3(0.0f, 0.0f, 1.0f));
		hasChanged = true;
	}
}

// Set X and Z rotation coordinates about Y axis
void Transform::SetRotationXZ(float rotationInput) {

	if (rotation[1] != rotationInput) {
		// Prevent rotation matrix from continuously updating
		glm::mat4 reset;
		rotationMatrix = reset;
		rotation[1] = rotationInput;
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
			glm::vec3(0.0f, 1.0f, 0.0f));
		hasChanged = true;
	}
}

// Set Y and Z rotation coordinates about X axis
void Transform::SetRotationYZ(float rotationInput) {

	if (rotation[0] != rotationInput) {
		// Prevent rotation matrix from continuously updating
		glm::mat4 reset;
		rotationMatrix = reset;
		rotation[0] = rotationInput;
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotationInput),
			glm::vec3(1.0f, 0.0f, 0.0f));
		hasChanged = true;
	}
}

// Set scale of vertices by given values
void Transform::SetScale(float inputX, float inputY, float inputZ) {

	if (scale[0] != inputX || scale[1] != inputY || scale[2] != inputZ) {
		// Prevent scale matrix from continuously updating
		resetScale = true;
		ResetMatrix();

		scale[0] *= inputX;
		scale[1] *= inputY;
		scale[2] *= inputZ;

		scaleMatrix = glm::scale(scaleMatrix, glm::vec3(inputX, inputY, inputZ));
	}
}

// Grow (or shrink) vertices by given values
void Transform::ScaleContinuous(float inputX, float inputY, float inputZ) {

	scale[0] *= inputX;
	scale[1] *= inputY;
	scale[2] *= inputZ;

	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(inputX, inputY, inputZ));
}

// Reset matrix back to identity matrix state
void Transform::ResetMatrix() {

	// Reset matrices
	glm::mat4 reset;

	if (resetTranslation) {
		translationMatrix = reset;
		translation[0] = 0.0f;
		translation[1] = 0.0f;
		translation[2] = 0.0f;
	}

	if (resetRotation) {
		rotationMatrix = reset;
		rotation[0] = 0.0f;
		rotation[1] = 0.0f;
		rotation[2] = 0.0f;
	}

	if (resetScale) {
		scaleMatrix = reset;
		scale[0] = 1.0f;
		scale[1] = 1.0f;
		scale[2] = 1.0f;
	}

	resetTranslation = false;
	resetRotation = false;
	resetScale = false;

}