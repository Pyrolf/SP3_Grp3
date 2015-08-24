#pragma once
#include "HackingBar.h"
#include <vector>;

class HackingGame
{
public:
	bool active;
	Vector3 bottomLeftPos, topRightPos;
	std::vector<HackingBar*> hackingBar;
	int currentBar;

	HackingGame(void);
	~HackingGame(void);

	void Init(Vector3 bottomLeftPos, Vector3 topRightPos);
	void Update(double dt);
	bool Input();
};

