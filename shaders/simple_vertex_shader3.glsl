#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureInput;
layout (location = 3) in vec3 normal;

out vec3 positionData;
out vec4 colorData;
out vec2 textureCoordinates;
out vec3 normalData;

uniform mat4 transform;
uniform mat4 finalTransform;

void main()  {
    gl_Position = finalTransform * vec4(position, 1.0f);
    positionData = vec3(transform * vec4(position, 1.0f));
    normalData = vec3(finalTransform * vec4(normal, 1.0f));
    colorData = vec4(color, 1.0f);
    textureCoordinates = textureInput;
}
