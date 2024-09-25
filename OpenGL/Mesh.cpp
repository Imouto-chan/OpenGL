#include "Mesh.h"
#include "Shader.h"

Mesh::~Mesh()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;

	//m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	m_vertexData = {
		/* Position */		 /* RGBA Color */
		0.2f, 0.2f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.9f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f,	 0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.0f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f,	 0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	vertexBuffer = 0;
}

void Mesh::Render(glm::mat4 wvp)
{
	glUseProgram(shader->GetProgramID()); // Use our shader

	// Set the world view project attribute
	wvp *= world;
	glUniformMatrix4fv(shader->GetAttrWVP(), 1, FALSE, &wvp[0][0]);

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(),			// Match the layout in the shader
		3			/*size*/,
		GL_FLOAT	/*type*/,
		GL_FALSE	/*normalized*/,
		7 * sizeof(float)			/*stride (7 floats per vertex definition)*/,
		(void*)0	/*offset*/);

	// Set the Colors attribute buffer
	glEnableVertexAttribArray(shader->GetAttrColors());
	glVertexAttribPointer(
		shader->GetAttrColors(),	//
		4,							// size
		GL_FLOAT,					// type
		GL_FALSE,					// normalized?
		7 * sizeof(float),			// stride (7 floats per vertex definition)
		(void*)(3 * sizeof(float))	// array buffer offset
	);

	// Draw the triangle
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrColors());
}