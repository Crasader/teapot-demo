#version 330 core

in vec3 positionData;
in vec4 colorData;
in vec2 textureCoordinates;
in vec3 normalData;

out vec4 color;

uniform sampler2D textureData1, textureData2, textureData3, textureData4;
uniform sampler2D textureData5, textureData6, textureData7, textureData8;
uniform sampler2D textureData9, textureData10, textureData11, textureData12;
uniform sampler2D textureData13, textureData14, textureData15, textureData16;

uniform vec4 lightColor;
uniform mat4 lightModel;
uniform vec3 lightPosition;
uniform float ambientStrength;

void main() {
  vec3 lightDirection = normalize(lightPosition - positionData);
  float angle = max(dot(normalData, lightDirection), 0.0f);
  vec3 diffuse = angle * vec3(lightColor);
  vec3 result = (ambientStrength + diffuse) * colorData;
  color = vec4(result, 1.0f);
}
