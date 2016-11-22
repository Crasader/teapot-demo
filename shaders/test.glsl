#version 330 core

in vec4 colorData;
in vec2 textureCoordinates;
out vec4 color;
uniform sampler2D textureData1, textureData2, textureData3, textureData4;
uniform sampler2D textureData5, textureData6, textureData7, textureData8;
uniform sampler2D textureData9, textureData10, textureData11, textureData12;
uniform sampler2D textureData13, textureData14, textureData15, textureData16;

uniform vec4 lightColor;
uniform vec3 lightPosition;

void main() {
    color = colorData;
  //  color = mix(texture(textureData1, textureCoordinates), texture(textureData2, textureCoordinates), 0.5f);
}
