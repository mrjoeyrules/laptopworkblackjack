#include "CustomMath.h"
using namespace std;
int CustomMath::countDigit(int number) // function to count how many digits are in a number.
{
	int count = 0;
	while (number != 0)
	{
		number = number / 10;
		count++;
	}
	return count;
}