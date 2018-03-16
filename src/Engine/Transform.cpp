#include "Transform.h"

Transform::Transform():
	localPosition(0, 0, 0),
	localScale(1, 1, 1),
	parent(nullptr),
	siblingId(0)
{
}

glm::mat4 Transform::ModelMatrix() const
{
	glm::mat4 result;
	result = glm::translate(result, worldPosition);
	result *= glm::mat4_cast(worldRotation);
	result = glm::scale(result, worldScale);
	return result;
}

glm::vec3 Transform::Position() const
{
	return worldPosition;
}

glm::quat Transform::Rotation() const
{
	return worldRotation;
}

glm::vec3 Transform::Scale() const
{
	return worldScale;
}

void Transform::SetLocalPosition(const glm::vec3 &position)
{
	this->localPosition = position;
	Update();
}

void Transform::Move(const glm::vec3 &offset)
{
	this->localPosition += offset;
	Update();
}

void Transform::SetLocalRotation(const float &degrees, const glm::vec3 &axis)
{
	glm::mat4 rotationMatrix;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(degrees), axis);
	localRotation = glm::quat_cast(rotationMatrix);
	Update();
}

void Transform::Rotate(const float& degrees, const glm::vec3& axis)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4_cast(localRotation), glm::radians(degrees), axis);
	localRotation = glm::quat_cast(rotationMatrix);
	Update();
}

void Transform::SetLocalScale(const glm::vec3& scale)
{
	this->localScale = scale;
	Update();
}

void Transform::Scale(const glm::vec3& scale)
{
	this->localScale = glm::vec3(this->localScale.x * scale.x, this->localScale.y * scale.y, this->localScale.z * scale.z);
	Update();
}

void Transform::SetParent(Transform* parent)
{
	if(this->parent != nullptr)
	{
		this->parent->RemoveChild(siblingId);
	}
	this->parent = parent;
	siblingId = this->parent->AddChild(this);
}

int Transform::AddChild(Transform* child)
{
	children.push_back(child);
	return children.size() - 1;
}

void Transform::RemoveChild(int id)
{
	children.erase(children.begin() + id);
	for (int i = id; i < children.size(); i++)
	{
		children[i]->siblingId = i;
	}
}

void Transform::Update()
{
	if(parent != nullptr)
	{
		worldPosition = parent->worldPosition + localPosition;
		worldRotation = parent->worldRotation * localRotation;
		worldScale = parent->worldScale * localScale;		
	}
	else
	{
		worldPosition = localPosition;
		worldRotation = localRotation;
		worldScale = localScale;
	}

	for(auto&& child: children)
	{
		if (child) child->Update();
	}
}


