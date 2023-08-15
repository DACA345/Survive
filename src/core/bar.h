#pragma once

#define BAR_MAX 10
#define BAR_MIN 0

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

	// Method to return true/false if there's no more ints
	bool isEmpty() const;

private:
	int dataval; // Variable to store the int value
};