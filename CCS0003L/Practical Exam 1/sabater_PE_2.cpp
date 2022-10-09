#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

int main()
{
	double first_side = 0, second_side = 0, third_side = 0;
	long double s = 0, area = 0;

	cout << "Find the area of any triangle using Heron's Formula :" << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Input the length of the sides of the triangle:" << endl;
	cout << "Enter first side: ";
	cin >> first_side;
	cout << "Enter second side: ";
	cin >> second_side;
	cout << "Enter third side: ";
	cin >> third_side;

	s = (first_side + second_side + third_side) / 2;
	area = sqrt(s * (s - first_side) * (s - second_side) * (s - third_side));

	cout << "The value of s is : " << ("%.4f", s) << endl;
	cout << ("The area of the triangle is : %.4f", area) << endl;

	return 0;
}
