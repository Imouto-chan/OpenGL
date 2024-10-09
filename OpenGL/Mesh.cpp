#include "Mesh.h"
#include "Shader.h"

Mesh::~Mesh()
{
	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
	}
	if (indexBuffer != 0)
	{
		glDeleteBuffers(1, &indexBuffer);
	}

	texture.Cleanup();
	texture2.Cleanup();
}

void Mesh::Create(Shader* _shader)
{
	shader = _shader;
	texture = Texture();
	texture.LoadTexture("../Assets/Textures/Tacos.jpg");

	texture2 = Texture();
	texture2.LoadTexture("../Assets/Textures/Pattern.png");

	//m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	//m_vertexData = {
	//	/* Position */		 /* RGBA Color */
	//	0.2f, 0.2f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
	//	0.3f, 0.9f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,
	//	0.4f, 0.5f, 0.0f,	 0.0f, 0.0f, 1.0f, 1.0f,
	//	0.7f, 0.8f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
	//	0.8f, 0.0f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f,
	//	1.0f, 0.6f, 0.0f,	 0.0f, 0.0f, 1.0f, 1.0f,
	//	1.0f, 0.2f, 0.0f,	 1.0f, 0.0f, 0.0f, 1.0f,
	//	1.5f, 0.6f, 0.0f,	 0.0f, 1.0f, 0.0f, 1.0f
	//};

	//m_vertexData = {
	//	/* Position */		 /* RGBA Color */
	//	20.0f, 20.0f, 0.0f, 	1.0f, 0.0f, 0.0f, 1.0f,
	//	30.0f, 90.0f, 0.0f, 	0.0f, 1.0f, 0.0f, 1.0f,
	//	40.0f, 50.0f, 0.0f, 	0.0f, 0.0f, 1.0f, 1.0f,
	//	70.0f, 80.0f, 0.0f, 	1.0f, 0.0f, 0.0f, 1.0f,
	//	80.0f, 40.0f, 0.0f, 	0.0f, 1.0f, 0.0f, 1.0f,
	//	100.0f, 60.0f, 0.0f, 	0.0f, 0.0f, 1.0f, 1.0f,
	//	100.0f, 20.0f, 0.0f, 	1.0f, 0.0f, 0.0f, 1.0f,
	//	150.0f, 60.0f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f
	//};

	// Default values to reuse
	//float a = 26.0f;
	//float b = 42.0f;

	//m_vertexData = {
	//	/* Position */		 /* RGBA Color */
	//	-a, 0.0f, b,	1.0f, 0.0f, 0.0f, 1.0f, // Red
	//	a, 0.0f, b,		1.0f, 0.549f, 0.0f, 1.0f, // Orange
	//	-a, 0.0f, -b, 	1.0f, 1.0f, 0.0f, 1.0f, // Yellow
	//	a, 0.0f, -b, 	1.0f, 1.0f, 0.0f, 1.0f, // Green
	//	0.0f, b, a, 	0.0f, 0.0f, 1.0f, 1.0f,// Blue
	//	0.0f, b, -a, 	0.294f, 0.0f, 0.51f, 1.0f, // Indigo
	//	0.0f, -b, a, 	0.502f, 0.0f, 0.502f, 1.0f, // Purple
	//	0.0f, -b, -a, 	1.0f, 1.0f, 1.0f, 1.0f, //White
	//	b, a, 0.0f, 	0.0f, 1.0f, 1.0f, 1.0f, // Cyan
	//	-b, a, 0.0f, 	0.0f, 0.0f, 0.0f, 1.0f, // Black
	//	b, -a, 0.0f, 	0.118f, 0.565f, 1.0f, 1.0f, // Dodger blue
	//	-b, -a, 0.0f, 	0.863f, 0.078f, 0.235f, 1.0f // Crimson
	//};

	//m_vertexData = {
	//	/*Position*/			/*RGB Color*/
	//	50.0f, 50.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f, // Top=right
	//	50.0f, -50.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, // Bottom-right
	//	-50.0f, -50.0f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f, // Bottom-left
	//	-50.0f, 50.0f, 0.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f // Top-left
	//};

	m_vertexData = {
		/* Position */ /* Normals */ /* Texture Coords */
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	//m_indexData = {
	//	0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
	//	1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
	//	3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
	//	5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
	//	7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
	//};

	/*m_indexData = {
		2, 0, 3, 2, 1, 0
	};

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_indexData.size() * sizeof(float), m_indexData.data(), GL_STATIC_DRAW);*/
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	texture.Cleanup();
	texture2.Cleanup();

	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::Render(glm::mat4 wvp)
{
	glUseProgram(shader->GetProgramID()); // Use our shader

	// Set the DiffuseColor
	shader->SetVec3("DiffuseColor", { 1.0f, 0.0f, 0.0f });

	world = glm::rotate(world, 0.005f, { 0, 1, 0 });
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
		8 * sizeof(float)			/*stride (8 floats per vertex definition)*/,
		(void*)0	/*offset*/);

	// Set the Colors attribute buffer
	//glEnableVertexAttribArray(shader->GetAttrColors());
	//glVertexAttribPointer(
	//	shader->GetAttrColors(),	//
	//	4,							// size
	//	GL_FLOAT,					// type
	//	GL_FALSE,					// normalized?
	//	8 * sizeof(float),			// stride (8 floats per vertex definition)
	//	(void*)(3 * sizeof(float))	// array buffer offset
	//);

	glEnableVertexAttribArray(shader->GetAttrNormals());
	glVertexAttribPointer(shader->GetAttrNormals(),
		3, GL_FLOAT, GL_FALSE,	// size, type, normalized?
		8 * sizeof(float),		// stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float)) // array buffer offset
	);

	// Tex
	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),	
		2,							// size
		GL_FLOAT,					// type
		GL_FALSE,					// normalized
		8 * sizeof(float),			// stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float))	// array buffer offset
	);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetTexture()); // Bind the texture
	glUniform1i(shader->GetSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2.GetTexture()); // Bind the texture
	glUniform1i(shader->GetSampler2(), 1);

	// Draw the triangle
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	//glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0); // Draw based off index data
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 8);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	//glDisableVertexAttribArray(shader->GetAttrColors());
	glDisableVertexAttribArray(shader->GetAttrNormals());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}