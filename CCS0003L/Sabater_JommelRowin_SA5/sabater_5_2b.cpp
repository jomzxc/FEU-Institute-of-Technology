#include <iostream>
#include <string>

using namespace std;

string get_horoscope(int month, int day);
void is_valid_input(int placeholder, int day);

int main()
{

    string month[] = { "January", "February", "March", "April", "May", "June", "July",
                      "August", "September", "October", "November", "December" };
    int day;
    int placeholder;

    cout << "Enter month: ";
    cin >> placeholder;

    cout << "Enter day: ";
    cin >> day;

    is_valid_input(placeholder, day);

    string zodiac = get_horoscope(placeholder, day);

    cout << "Zodiac sign for "<< month[placeholder - 1] << " " << day << " is " << zodiac << endl;

    return 0;
}

void is_valid_input(int placeholder, int day) {

    if (!(placeholder >= 1 && placeholder <= 12) || !(day >= 1 || day <= 31)) {

        cout << "INVALID INPUT" << endl;
        exit(1);
    }
}

string get_horoscope(int month, int day) {

    switch (month) {
        case 1:
            return ((day <= 19) ? "Caapricorn" : "Aquarius");
        case 2:
            return ((day <= 18) ? "Aquarius" : "Pisces");
        case 3:
            return ((day <= 20) ? "Pisces" : "Aries");
        case 4:
            return ((day <= 19) ? "Aries" : "Taurus");
        case 5:
            return ((day <= 20) ? "Taurus" : "Gemini");
        case 6:
            return ((day <= 20) ? "Gemini" : "Cancer");
        case 7:
            return ((day <= 22) ? "Cancer" : "Leo");
        case 8:
            return ((day <= 22) ? "Leo" : "Virgo");
        case 9:
            return ((day <= 22) ? "Virgo" : "Libra");
        case 10:
            return ((day <= 22) ? "Libra" : "Scorpio");
        case 11:
            return ((day <= 21) ? "Scorpio" : "Sagittarius");
        case 12:
            return ((day <= 21) ? "Sagittarius" : "Capricorn");
        default:
            cout << "INVALID INPUT" << endl;
            exit(2);
    }
}