#ifndef GLMESH_H
#define GLMESH_H

#include "Mesh.h"

class GLMesh : public Mesh
{
public:
	GLMesh(const std::string &GLMeshName);
	virtual ~GLMesh();
	void Render();
	void Render(unsigned offset, unsigned count);

	
};

#endif