#include <iostream>
#include <numeric>
#include <iomanip>

using namespace std;

int main()
{
    float grade[] = {0, 0, 0};

    cout << "INPUT 3 EXAM GRADES: " << endl;
    for (int i = 0; i < (sizeof(grade) / sizeof(grade[0])); i++) {
        cout << "EXAM" << i << ": ";
        cin >> grade[i];
    }

    float sum = (accumulate(begin(grade), end(grade), float()));
    float average = sum / (sizeof(grade) / sizeof(grade[0]));

    cout << fixed;
    cout << setprecision(2);
    cout << "YOUR AVERAGE GRADE IS " << average << ((sum >= 70) ? " :-)" : " :-(");

    return 0;
}