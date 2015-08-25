#pragma once
#include "Timing.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Highscore
{
public:
	Highscore();
	~Highscore();

	void newScore(CTiming);
	int getCount(void);

	void reset();

	bool ReadFromTextFile();
	void SaveTextFile();
	//void HighscoreCheck(double b);

private:	
	CTiming timerin[5];
	int counter;
	CTiming highscore;
	string PlayerName;
};