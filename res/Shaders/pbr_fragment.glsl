#version 420

out vec4 FragColor;
in vec3 WorldPos;
in vec2 Uv;
in mat3 TBN;

layout(binding = 0) uniform sampler2D AlbedoMap;
layout(binding = 1) uniform sampler2D NormalMap;
layout(binding = 2) uniform sampler2D MetallicSmoothnessMap;

uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform float AttenuationFactor;

uniform vec3 CamPos;

const float PI = 3.14159265359;

float PositiveDot(vec3 a, vec3 b) {
	return max(dot(a, b), 0.0);
}

float ThrowbridgeReitzGGX(vec3 normal, vec3 halfway, float roughness) {
	float a = roughness * roughness;
	float a2 = a*a;

	float nDotH = PositiveDot(normal, halfway);
	float nDotH2 = nDotH * nDotH;

	float denom = (nDotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return a2 / denom;
}

float GeometrySchlickGGX(float nDotV, float roughness) {

	float k = roughness + 1.0;
	k = k * k / 8;

	float denom = nDotV * (1.0 - k) + k;

	return nDotV / denom;
}

float GeometrySmith(vec3 normal, vec3 view, vec3 light, float roughness) {
	float nDotV = PositiveDot(normal, view);
	float nDotL = PositiveDot(normal, light);
	float ggx1 = GeometrySchlickGGX(nDotV, roughness);
	float ggx2 = GeometrySchlickGGX(nDotL, roughness);

	return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(1 - cosTheta, 5.0);
}

void main() {
	vec3 albedo = pow(texture(AlbedoMap, Uv).rgb, vec3(2.2));
	float metallic = texture(MetallicSmoothnessMap, Uv).r;
	float roughness = texture(MetallicSmoothnessMap, Uv).a;

	vec3 normal = texture(NormalMap, Uv).rgb;
	normal = normal * 2.0 - 1.0;
	normal = TBN * normal;

	vec3 f0 = vec3(0.04);
	f0 = mix(f0, albedo, metallic);

	vec3 totalRadiance = vec3(0.0);

	vec3 viewVector = normalize(CamPos - WorldPos);
	vec3 lightVector = normalize(LightPosition - WorldPos);
	vec3 halfwayVector = normalize(viewVector + lightVector);

	float distance = length(LightPosition - WorldPos);
	float attenuation = 1.0 / (1.0 + AttenuationFactor * distance * distance);
	vec3 radiance = LightColor * attenuation;

	float ndf = ThrowbridgeReitzGGX(normal, halfwayVector, roughness);
	float geometry = GeometrySmith(normal, viewVector, lightVector, roughness);
	vec3 fresnel = FresnelSchlick(PositiveDot(halfwayVector, viewVector), f0);

	vec3 nominator = ndf * geometry * fresnel;
	float denominator = 4 * PositiveDot(normal, viewVector) * PositiveDot(normal, lightVector) + 0.001;
	vec3 specular = nominator / denominator;

	vec3 kSpecular = fresnel;
	vec3 kDiffuse = vec3(1.0) - kSpecular;
	kDiffuse *= 1.0 - metallic;

	totalRadiance += (kDiffuse * albedo / PI + specular) * radiance * PositiveDot(normal, lightVector);

	vec3 ambient = vec3(0.03) * albedo;
	vec3 color = ambient + totalRadiance;

	//HDR
	color = color / (color + vec3(1.0));

	//gamma correction
	color = pow(color, vec3(1.0 / 2.2));

	FragColor = vec4(color, 1);
}



