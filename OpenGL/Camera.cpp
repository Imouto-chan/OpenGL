#include "Camera.h"

Camera::Camera(const Resolution& _resolution, const float _near, const float _far)
{
	projection = glm::perspective(glm::radians((float)_resolution.fov),
		(float)_resolution.width / (float)_resolution.height,
		_near,
		_far);

	view = glm::lookAt(
		glm::vec3(1, 0, 0), // Default is at 1, 0, 0 in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}

void Camera::SetResolution(const Resolution& _resolution, const float _near, const float _far)
{
	projection = glm::perspective(glm::radians((float)_resolution.fov),
		(float)_resolution.width / (float)_resolution.height,
		_near,
		_far);

	view = glm::lookAt(
		glm::vec3(1, 0, 0), // Default is at 1, 0, 0 in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0, -1, 0 to look upside-down
	);
}
//
//void Camera::SetWorldSpace(glm::vec3 _worldSpace)
//{
//	worldSpace = _worldSpace;
//}
