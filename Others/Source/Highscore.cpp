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

void Highscore::sortingofScore(int first, int last)
{
//	if(first < last)
//	{
//		int middle = (first + last)/2;
//		sortingofScore(first, middle);
//		MergeSort(middle + 1, last,false, true);
//		mergeIDDesc(first, middle, last);
//	}
}

void Highscore::reset()
{
	for(int i = 0; i < counter; ++i)
	{
		timerin[counter].setMin(0);
		timerin[counter].setSec(0);
	}

}