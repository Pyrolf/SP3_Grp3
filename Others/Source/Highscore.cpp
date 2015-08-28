#include "Highscore.h"

Highscore::Highscore()
{
	counter = 0;
}

Highscore::~Highscore()
{
	ofstream myFile("Highscore.txt");
	int i = 0;
	if(myFile.is_open())
	{
		while(i != 5)
		{
			myFile << record[i].getTiming().getMin() << " " << record[i].getTiming().getSec() <<  record[i].getName() << endl;
			i++;
		}
	}
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

/*
int writehighscore(string szFileName, Highscore* phs)
ofstream myFile(szFileName);
int i =  0;
if(myFile.open())
{
while(phs->szName.length())
{
myFile << phs->szName << " " << phs->score << endl;
++i;
phs++;
}
return i;
}
*/

int Highscore::writehighscore(string File, CRecord rec)
{
	ofstream myFile(File);
	int i = 0;
	if(myFile.is_open())
	{
		while(i < 5)
		{
			myFile << rec.getTiming().getMin() << ":" << rec.getTiming().getSec() << " " <<  rec.getName() << endl;
		}
	}
	return i;
}

bool Highscore::HighscoreCheck(CRecord recs)
{
	if(recs.getTiming().getMin() == record[4].getTiming().getMin())
	{
		if(recs.getTiming().getSec() < record[4].getTiming().getSec())
		{
			return true;
		}
		else 
			return false;
	}
	else if(recs.getTiming().getMin() > record[4].getTiming().getMin())
	{
		return false;
	}
	else
		return true;
}

void Highscore::storeNewRecord(CRecord recs)
{
	for(int i = 4; i >= 0; --i)
	{
		if(recs.getTiming().getMin() == record[i].getTiming().getMin())
		{
			if(recs.getTiming().getSec() >= record[i].getTiming().getSec())
			{
				for(int k = 4; k > i; --k)
				{
					record[k] = record[k - 1];
				}
				record[i] = recs;
				return;
			}
		}
		else if(recs.getTiming().getMin() > record[i].getTiming().getMin())
		{
			for(int k = 4; k > i; --k)
			{
				record[k] = record[k - 1];
			}
			record[i] = recs;
			return;
		}
	}
	for(int k = 4; k > 0; --k)
	{
		record[k] = record[k - 1];
	}

	record[0] = recs;
}