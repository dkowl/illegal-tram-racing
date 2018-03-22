#pragma once
#include "Camera.h"

class CameraUi : public Camera
{
public:
	CameraUi();

	glm::mat4 ViewMatrix() const override;
	glm::mat4 ProjectionMatrix() const override;
};
