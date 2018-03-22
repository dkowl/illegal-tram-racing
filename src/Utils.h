#pragma once
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Utils
{
	void DisplayMat4(glm::mat4 &m);
	void DisplayVec3(glm::vec3 &v);

	float GetYRotation(glm::vec3 v);
}