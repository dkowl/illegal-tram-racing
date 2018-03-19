#include "Utils.h"

namespace Utils
{
	void DisplayMat4(glm::mat4 &m)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << m[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void DisplayVec3(glm::vec3& v)
	{
		std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	}

	float GetYRotation(glm::vec3 v)
	{
		v.y = 0;
		v = glm::normalize(v);
		float dot = glm::dot(v, glm::vec3(0, 0, -1));
		float angle = glm::acos(dot);
		if (v.x < 0) angle = 2*glm::pi<float>() - angle;
		return angle;
	}
}
