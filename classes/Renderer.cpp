#include "pch.h"

// Total number of draw calls per loop
int Renderer::drawCount = 0;

// Adds mesh to buffer, performs draw call based on mesh properties, removes mesh from buffer
void Renderer::Draw(Mesh* mesh, int modeInput, Shader* shader, Light* light) {
	
	GLuint mode = modeInput;
	int indices = mesh->numberOfIndices;
	int vertices = mesh->numberOfVertices;

	Camera* camera = Camera::GetCurrentCamera();

	if (camera && camera->transform.HasChanged()) {
		camera->Update();
	}

	if (shader) {
		shader->Use();

		if (light) {
			// Set the light color for the shader
			Color4F color = light->color.GetColor();
			Position position = light->transform.position();
			shader->SetUniformVec4Float("lightColor", color.r, color.g, color.b, color.a);
			shader->SetUniformVec3Float("lightPosition", position.x, position.y, position.z);
			shader->SetUniformFloat("ambientStrength", light->GetAmbientStrength());
			GLint lightModelLocation = glGetUniformLocation(shader->Get_ID(), "lightModel");
			glm::mat4 lightModel = light->transform.GetTransformMatrix();
			glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));
		}

		else {
			shader->SetUniformVec4Float("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
			shader->SetUniformVec3Float("lightPosition", 0.0f, 10.0f, 0.0f);
			shader->SetUniformFloat("ambientStrength", 1.0f);
			GLint lightModelLocation = glGetUniformLocation(shader->Get_ID(), "lightModel");
			glm::mat4 lightModel;
			glUniformMatrix4fv(lightModelLocation, 1, GL_FALSE, glm::value_ptr(lightModel));
		}
	}

	mesh->BindToGLRenderer(shader);

	if (indices > 0) {
		glDrawElements(mode, indices, GL_UNSIGNED_INT, 0);
	}

	if (indices == 0) {
		glDrawArrays(mode, 0, vertices);
	}

	mesh->UnbindFromGLRenderer();

	drawCount++;
}

// Returns total number of draw calls before reset
int Renderer::GetDrawCount() {
	return drawCount;
}

// Resets counted number of draw calls
void Renderer::ResetDrawCount() {
	drawCount = 0;
}