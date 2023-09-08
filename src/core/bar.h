#pragma once

#define BAR_MAX 100
#define BAR_MIN 0

/**
 * @brief 	This class describes a users bar.
 * 
 */
class Bar
{
public:
	/**
	 * @brief      Constructs a new bar with an initial value.
	 *
	 * @param[in]  initialVal  The initial value
	 */
	Bar(int initialVal);

	/**
	 * @brief      Constructs a new bar with the default max value..
	 */
	Bar();

	/**
	 * @brief      Destroys the object.
	 */
	~Bar();

	/**
	 * @brief      Additive update to the bars value.
	 *
	 * @param[in]  val   The value
	 *
	 * @return     The updated value.
	 */
	int plus(int val);

	/**
	 * @brief      Reductive update to the bars value.
	 *
	 * @param[in]  val   The value
	 *
	 * @return     The updated value.
	 */
	int minus(int val);

	/**
	 * @brief      Gets the value.
	 *
	 * @return     The value.
	 */
	int getValue() const;

	/**
	 * @brief      Determines if bar is empty.
	 *
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty() const;

private:
	/**
	 * Value of the bar.
	 */
	int dataval;
};