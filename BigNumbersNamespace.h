#pragma once
#include <vector>
#include <string>

namespace BigNumbersNamespace
{
	class BigNumberClass
	{
	private:
		std::vector <int> bigNumberDigits;
		bool negativeNumber;
		bool greaterThan(std::vector <int> vector1, std::vector <int> vector2);
		bool lessThan(std::vector<int> vector1, std::vector<int> vector2);
		void flipVector(std::vector <int> vectorToFlip);
		void addHelper(std::vector <int> vector1, std::vector <int> vector2, std::vector <int> vector3);
		void subtractHelper(std::vector <int> vector1, std::vector <int> vector2, std::vector <int> vector3);
	public:
		//constructors
		BigNumberClass();
		BigNumberClass(std::string val);
		//operation overloading
		BigNumberClass operator +(BigNumberClass right);
		BigNumberClass operator -(BigNumberClass right);
		BigNumberClass operator *(BigNumberClass right);
		BigNumberClass operator /(BigNumberClass right);
		BigNumberClass operator %(BigNumberClass right);
		//exceptions
		class NumberOverflowException {};
		class DividingByZeroException {};
		class ModulusByZeroException {};
	};
}
