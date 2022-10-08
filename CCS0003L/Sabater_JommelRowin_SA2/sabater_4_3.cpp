#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
using namespace std;

#define PI (float)3.14159
int main()
{
    // Initialize values
    float side_a = 0, side_b = 0, side_c = 0;
    float angle_c = 0;

    // Ask the user for 3 input value
    // Side a, side b, and angle c
    cout << "Enter the value of the following." << endl;
    cout << "Side A: ";
    cin >> side_a;
    cout << "Side B: ";
    cin >> side_b;
    cout << "Angle C: ";
    cin >> angle_c;

    // Convert degree to radian value
    angle_c *= PI / 180;
    // Calculate value of side c
    side_c = sqrt(pow(side_a, 2) + pow(side_b, 2) - (2 * side_a * side_b) * cos(angle_c));

    // Display the value of side c
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "The Value of Side C is " << side_c << endl;

    return 0;
}

