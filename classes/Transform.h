#pragma once
#include "pch.h"

class Mesh;
class Shader;
class Camera;

// Handles position data for object
class Transform {
public:

	// Allow mesh and camera to perform transform methods
	friend class Mesh;
	friend class Camera;

	// Handles position data for object
	Transform(float inputX = 0.0f, float inputY = 0.0f, float inputZ = 0.0f);
	~Transform();

	// Returns transformation matrix (translate * rotate * scale)
	glm::mat4 GetTransformMatrix();

	// Returns translation matrix (view / view space)
	glm::mat4 GetTranslationMatrix();

	// Returns rotation matrix (model / world space)
	glm::mat4 GetRotationMatrix();

	// Returns scale matrix
	glm::mat4 GetScaleMatrix();

	// Returns whether the transform has changed and needs to be recalculated
	bool HasChanged();

	// Get position of object
	Position position();

	// Move vertices by given values
	void Translate(float inputX, float inputY, float inputZ);

	// Set offset for mesh
	void Offset(float inputX, float inputY, float inputZ);

	// Move origin to coordinates
	void MoveTo(float inputX, float inputY, float inputZ);

	// Increase X and Y rotation coordinates about Z axis
	void RotateXY(float rotation);

	// Increase X and Z rotation coordinates about Y axis
	void RotateXZ(float rotation);

	// Increase Y and Z rotation coordinates about X axis
	void RotateYZ(float rotation);

	// Set X and Y rotation coordinates about Z axis
	void SetRotationXY(float rotation);

	// Set X and Z rotation coordinates about Y axis
	void SetRotationXZ(float rotation);

	// Set Y and Z rotation coordinates about X axis
	void SetRotationYZ(float rotation);

	// Set scale of vertices by given values
	void SetScale(float inputX, float inputY, float inputZ);

	// Grow (or shrink) vertices by given values
	void ScaleContinuous(float inputX, float inputY, float inputZ);

	// Updates transformation matrix
	void UpdateMatrix();

private:
	Position _position;

	// Whether the transform has changed and needs to be recalculated
	bool hasChanged = false;

	// Performs transformations with respect to camera
	void Update(Shader* shader);

	// Matrix that stores scale values for mesh vertices
	float scale[3]{ 1 };

	// Matrix that stores rotation values for mesh vertices.
	float rotation[3]{ 0 };

	// Matrix that stores translation values for mesh vertices
	float translation[3]{ 0 };
	
	// Reset matrix back to identity matrix state
	void ResetMatrix();

	// Whether to reset translation after Update
	bool resetTranslation = false;

	// Whether to reset rotation after Update
	bool resetRotation = false;

	// Whether to reset scale after Update
	bool resetScale = false;

	// The transformed matrix
	glm::mat4 transformMatrix;

	// The scale matrix
	glm::mat4 scaleMatrix;

	// The rotation matrix
	glm::mat4 rotationMatrix;

	// The translation matrix
	glm::mat4 translationMatrix;

};

