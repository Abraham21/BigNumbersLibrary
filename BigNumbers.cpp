#include "stdafx.h"
#include "math.h"
#include "BigNumbersNamespace.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace BigNumbersNamespace;

/*!
* \brief default contructor
* \details Initializes BigNumber to value of zero
* \param none
*/
BigNumberClass::BigNumberClass()
{
	//initialize to 0
	//negative number = false
	bigNumberDigits.push_back(0);
	negativeNumber = false;
}

/*!
* \brief contructor
* \details Initializes BigNumber to a value given from string
* \param value from string
*/
BigNumberClass::BigNumberClass(std::string val)
{
	std::string newNumber = val;
	//check if user input is 10,000 digits or less
	//throw exception if necessary
	if (newNumber.length() > 10000) throw NumberOverflowException();
	//checks if negative
	if (newNumber[0] == '-') negativeNumber = true;
	else negativeNumber = false;
	//if negative number, remove negative sign
	if (negativeNumber)
	{
		newNumber.erase(0, 1);
		for (int counter = newNumber.length() - 1; counter >= 0; counter--)
			bigNumberDigits.insert(bigNumberDigits.begin(), newNumber[counter] - '0');
	}
	else
	{
		for (int counter = newNumber.length() - 1; counter >= 0; counter--)
			bigNumberDigits.insert(bigNumberDigits.begin(), newNumber[counter] - '0');
	}
}

/*!
* \brief A method that takes in a vector and flips its order
* \param Takes in a vector
*/
void BigNumberClass::flipVector(std::vector <int> vectorToFlip)
{
	int temp;
	int indexVector = vectorToFlip.size() - 1;
	for (int count = 0; count < vectorToFlip.size() / 2; count++) {
		temp = vectorToFlip[count];
		vectorToFlip[count] = vectorToFlip[count];
		vectorToFlip[indexVector] = temp;
		indexVector -= 1;
	}
}

/*!
* \brief A method that compares vectors and returns true if
*		 1st parameter is greater than 2nd parameter
* \param Takes in two vectors
*/
bool BigNumberClass::greaterThan(std::vector <int> vector1, std::vector <int> vector2)
{
	if (vector1.size() > vector2.size())
	{
		//vector 1 is greater than vector 2, return true
		return true;
	}
	else
	{
		//vector 1 is not greater than vector 2, return true
		return false;
	}
}

/*!
* \brief A method that compares vectors and returns true if
*		 1st parameter is less than 2nd parameter
* \param Takes in two vectors
*/
bool BigNumberClass::lessThan(std::vector<int> vector1, std::vector<int> vector2)
{
	//initialize nums
	int num1 = vector1.size();
	int num2 = vector2.size();
	if (num1 < num2) return true;
	if (num2 < num1) return false;
	//logic to check if smaller
	for (int i = 0; i < num1; i++)
		if (vector1[i] < vector2[i]) return true; else
			if (vector1[i] > vector2[i]) return false;
	//return false if no value has been returned already
	return false;
}

/*!
* \brief A method that subtracts two vectors
*		 and stores the result in a third vector.
* \param Takes in three vectors
*/
void BigNumberClass::subtractHelper(std::vector <int> vector1, std::vector <int> vector2, std::vector <int> vector3)
{
	std::vector <int> value1 = vector1, value2 = vector2;

	if (lessThan(value1, value2))
	{
		//need to check if less than value for correct sign
		swap(value1, value2);
	}

	int hold = 0;
	int num1 = value1.size();
	int num2 = value2.size();
	int difference = num1 - num2;

	for (int counter = num2 - 1; counter >= 0; counter--) {
		int val = ((value1[counter + difference]) - (value2[counter]) - hold);
		if (val < 0)
		{
			hold = 1;
			val += 10;
		}
		else {
			hold = 0;
		}
		vector3.push_back(val);
	}

	for (int counter = num1 - num2 - 1; counter >= 0; counter--) {
		if (value1[counter] == 0 && hold) {
			vector3.push_back('9');
			continue;
		}
		int val = ((value1[counter]) - hold);
		if (counter>0 || val>0) vector3.push_back(val);
		hold = 0;
	}
	flipVector(vector3);
}

/*!
* \brief A method that adds two vectors and stores
*		 the result in a third vector
* \param Takes in three vectors
*/
void BigNumberClass::addHelper(std::vector <int> vector1, std::vector <int> vector2, std::vector <int> vector3)
{
	std::vector<int> value1 = vector2, value2 = vector2;

	if (value1.size() > value2.size()) swap(value1, value2);

	int hold = 0;
	int num1 = value1.size();
	int num2 = value2.size();
	int difference = num2 - num1;

	for (int counter = num1 - 1; counter >= 0; counter--) {
		int val = ((value1[counter]) + (value2[counter + difference]) + hold);
		vector3.push_back(val % 10);
		hold = val / 10;
	}
	for (int counter = num2 - num1 - 1; counter >= 0; counter--) {
		int val = ((value2[counter]) + hold);
		vector3.push_back(val % 10);
		hold = val / 10;
	}
	if (hold)
	{
		//push back the hold value if needed
		vector3.push_back(hold);
	}
	//flips vector
	flipVector(vector3);
}

/*!
* \brief Operation overloading for * multiplication functionality
* \param Takes in BigNumberClass
*/
BigNumberClass BigNumbersNamespace::BigNumberClass::operator *(BigNumberClass right) {
	BigNumberClass result;
	if (negativeNumber != right.negativeNumber) result.negativeNumber = true;
	int num1 = bigNumberDigits.size(), num2 = right.bigNumberDigits.size();
	std::vector<int> vectorResult(num1 + num2, 0);
	std::string string1;
	std::string string2;

	for (int counter = 0; counter < bigNumberDigits.size(); counter++) string1 += bigNumberDigits[counter] + '0';
	for (int counter = 0; counter < right.bigNumberDigits.size(); counter++) string2 += right.bigNumberDigits[counter] + '0';
	if (string1 == "0" || string2 == "0") return result;

	int number1 = 0, number2 = 0;

	for (int counter = num1 - 1; counter >= 0; counter--) {
		int hold = 0;
		int num1 = string1[counter] - '0';
		number2 = 0;
		for (int indexWithin = num2 - 1; indexWithin >= 0; indexWithin--) {
			int num2 = string2[indexWithin] - '0';
			int val = hold + vectorResult[number1 + number2] + (num1 * num2);
			hold = val / 10;
			vectorResult[number1 + number2] = val % 10;
			number2++;
		}
		if (hold > 0)
		{
			//need to account for hold value
			vectorResult[number1 + number2] += hold;
		}
		//increment
		number1++;
	}
	int vectorCounter = vectorResult.size() - 1;
	while (vectorCounter >= 0 && vectorResult[vectorCounter] == 0) vectorCounter--;
	std::string values = "";
	while (vectorCounter >= 0) {
		//fill values string with values from vector
		values += std::to_string(vectorResult[vectorCounter--]);
	}
	for (int count = 0; count < values.length(); count++) result.bigNumberDigits.push_back(values[count] - '0');
	while (result.bigNumberDigits[0] == 0) result.bigNumberDigits.erase(result.bigNumberDigits.begin());
	return result;
}

/*!
* \brief Operation overloading for / division functionality
* \param Takes in BigNumberClass
*/
BigNumberClass BigNumbersNamespace::BigNumberClass::operator /(BigNumberClass right) {
	BigNumbersNamespace::BigNumberClass result;
	//check if trying to divide by zero and throw exception if necessary
	if (int(right.bigNumberDigits.size()) == 1 && right.bigNumberDigits[0] == 0) {
		throw new ModulusByZeroException();
	}
	//divide logic
	while (result.bigNumberDigits[0] == 0) result.bigNumberDigits.erase(result.bigNumberDigits.begin());
	return result;
}

/*!
* \brief Operation overloading for % modulus functionality
* \param Takes in BigNumberClass
*/
BigNumberClass BigNumbersNamespace::BigNumberClass::operator %(BigNumberClass right) {
	bool greater;
	BigNumbersNamespace::BigNumberClass result;
	//check if trying to modulus by zero and throw exception if necessary
	if (int(right.bigNumberDigits.size()) == 1 && right.bigNumberDigits[0] == 0) {
		throw new ModulusByZeroException();
	}
	//modulus logic
	while (result.bigNumberDigits[0] == 0) result.bigNumberDigits.erase(result.bigNumberDigits.begin());
	return result;
}

/*!
* \brief Operation overloading for - subtraction functionality
* \param Takes in BigNumberClass
*/
BigNumberClass BigNumbersNamespace::BigNumberClass::operator -(BigNumberClass right) {
	BigNumberClass result;
	bool greater = !lessThan(bigNumberDigits, result.bigNumberDigits);
	if (negativeNumber != right.negativeNumber)
	{
		if (greater && !negativeNumber)
		{
			addHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
			result.negativeNumber = false;
		}
		else if (greater && negativeNumber)
		{
			addHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
			result.negativeNumber = true;
		}
		else if (!greater)
		{
			addHelper(right.bigNumberDigits, bigNumberDigits, result.bigNumberDigits);
			result.negativeNumber = false;
		}
	}
	else if (negativeNumber && right.negativeNumber) {
		if (!greater)
		{
			subtractHelper(right.bigNumberDigits, bigNumberDigits, result.bigNumberDigits);
			result.negativeNumber = false;
		}
		else {
			subtractHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
			result.negativeNumber = true;
		}
	}
	else {
		if (!greater) {
			result.negativeNumber = true;
			subtractHelper(right.bigNumberDigits, bigNumberDigits, result.bigNumberDigits);
		}
		else {
			result.negativeNumber = false;
			subtractHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
		}
	}
	while (result.bigNumberDigits[0] == 0) result.bigNumberDigits.erase(result.bigNumberDigits.begin());
	return result;
}

/*!
* \brief Operation overloading for + addition functionality
* \param Takes in BigNumberClass
*/
BigNumberClass BigNumbersNamespace::BigNumberClass::operator +(BigNumberClass right)
{
	bool greater;
	BigNumbersNamespace::BigNumberClass result;
	//answer will be negative if both numbers are negative
	if (negativeNumber == right.negativeNumber)
	{
		result.negativeNumber = negativeNumber;
		addHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
	}
	else
	{
		//logic for order of numbers
		greater = greaterThan(bigNumberDigits, right.bigNumberDigits);
		if (greater) subtractHelper(bigNumberDigits, right.bigNumberDigits, result.bigNumberDigits);
		else subtractHelper(right.bigNumberDigits, bigNumberDigits, result.bigNumberDigits);
		//logic for sign of number
		result.negativeNumber = false;
		if (greater&&negativeNumber) result.negativeNumber = true;
		if ((!greater) && (!negativeNumber)) result.negativeNumber = true;
	}
	while (result.bigNumberDigits[0] == 0) result.bigNumberDigits.erase(result.bigNumberDigits.begin());
	return result;
}
