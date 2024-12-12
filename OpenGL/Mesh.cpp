#include "Mesh.h"
#include "Shader.h"
#include "GameController.h"
#include <OBJ_Loader.h>

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

	textureDiffuse.Cleanup();
	textureSpecular.Cleanup();
}

void Mesh::Create(Shader* _shader, std::string _file)
{
	shader = _shader;

	objl::Loader loader;
	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh"); // Load .obj file

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];
		std::vector<objl::Vector3> tangents;
		std::vector<objl::Vector3> bitangents;
		std::vector<objl::Vertex> triangle;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
		{
			triangle.clear();
			triangle.push_back(curMesh.Vertices[j]);
			triangle.push_back(curMesh.Vertices[j + 1]);
			triangle.push_back(curMesh.Vertices[j + 2]);
			CalculateTangents(triangle, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

			if (loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}

	//std::string diffuseMap = loader.LoadedMaterials[0].map_Kd;
	//const size_t last_slash_idx = diffuseMap.find_last_of("\\/");
	//if (std::string::npos != last_slash_idx)
	//{
	//	diffuseMap.erase(0, last_slash_idx + 1);
	//}

	//textureDiffuse = Texture();
	//textureDiffuse.LoadTexture("../Assets/Textures/" + diffuseMap);

	//textureSpecular = Texture();
	//textureSpecular.LoadTexture("../Assets/Textures/" + diffuseMap);

	textureDiffuse = Texture();
	if (loader.LoadedMaterials[0].map_Kd != "")
	{
		textureDiffuse.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));
	}
	else // backup just for safety
	{
		textureDiffuse.LoadTexture("../Assets/Textures/Pattern.png");
	}

	textureSpecular = Texture();
	if (loader.LoadedMaterials[0].map_Ks != "")
	{
		textureSpecular.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
	}

	textureNormal = Texture();
	if (loader.LoadedMaterials[0].map_bump != "")
	{
		enableNormalMaps = true;
		textureNormal.LoadTexture("../Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
	}

	vertexStride = 8;
	if (enableNormalMaps)
	{
		vertexStride += 6;
	}

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	textureDiffuse.Cleanup();
	textureSpecular.Cleanup();

	vertexBuffer = 0;
	indexBuffer = 0;
}

void Mesh::CalculateTransform()
{
	// Remember Matrix math is right to left so you read it bottom up
	// If we write this we get: world = T * R(Yaw, Pitch, Roll) * S
	world = glm::translate(glm::mat4(1.0f), position);
	world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0)); // Yaw
	world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0)); // Pitch
	world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1)); // Roll
	world = glm::scale(world, scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	shader->SetMat4("World", world);
	shader->SetMat4("WVP", _pv * world);
	shader->SetVec3("CameraPosition", cameraPosition);
	shader->SetInt("EnableNormalMaps", enableNormalMaps);

	std::vector<Mesh*>& lights = GameController::GetInstance().GetLights();
	for (int i = 0; i < lights.size(); i++)
	{
		// Configure Light
		shader->SetVec3(Concat("light[", i, "].position").c_str(), lights[i]->GetPosition());
		shader->SetVec3(Concat("light[", i, "].direction").c_str(), lights[i]->GetLightDirection());

		shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), { 1.0f, 1.0f, 1.0f });
		shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), lights[i]->GetColor());
		shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

		shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), 0.032f);

		shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 200);
	}
	
	// Configure Material
	shader->SetFloat("material.specularStrength", 8.0f);
	shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, textureDiffuse.GetTexture());
	shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, textureSpecular.GetTexture());
	shader->SetTextureSampler("material.normalTexture", GL_TEXTURE1, 2, textureNormal.GetTexture());
}

void Mesh::Render(glm::mat4 _pv)
{
	glUseProgram(shader->GetProgramID()); // Use our shader

	rotation.y += 0.005f;

	CalculateTransform();
	SetShaderVariables(_pv);
	BindAttributes();

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / vertexStride);
	glDisableVertexAttribArray(shader->GetAttrVertices());
	glDisableVertexAttribArray(shader->GetAttrNormals());
	glDisableVertexAttribArray(shader->GetAttrTexCoords());
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(shader->GetAttrVertices());
	glVertexAttribPointer(
		shader->GetAttrVertices(),			// Match the layout in the shader
		3			/*size*/,
		GL_FLOAT	/*type*/,
		GL_FALSE	/*normalized*/,
		vertexStride * sizeof(float)			/*stride (8 floats per vertex definition)*/,
		(void*)0	/*offset*/);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(shader->GetAttrNormals());
	glVertexAttribPointer(shader->GetAttrNormals(),
		3, GL_FLOAT, GL_FALSE,	// size, type, normalized?
		vertexStride * sizeof(float),		// stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float)) // array buffer offset
	);

	// Tex
	glEnableVertexAttribArray(shader->GetAttrTexCoords());
	glVertexAttribPointer(
		shader->GetAttrTexCoords(),
		2,							// size
		GL_FLOAT,					// type
		GL_FALSE,					// normalized
		vertexStride * sizeof(float),			// stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float))	// array buffer offset
	);

	if (enableNormalMaps)
	{
		// 4th Attribute buffer : tangent
		glEnableVertexAttribArray(shader->GetAttrTangents());
		glVertexAttribPointer(
			shader->GetAttrTangents(),
			3,							// size
			GL_FLOAT,					// type
			GL_FALSE,					// normalized
			vertexStride * sizeof(float),			// stride (8 floats per vertex definition)
			(void*)(8 * sizeof(float))	// array buffer offset
		);

		// 5th Attribute buffer : bitangent
		glEnableVertexAttribArray(shader->GetAttrBitangents());
		glVertexAttribPointer(
			shader->GetAttrBitangents(),
			3,							// size
			GL_FLOAT,					// type
			GL_FALSE,					// normalized
			vertexStride * sizeof(float),			// stride (8 floats per vertex definition)
			(void*)(11 * sizeof(float))	// array buffer offset
		);
	}

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture.GetTexture()); // Bind the texture
	//glUniform1i(shader->GetSampler1(), 0);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2.GetTexture()); // Bind the texture
	//glUniform1i(shader->GetSampler2(), 1);
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
	std::string index = std::to_string(_index);
	return (_s1 + index + _s2);
}

std::string Mesh::RemoveFolder(std::string& _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}
	return _map;
}

void Mesh::CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	// Calculate tangent/bitangent vectors of both triangles
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

	_bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}
