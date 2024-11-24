#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{
public:
	Camera() = default;
	Camera(const Resolution &_resolution, const float _near = 0.1f, const float _far = 1000.0f);
	virtual ~Camera() = default;

	void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
	{
		position = _position;
		view = glm::lookAt(_position, _lookAt, _up);
	}

	void SetResolution(const Resolution& _resolution, const float _near, const float _far);
	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	glm::vec3 GetPosition() { return position; }
	//void SetWorldSpace(glm::vec3 _worldSpace);

private:
	glm::mat4 projection = {};
	glm::mat4 view = {};
	glm::vec3 position = {};
	//glm::vec3 worldSpace = glm::vec3(4, 3, 3);
};

#endif // CAMERA_H