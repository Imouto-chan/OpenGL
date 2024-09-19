#include "Camera.h"

Camera::Camera(Resolution _resolution)
{
	projection = glm::perspective(glm::radians((float)_resolution.fov),
		(float)_resolution.width / (float)_resolution.height,
		0.1f,
		1000.0f);

	view = glm::lookAt(
		worldSpace, // Camera is at 4, 3, 3 in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}

void Camera::SetResolution(Resolution _resolution)
{
	projection = glm::perspective(glm::radians((float)_resolution.fov),
		(float)_resolution.width / (float)_resolution.height,
		0.1f,
		1000.0f);

	view = glm::lookAt(
		worldSpace, // Camera is at 4, 3, 3 in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}

void Camera::SetWorldSpace(glm::vec3 _worldSpace)
{
	worldSpace = _worldSpace;
}
