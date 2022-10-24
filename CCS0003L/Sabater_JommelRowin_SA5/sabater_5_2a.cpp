#include <iostream>
#include <string>
#include <iomanip>

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

    cout << "Zodiac sign for " << month[placeholder - 1] << " " << day << " is " << zodiac << endl;

    return 0;
}

void is_valid_input(int placeholder, int day) {

    if ((placeholder >= 1 && placeholder <= 12) && (day >= 1 && day <= 31)) {
        return;
    }
    else {
        cout << "INVALID INPUT...";
        exit(1);
    }
}

string get_horoscope(int month, int day) {

    if (month == 1) {
        return ((day <= 19) ? "Capricorn" : "Aquarius");
    }
    else if (month == 2) {
        return ((day <= 18) ? "Aquarius" : "Pisces");
    }
    else if (month == 3) {
        return ((day <= 20) ? "Pisces" : "Aries");
    }
    else if (month == 4) {
        return ((day <= 19) ? "Aries" : "Taurus");
    }
    else if (month == 5) {
        return ((day <= 20) ? "Taurus" : "Gemini");
    }
    else if (month == 6) {
        return ((day <= 20) ? "Gemini" : "Cancer");
    }
    else if (month == 7) {
        return ((day <= 22) ? "Cancer" : "Leo");
    }
    else if (month == 8) {
        return ((day <= 22) ? "Leo" : "Virgo");
    }
    else if (month == 9) {
        return ((day <= 22) ? "Virgo" : "Libra");
    }
    else if (month == 10) {
        return ((day <= 22) ? "Libra" : "Scorpio");
    }
    else if (month == 11) {
        return ((day <= 21) ? "Scorpio" : "Sagittarius");
    }
    else if (month == 12) {
        return ((day <= 21) ? "Sagittarius" : "Capricorn");
    }
    else {
        cout << "INVALID INPUT...";
        exit(2);
    }
}
