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
		record[counter].getTiming().setMin(timeringa.getMin());
		record[counter].getTiming().setSec(timeringa.getSec());
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
		record[counter].getTiming().setMin(0);
		record[counter].getTiming().setSec(0);
	}

}

bool Highscore::ReadFromTextFile()
{
	string line;
	std::ifstream myfile;
	myfile.open("Highscore.txt");
	

	if (myfile.is_open())
	{
		cout << "File opened" << endl;
		int i = 0;
		while(i != 5)
		{
			std::getline(myfile, line);
			//std::stringstream myLine (line);
			line >> record[i];
			i += 1;
		}
	}
	else
	{
		cout << "File not opened" << endl;	
		return false;
	}
	
	myfile.close();

	return true;
}


//void Highscore::SaveTextFile()
//{
//	std::ofstream myfile;
//	myfile.open ("Highscore.txt", std::ios::in|std::ios::trunc);
//	myfile << highscore.getMin() << highscore.getSec() << endl;
//	myfile.close();
//}

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