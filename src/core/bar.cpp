#include "bar.h"

// Define constructor
Bar::Bar(int initialValue)
{
    dataval = initialValue; // Initialize dataval with the provided initial value
}

// Constructor with no parameter (defaults to 10)
Bar::Bar() : dataval(BAR_MAX)
{
    // Since there is no parameter, the constructor will initialize dataval to 10.
}

// Define Destructor
Bar::~Bar()
{
    // code here
}

// Define addition method
int Bar::plus(int val)
{
    dataval += val; // original value plus input
    // Apply limits after addition to ensure the health bar stays within bounds.
    if (dataval > BAR_MAX)
        dataval = BAR_MAX;
    return dataval; // return updated value
}

// Define subtract method
int Bar::minus(int val)
{
    dataval -= val; // original value minus input
    // Apply limits after subtraction to ensure the health bar stays within bounds.
    if (dataval < BAR_MIN)
        dataval = BAR_MIN;
    return dataval; // return updated value
}

// Define return value method
int Bar::getValue() const
{
    return dataval; // return current value without modifying
}

// Define isEmpty bool method
bool Bar::isEmpty() const
{
    return dataval == 0;
}
