#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>

void is_valid_input_figure(std::string figure);
void is_valid_input_num(std::string num);

int main()
{
    std::string figure = "\n";
    double volume = 0;

    std::cout << "Volume of Figures\n";
    std::cout << "[C] - Cube\n";
    std::cout << "[R] - Rectangular Prism\n";
    std::cout << "[S] - Sphere\n";

    std::cout << "\nChoose figure: ";
    getline(std::cin >> std::ws, figure);
    is_valid_input_figure(figure);

    // Get input for chosen figure 
    // Don't accept invalid figure
    // Compute the volume using the given parameter and ouputs it
    switch (figure[0]){
        // For Cube
        case 'C':
        case 'c': {
            std::string side = "\n";

            std::cout << "\nYou have chosen Cube.\n";

            std::cout << "Enter side: ";
            getline(std::cin >> std::ws, side);
            is_valid_input_num(side);

            volume = pow(stod(side), 3);

            printf("The volume of the Cube is: %.2f\n", volume);

            break;
        }
        // For Rectangular Prism
        case 'R':
        case 'r': {
            std::string length = "\n", width = "\n", height = "\n";

            std::cout << "\nYou have chosen Rectangular Prism.\n";

            std::cout << "Enter length: ";
            getline(std::cin >> std::ws, length);
            is_valid_input_num(length);

            std::cout << "Enter width: ";
            getline(std::cin >> std::ws, width);
            is_valid_input_num(width);

            std::cout << "Enter height: ";
            getline(std::cin >> std::ws, height);
            is_valid_input_num(height);

            volume = stod(length) * stod(width) * stod(height);

            printf("The volume of the Rectangular Prism is: %.2f\n", volume);

            break;
        }
        // For Sphere
        case 'S':
        case 's': {
            std::string radius = "\n";
            std::cout << "\nYou have chosen Sphere.\n";

            std::cout << "Enter radius: ";
            getline(std::cin >> std::ws, radius);
            is_valid_input_num(radius);

            volume = (4.0 / 3.0) * M_PI * pow(stod(radius), 3);

            printf("The volume of the Sphere is: %.2f\n", volume);

            break;
        }
        // If not a valid figure
        default:
            std::cout << "INVALID INPUT...";
            exit(1);
    }
    return 0;
}

// Validates input value for figure
void is_valid_input_figure(std::string figure) {
    
    // Check if input contains one character
    if (figure.length() != 1) {
        std::cout << "INVALID INPUT..." << std::endl;
        exit(2);
    }
    return;
}

// Validates input value aka volume parameters
void is_valid_input_num(std::string num) {

    bool decimal_point_exist = false;

    // Loops through the string
    // Access all individual characters
    for (int i = 0; i < num.length(); i++) {

        // Check if character is a digit
        // If not digit, it is considered an invalid input (Exception: decimal point)
        if (isdigit(num[i])) {
            continue;
        }
        else {
            if (num[i] == '.') {

                // Note: Accept decimal point as long as only one exists
                // If decimal point occurs more than once, it is considered an invalid input
                if (decimal_point_exist) {
                    std::cout << "INVALID INPUT..." << std::endl;
                    exit(3);
                }
                else {
                    decimal_point_exist = true;
                    continue;
                }
            }
            else {
                std::cout << "INVALID INPUT..." << std::endl;
                exit(4);
            }
        }
    }
    return;
}