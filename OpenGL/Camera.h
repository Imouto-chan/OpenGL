#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera
{
public:
	Camera() = default;
	Camera(Resolution _resolution);
	virtual ~Camera() = default;

	void SetResolution(Resolution _resolution);
	glm::mat4 GetProjection() { return projection; }
	glm::mat4 GetView() { return view; }
	void SetWorldSpace(glm::vec3 _worldSpace);

private:
	glm::mat4 projection = {};
	glm::mat4 view = {};
	glm::vec3 worldSpace = glm::vec3(4, 3, 3);
};

#endif // CAMERA_H