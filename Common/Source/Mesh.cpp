#include "Mesh.h"

Mesh::Mesh(const std::string &GLMeshName)
: name(GLMeshName)
, mode(DRAW_TRIANGLES)
{
}

Mesh::~Mesh(void)
{
}
