#ifndef SHADER_H
#define SHADER_H

#include "../OpenGL/StandardIncludes.h"

class Shader
{
public:
	Shader() = default;
	virtual ~Shader();

	GLuint GetProgramID() { return programID; }
	GLuint GetAttrVertices() { return attrVertices; }
	GLuint GetAttrColors() { return attrColors; }
	GLuint GetAttrNormals() { return attrNormals; }
	GLuint GetAttrTangents() { return attrTangents; }
	GLuint GetAttrBitangents() { return attrBitangents; }
	GLuint GetAttrTexCoords() { return attrTexCoords; }
	GLuint GetAttrWVP() { return attrWVP; }
	GLuint GetAttrInstanceMatrix() { return attrInstanceMatrix; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetVec3(const char* _name, glm::vec3 _value);
	void SetMat4(const char* _name, glm::mat4 _value);
	void SetFloat(const char* _name, float _value);
	void SetTextureSampler(const char* _name, GLuint _texUint, int _texUintId, int _value);
	void SetInt(const char* _name, int _value);

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint programID = 0; // ID of out shader program
	GLuint attrVertices = 0; // Handle for the attribute vertex buffer
	GLuint attrColors = 0; // Handle for the attribute color
	GLuint attrNormals = 0; // Handle for the attribute normal
	GLuint attrTangents = 0; // Handle for the attribute tangents
	GLuint attrBitangents = 0; // Handle for the attribute bitangents
	GLuint attrTexCoords = 0; // Handle for the attribute tex coords
	GLuint attrWVP = 0;
	GLuint attrInstanceMatrix = 0;
	GLint result = GL_FALSE;
	int infoLogLength = 0;

};



#endif // SHADER_H