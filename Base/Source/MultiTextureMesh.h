#pragma once
#include "GLMesh.h"
#include "MultiTexture.h"

class MultiTextureMesh : public MultiTexture, public GLMesh
{
public:
	MultiTextureMesh(const std::string &GLMeshName);
	virtual ~MultiTextureMesh(void);

	void ChangeTexture(const int slot);
};