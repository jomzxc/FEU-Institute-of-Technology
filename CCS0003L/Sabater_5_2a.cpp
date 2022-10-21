#include <iostream>
#include <string>

using namespace std;

string get_horoscope(int month, int day);
void is_valid_input(int placeholder, int day);

int main()
{

    string month[] = {"January", "February", "March", "April", "May", "June", "July", 
                      "August", "September", "October", "November", "December"};
    int day;
    int placeholder;

    cout << "Enter month: ";
    cin >> placeholder;

    cout << "Enter day: ";
    cin >> day;

    is_valid_input(placeholder, day);

    string zodiac = get_horoscope(placeholder, day);

    cout << ("Zodiac sign for %s %d is %s", month[placeholder - 1], day, zodiac) << endl;
    
    return 0;
}

void is_valid_input(int placeholder, int day) {

    if (!(placeholder >= 1 || placeholder <= 12) || !(day >= 1 || day <= 31)) {

        exit(1);
    }
}

string get_horoscope(int month, int day) {
    
    if (month == 1) {
        if (day <= 19) {
            return "Capricorn";
        }
        else {
            return "Aquarius";
        }
    }
    else if (month == 2) {
        if (day <= 18) {
            return "Aquarius";
        }
        else {
            return "Pisces";
        }
    }
    else if (month == 3) {
        if (day <= 20) {
            return "Pisces";
        }
        else {
            return "Aries";
        }
    }
    else if (month == 4) {
        if (day <= 19) {
            return "Aries";
        }
        else {
            return "Taurus";
        }
    }
    else if (month == 5) {
        if (day <= 20) {
            return "Taurus";
        }
        else {
            return "Gemini";
        }
    }
    else if (month == 6) {
        if (day <= 20) {
            return "Gemini";
        }
        else {
            return "Cancer";
        }
    }
    else if (month == 7) {
        if (day <= 22) {
            return "Cancer";
        }
        else {
            return "Leo";
        }
    }
    else if (month == 8) {
        if (day <= 22) {
            return "Leo";
        }
        else {
            return "Virgo";
        }
    }
    else if (month == 9) {
        if (day <= 22) {
            return "Virgo";
        }
        else {
            return "Libra";
        }
    }
    else if (month == 10) {
        if (day <= 22) {
            return "Libra";
        }
        else {
            return "Scorpio";
        }
    }
    else if (month == 11) {
        if (day <= 21) {
            return "Scorpio";
        }
        else {
            return "Sagittarius";
        }
    }
    else if (month == 12) {
        if (day <= 21) {
            return "Sagittarius";
        }
        else {
            return "Capricorn";
        }
    }
    else {
        cout << "INVALID INPUT";
        exit(2);
    }
}