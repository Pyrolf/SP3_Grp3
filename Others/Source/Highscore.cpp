#include "Highscore.h"

Highscore::Highscore()
{
	counter = 0;
}

Highscore::~Highscore()
{
}

void Highscore::newScore(CTiming timeringa)
{
	if(counter < 5)
	{
		timerin[counter].setMin(timeringa.getMin());
		timerin[counter].setSec(timeringa.getSec());
		counter++;
	}
}

int Highscore::getCount(void)
{
	return counter;
}

void Highscore::reset()
{
	for(int i = 0; i < counter; ++i)
	{
		timerin[counter].setMin(0);
		timerin[counter].setSec(0);
	}

}


bool Highscore::ReadFromTextFile()
{
	stringstream line;
	std::ifstream myfile ("HighScore.txt");
	if (myfile.is_open())
	{
		myfile >> highscore;
	}
	else
		return false;
	return true;
}


void Highscore::SaveTextFile()
{
	std::ofstream myfile;
	myfile.open ("HighScore.txt", std::ios::in|std::ios::trunc);
	myfile << highscore.getMin() << highscore.getSec() << endl;
	myfile.close();
}

//void Highscore::HighscoreCheck(double b)
//{
//	highscore = b;
//	if (highscore > b)
//	{
//		SaveTextFile();
//		highscore = b;
//	}
//
//}