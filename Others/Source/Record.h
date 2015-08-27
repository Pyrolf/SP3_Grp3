#pragma once
#include <string>
#include "Timing.h"
using namespace std;

class CRecord
{
public:
	CRecord(void);
	~CRecord(void);

    CTiming getTiming();
	void setTiming(CTiming);

	string getName();
	void setName(string);
	
	friend std::string& operator>>(std::string& line, CRecord& record)
	{
		//std::string line;
		std::string temp;
		CTiming timeTemp;
		/*std::getline(is, line);*/

		std::istringstream iss(line);

		iss >> temp;
		timeTemp.setMin(std::stoi(temp));
		record.setTiming(timeTemp);
		temp.clear();

		iss >> temp;
		timeTemp.setSec(std::stod(temp));
		record.setTiming(timeTemp);
		temp.clear();

		std::getline(iss, temp);
		record.setName(temp);

		return line;
    };

private:
	CTiming timing;
	string playername;

};

