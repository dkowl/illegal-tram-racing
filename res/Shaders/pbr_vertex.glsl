#version 420
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUv;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec3 worldPos;
out vec2 uv;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	WorldPos = vec3(model * vec4(aPos, 1.0));
	Uv = aUv;
	Normal = mat3(model) * aNormal;

	gl_Position = projection * view * vec4(worldPos, 1.0);
}