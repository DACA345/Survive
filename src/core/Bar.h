#pragma once

class Bar
{
public:
	// Constructor with an integer parameter
	Bar(int initialVal);

	// Default Constructor
	Bar();

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