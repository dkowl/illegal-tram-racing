#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

public:
	Transform();

	glm::mat4 ModelMatrix() const;

	void SetPosition(const glm::vec3 &position);
	void Move(const glm::vec3 &offset);

	void SetRotation(const float &degrees, const glm::vec3 &axis);
	void Rotate(const float &degrees, const glm::vec3 &axis);

	void SetScale(const glm::vec3 &scale);
	void Scale(const glm::vec3 &scale);

};