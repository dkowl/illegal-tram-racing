#pragma once
#include "Camera.h"

class CameraUi : public Camera
{
	float aspectRatio;

public:
	CameraUi();

	glm::mat4 ViewMatrix() const override;
	glm::mat4 ProjectionMatrix() const override;

	void SetAspectRatio(float aspectRatio);
};
