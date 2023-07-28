#pragma once
#include ""

class Bar
{
public:
	// Constructor with an integer parameter
	Bar(int initialVal);

	// Destructor 
	~Bar();

	// Method for addition
	int plus(int val);

	// Method for subtract
	int minus(int val);

	// Method to get current value
	int getValue() const;

private:
	int dataval; // Variable to store the int value
};

// Define constructor
Bar::Bar(int intialValue)
{
	dataval = intialValue; // Initialize dataval with the provided intial value
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
	return dataval; // return updated value
}

// Define subtract method
int Bar::minus(int val)
{
	dataval -= val; // original value minus input
	return dataval; // return updated value
}

// Define return value method
int Bar::getValue() const
{
	return dataval; // return current value without modifying
}