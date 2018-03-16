#include "Transform.h"

Transform::Transform():
	position(0, 0, 0),
	scale(1, 1, 1)
{
}

glm::mat4 Transform::ModelMatrix() const
{
	glm::mat4 result;
	result = glm::translate(result, position);
	result *= glm::mat4_cast(rotation);
	result = glm::scale(result, scale);
	return result;
}

void Transform::SetPosition(const glm::vec3 &position)
{
	this->position = position;
}

void Transform::Move(const glm::vec3 &offset)
{
	this->position += offset;
}

void Transform::SetRotation(const float &degrees, const glm::vec3 &axis)
{
	glm::mat4 rotationMatrix;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(degrees), axis);
	rotation = glm::quat_cast(rotationMatrix);
}

void Transform::Rotate(const float& degrees, const glm::vec3& axis)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4_cast(rotation), glm::radians(degrees), axis);
	rotation = glm::quat_cast(rotationMatrix);
}

void Transform::SetScale(const glm::vec3& scale)
{
	this->scale = scale;
}

void Transform::Scale(const glm::vec3& scale)
{
	this->scale = glm::vec3(this->scale.x * scale.x, this->scale.y * scale.y, this->scale.z * scale.z);
}


