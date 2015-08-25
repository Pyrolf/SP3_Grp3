#pragma once

#include <sstream>
#include <string>

class CTiming
{
public:
	CTiming(void);
	CTiming(int min, int sec);
	~CTiming(void);

	void Normalising();

	int getMin();
	void setMin(int);

	double getSec();
	void setSec(double);

	friend std::istream& operator>>(std::istream& is, CTiming& timing)
    {
        std::string line;
        std::string temp;
        std::getline(is, line);

        std::istringstream iss(line);

        iss >> temp;
		timing.min = std::stod(temp);

		temp.clear();
        iss >> temp;
		timing.sec = std::stod(temp);

        std::getline(iss, timing.name);

        return is;
    };

	CTiming operator+(const CTiming&);
	bool operator>(const CTiming&);

	void update(double dt);
	void Reset();

   
private:
	int min;
	double sec;
	std::string name;
};

