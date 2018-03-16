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
}
