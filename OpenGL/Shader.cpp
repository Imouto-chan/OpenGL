#include "Shader.h"
#include <iostream>

Shader::~Shader()
{
	if (programID != 0)
		glDeleteProgram(programID);
}

void Shader::Cleanup()
{
	glDeleteProgram(programID);
	programID = 0;
}

void Shader::SetVec3(const char* _name, glm::vec3 _value)
{
	GLint loc = glGetUniformLocation(programID, _name);
	if (loc != -1)
	{
		glUniform3fv(loc, 1, &_value[0]);
	}
}

void Shader::SetMat4(const char* _name, glm::mat4 _value)
{
	GLint loc = glGetUniformLocation(programID, _name);
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]);
	}
}

void Shader::LoadAttributes()
{
	attrVertices = glGetAttribLocation(programID, "vertices"); // Get a handle for the vertex buffer
	attrColors = glGetAttribLocation(programID, "colors"); // Get a handle for the colors buffer
	attrNormals = glGetAttribLocation(programID, "normals"); // Get a handle for the normal
	attrTexCoords = glGetAttribLocation(programID, "texCoords"); // Get a handle for the texture coords buffer
	sampler1 = glGetUniformLocation(programID, "sampler1"); // Get a handle for the texture sampler 1
	sampler2 = glGetUniformLocation(programID, "sampler2"); // Get a handle for the texture sampler 2
	attrWVP = glGetUniformLocation(programID, "WVP"); // Get a to the WVP
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0)
	{
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type); // Create the shader

	// Read the Shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ !\N", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
	{
		shaderCode += "\n" + Line;
	}
	shaderStream.close();

	// Compile Shader
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, shaderID);

	// Attach shader to program
	glAttachShader(programID, shaderID);

	return shaderID;
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	programID = glCreateProgram(); // Create the shader program
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER); // Load vertex shader
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER); // Load fragment shader
	glLinkProgram(programID); // Link the program

	// Check the program
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	EvaluateShader(infoLogLength, programID);

	// Free resources
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}
