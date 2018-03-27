#pragma once
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Utils
{
	void DisplayMat4(glm::mat4 &m);
	void DisplayVec3(glm::vec3 &v);
	void DisplayVec3(glm::vec3 &v, const std::string &name);

	float GetYRotation(glm::vec3 v);
	float GetYRotationAngleBetweenVectors(glm::vec3 a, glm::vec3 b);

	float SmoothStep(float a, float b, float smoothness, float deltaTime);
	glm::vec3 SmoothStep(glm::vec3 a, glm::vec3 b, float smoothness, float deltaTime);

	float NormalizeAngle(float x, float base);
}