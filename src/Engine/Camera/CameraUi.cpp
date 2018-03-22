#include "CameraUi.h"

CameraUi::CameraUi()
{
}

glm::mat4 CameraUi::ViewMatrix() const
{
	return glm::mat4(1);
}

glm::mat4 CameraUi::ProjectionMatrix() const
{
	return glm::mat4(1);
}
