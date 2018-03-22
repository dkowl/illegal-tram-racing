#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

class CameraPerspective : public Camera
{
public:
	enum class Mode
	{
		POSITION,
		PITCH_YAW,
		PITCH
	};

private:
	Mode mode;

	glm::vec3 target;
	glm::vec3 targetTarget;

	glm::vec3 position;

	float yaw;
	float targetYaw;
	float pitch;
	float targetPitch;
	float minPitch;
	float maxPitch;
	float distance;
	float minDistance;
	float maxDistance;

	float fov;
	float nearClipPlane;
	float farClipPlane;

	float targetSmoothness;
	float yawSmoothness;
	float pitchSmoothness;

public:
	CameraPerspective();

	void Update();

	glm::mat4 ViewMatrix() const override;
	glm::mat4 ProjectionMatrix() const override;

	glm::vec3 UpVector() const;
	glm::vec3 RightVector() const;
	glm::vec3 DirectionVector() const;

	void SetMode(Mode mode);

	void SetTarget(glm::vec3 &&target);

	void SetPosition(glm::vec3 &&position);

	void SetYaw(float yawDegrees);
	void SetPitch(float pitchDegrees);
	void SetMinPitch(float minPitch);
	void SetMaxPitch(float maxPitch);
	void SetDistance(float distance);
	void SetMinDistance(float minDistance);
	void SetMaxDistance(float maxDistance);

	void Zoom(float deltaDistance);
	void RotateAround(float deltaYaw, float deltaPitch);
};
