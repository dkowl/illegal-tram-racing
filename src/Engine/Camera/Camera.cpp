#include "Camera.h"

Camera::Camera() = default;

void Camera::SetScreenshakeOffset(const glm::vec3 &offset)
{
	screenshakeOffset = offset;
}
