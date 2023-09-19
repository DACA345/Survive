#pragma once

class Climate
{
public:

	Climate();

	Climate(double optMin, double optMax);

	bool optimum(double inputMin, double inputMax);

	void setOptimum(double inputMin, double inputMax);

private:

	double optimumMaxTemp;
	double optimumMinTemp;

};