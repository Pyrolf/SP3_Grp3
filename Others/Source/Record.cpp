#include "Record.h"


CRecord::CRecord(void)
{
	playername = "";
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

void CRecord::update(double dt)
{
	timing.setSec(dt + timing.getSec());
	timing.Normalising();
}

void CRecord::reset()
{
	timing.Reset();
}

