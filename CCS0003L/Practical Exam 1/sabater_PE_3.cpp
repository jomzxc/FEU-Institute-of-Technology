#include <iostream>

using namespace std;

int main()
{
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    float slope = 0, intercept = 0;
    
    cout << "Program to find the equation of a line given two endpoints:" << endl;
    cout << "Enter X1: ";
    cin >> x1;
    cout << "Enter Y1: ";
    cin >> y1;
    cout << "Enter X2: " ;
    cin >> x2;
    cout << "Enter Y2: ";
    cin >> y2;

    slope = (y2 - y1) / (x2 - x1);
    intercept = y2 - slope * x2;


    printf("Equation of the line with endpoints (%.5g, %.5g) and (%.5g, %.5g) : Y = %.5fX +%.5f\n", x1, y1, x2, y2, slope, intercept);

    return 0;
}