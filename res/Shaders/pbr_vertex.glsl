#version 420
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUv;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec3 WorldPos;
out vec2 Uv;
out mat3 TBN;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

vec3 toModelSpace(vec3 x) {
	return normalize(vec3(model * vec4(x, 0.0)));
}

void main() {
	WorldPos = vec3(model * vec4(aPos, 1.0));
	Uv = aUv;
	TBN = mat3(
		toModelSpace(aTangent),
		toModelSpace(aBitangent),
		toModelSpace(aNormal)
		);

	gl_Position = projection * view * vec4(WorldPos, 1.0);
}