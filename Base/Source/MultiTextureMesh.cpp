#include "MultiTextureMesh.h"
#include "GL\glew.h"

MultiTextureMesh::MultiTextureMesh(const std::string &GLMeshName)
	:
GLMesh(GLMeshName)
{
}

MultiTextureMesh::~MultiTextureMesh(void)
{
	for(int i = 0; i < textures.size(); ++i)
	{
		glDeleteTextures(1, &textures[i]);
	}

	//To prevent GLMesh from deleting the texures again
	textureID = 0;
}

void MultiTextureMesh::ChangeTexture(const int slot)
{
	textureID = textures[slot];
}