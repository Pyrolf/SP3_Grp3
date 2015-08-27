#include "Record.h"


CRecord::CRecord(void)
{
	playername = "Name";
}


CRecord::~CRecord(void)
{
}

CTiming CRecord::getTiming()
{
	return timing;
}

void CRecord::setTiming(CTiming time)
{
	timing = time;
}

string CRecord::getName()
{
	return playername;
}

void CRecord::setName(string name)
{
	playername = name;
}