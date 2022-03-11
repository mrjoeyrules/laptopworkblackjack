#include "CustomMath.h"
#include <string>
using namespace std;
int CustomMath::countDigit(int number)
{
	int count = 0;
	while (number != 0)
	{
		number = number / 10;
		count++;
	}
	return count;
}