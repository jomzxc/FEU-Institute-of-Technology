#include <iostream>
#include <numeric>
#include <iomanip>

using namespace std;

int main()
{
    float grade[] = { 0, 0, 0 };
    string emoji = "\n";

    cout << "INPUT 3 EXAM GRADES" << endl;
    for (int i = 0; i < (sizeof(grade) / sizeof(grade[0])); i++) {
        cout << "EXAM " << i + 1 << ": ";
        cin >> grade[i];
    }

    float sum = (accumulate(begin(grade), end(grade), float()));
    float average = sum / ((float)sizeof(grade) / (float)sizeof(grade[0]));
    
    if (average >= 70) {
        emoji = " :-)";
    }
    else {
        emoji = " :-(";
    }

    cout << fixed << setprecision(2);
    cout << "YOUR AVERAGE GRADE IS " << average << emoji << endl;

    return 0;
}