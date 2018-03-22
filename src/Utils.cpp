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

	float SmoothStep(float a, float b, float smoothness, float deltaTime)
	{
		//std::cout << "a: " << a << "    b: " << b << "    deltaTime: " << deltaTime << std::endl;
		//std::cout << "smoothstep: " << glm::smoothstep(0.f, 1.f, 1.f - glm::pow(smoothness, deltaTime)) << std::endl;
		//std::cout << "mix: " << glm::mix(a, b, glm::smoothstep(0.f, 1.f, 1.f - glm::pow(smoothness, deltaTime))) << std::endl;
		return glm::mix(a, b, 1.f - glm::pow(smoothness, deltaTime));
	}

	glm::vec3 SmoothStep(glm::vec3 a, glm::vec3 b, float smoothness, float deltaTime)
	{
		return glm::vec3(
			SmoothStep(a.x, b.x, smoothness, deltaTime),
			SmoothStep(a.y, b.y, smoothness, deltaTime),
			SmoothStep(a.z, b.z, smoothness, deltaTime)
			);
	}

	float NormalizeAngle(float base, float x)
	{
		while(glm::abs(x-base) > 180)
		{
			if (x < base) x += 360;
			else x -= 360;
		}
		return x;
	}
}
