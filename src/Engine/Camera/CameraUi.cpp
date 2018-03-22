#include "CameraUi.h"

CameraUi::CameraUi()
{
}

glm::mat4 CameraUi::ViewMatrix() const
{
	//return glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	return glm::mat4(1);
}

glm::mat4 CameraUi::ProjectionMatrix() const
{
	return glm::ortho(-1, 1, -1, 1);
}
