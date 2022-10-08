#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    // Initialize variables
    float a = 0, b = 0, hyp = 0;

    // Ask user for 2 inputs of for side a and b
    cout << "Enter the value of the following:" << endl;
    cout << "Side A: ";
    cin >> a;
    cout << "Side B: ";
    cin >> b;;

    // Compute the size of hypotenuse
    hyp = sqrt(pow(a, 2) + pow(b, 2));

    // Output result
    cout << fixed << showpoint;
    cout << setprecision(2);
    cout << "Hypotenuse: " << hyp << endl;

    return 0;
}




