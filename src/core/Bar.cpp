#include "Bar.h"

// Define constructor
Bar::Bar(int intialValue)
{
	dataval = intialValue; // Initialize dataval with the provided intial value
}

// Constructor with no parameter (defaults to 10)
Bar::Bar() : dataval(10)
{
	// Since there is no parameter, the constructor will initialize dataval to 10.
}


// Define Destructor
Bar::~Bar()
{
	// code here
}

// Define addtion method
int Bar::plus(int val)
{
	dataval += val; // original value plus input
	// Apply limits after addition to ensure the health bar stays within bounds.
	if (dataval > 10)
		dataval = 10;
	return dataval; // return updated value
}

// Define subtract method
int Bar::minus(int val)
{
	dataval -= val; // original value minus input
	// Apply limits after subtraction to ensure the health bar stays within bounds.
	if (dataval < 0)
		dataval = 0;
	return dataval; // return updated value
}

// Define return value method
int Bar::getValue() const
{
	return dataval; // return current value without modifying
}