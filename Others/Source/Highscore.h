#pragma once
#include "Timing.h"
class Highscore
{
public:
	Highscore();
	~Highscore();

	void newScore(CTiming);
	int getCount(void);

	void sortingofScore(int first, int last);

	void reset();

private:	
	CTiming timerin[5];
	int counter;
};