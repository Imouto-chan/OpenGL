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
	GLuint GetAttrTexCoords() { return attrTexCoords; }
	GLuint GetSampler1() { return sampler1; }
	GLuint GetSampler2() { return sampler2; }
	GLuint GetAttrWVP() { return attrWVP; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	void SetVec3(const char* _name, glm::vec3 _value);
	void SetMat4(const char* _name, glm::mat4 _value);

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint programID = 0; // ID of out shader program
	GLuint attrVertices = 0; // Handle for the attribute vertex buffer
	GLuint attrColors = 0; // Handle for the attribute color
	GLuint attrNormals = 0; // Handle for the attribute Normal
	GLuint attrTexCoords = 0; // Handle for the attribute tex coords
	GLuint sampler1 = 0; // Handle for the attribute sampler 1
	GLuint sampler2 = 0; // Handle for the attribute sampler 2
	GLuint attrWVP = 0;
	GLint result = GL_FALSE;
	int infoLogLength = 0;

};



#endif // SHADER_H