#version 330

out vec4 FragColor;

in vec2 uv;

uniform sampler2D mainTexture;

void main() {
	FragColor = texture(mainTexture, uv);
	//FragColor = vec4(uv.x, uv.y, 0, 1);
}