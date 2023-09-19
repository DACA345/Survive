#include "climate.h"

Climate::Climate()
{
	optimumMinTemp = 0.0;
	optimumMaxTemp = 0.0;
}

Climate::Climate(double inputMin, double inputMax)
{
	optimumMinTemp = inputMin;
	optimumMaxTemp = inputMax;
}

Climate::setOptimum(double inputMin, double inputMax) 
{
	optimumMinTemp = inputMin;
	optimumMaxTemp = inputMax;
}

bool Climate::optimum(double inputMin, double inputMax)
{
	if (inputMin < optimumMinTemp || inputMax > optimumMaxTemp)
	{
		return false;
	}
	else
	{
		return true;
	}
}