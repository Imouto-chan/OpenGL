#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh() = default;
	virtual ~Mesh();

	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 wvp);

private:
	Shader* shader = nullptr;
	Texture texture {};
	Texture texture2{};
	GLuint vertexBuffer;
	GLuint indexBuffer = 0;
	std::vector<GLfloat> m_vertexData;
	std::vector<GLubyte> m_indexData;
	glm::mat4 world = glm::mat4(1);
	glm::vec3 position;
	glm::vec3 rotation;
};

#endif // MESH_H