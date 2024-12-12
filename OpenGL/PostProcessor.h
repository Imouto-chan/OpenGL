#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "Shader.h"

class PostProcessor
{
public:
	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

private:
	void CreateVertices();
	void CreateBuffers();
	void BindVertices();

private:
	GLuint framebuffer = 0;
	GLuint textureColorbuffer = 0;
	GLuint renderBufferObject = 0;
	GLuint vertexBuffer = 0; // GPU Vertex Buffer
	Shader* postShader = nullptr;
};

#endif // POSTPROCESSOR_H