#pragma once
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
	glm::vec3 localPosition;
	glm::quat localRotation;
	glm::vec3 localScale;

	glm::vec3 worldPosition;
	glm::quat worldRotation;
	glm::vec3 worldScale;

	std::weak_ptr<Transform> parent;
	std::vector<std::weak_ptr<Transform>> children;

public:
	Transform();

	glm::mat4 ModelMatrix() const;

	glm::vec3 Position() const;
	glm::quat Rotation() const;
	glm::vec3 Scale() const;

	void SetLocalPosition(const glm::vec3 &position);
	void Move(const glm::vec3 &offset);

	void SetLocalRotation(const float &degrees, const glm::vec3 &axis);
	void Rotate(const float &degrees, const glm::vec3 &axis);

	void SetLocalScale(const glm::vec3 &scale);
	void Scale(const glm::vec3 &scale);



private:
	void Update();

};