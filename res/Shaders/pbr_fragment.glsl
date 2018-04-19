#version 420

out vec4 FragColor;
in vec3 worldPos;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;

layout(binding = 0) uniform sampler2D albedoMap;
layout(binding = 1) uniform sampler2D normalMap;
layout(binding = 2) uniform sampler2D metallicSmoothnessMap;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 camPos;

const float PI = 3.14159265359;

int main() {

	FragColor = vec4(normal, 1);
}



