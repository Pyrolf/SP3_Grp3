#pragma once

#include <sstream>

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

	CTiming operator+(const CTiming&);
	bool operator>(const CTiming&);

	//void update(double dt);
	void Reset();

   
private:
	int min;
	double sec;
};

