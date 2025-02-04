#pragma once

#include <string>
#include "Material.h"

class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};

	Mesh(const std::string &GLMeshName);
	virtual ~Mesh(void);

	virtual void Render() = 0;
	virtual void Render(unsigned offset, unsigned count) = 0;

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;

	Material material;
	unsigned textureID;
};