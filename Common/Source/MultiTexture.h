#pragma once

#include <vector>

class MultiTexture
{
public:
	MultiTexture();
	~MultiTexture(void);

	std::vector<unsigned> textures;

	virtual void ChangeTexture(const int slot) = 0;
};

