#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh() = default;
	virtual ~Mesh();

	void Create(Shader* _shader);
	void Cleanup();
	void Render();

private:
	Shader* shader = nullptr;
	GLuint vertexBuffer;
	std::vector<GLfloat> m_vertexData;
};

#endif // MESH_H