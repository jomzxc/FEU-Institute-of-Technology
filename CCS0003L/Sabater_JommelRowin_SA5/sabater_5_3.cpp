#include <iostream>
#include <string>
#include <stdio.h>
#include <iomanip>

void is_valid_input(std::string monthly_sales);
double compute_income(double monthly_sales);


int main() {
    
    std::string monthly_sales = "\n";
    double income = 0;

    std::cout << "ENTER MONTHLY SALES: $";
    getline(std::cin >> std::ws, monthly_sales);

    is_valid_input(monthly_sales);

    // Ouput income value in 2 decimal places
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "YOUR INCOME : $" << compute_income(stod(monthly_sales)) << std::endl;
    
    return 0;
}

// Validates input value
void is_valid_input(std::string monthly_sales) {
    
    bool decimal_point_exist = false;

    // Loops through the string
    // Access all individual characters
    for (int i = 0; i < monthly_sales.length(); i++) {

        // Check if character is a digit
        // If not digit, it is considered an invalid input (Exception: decimal point)
        if (isdigit(monthly_sales.at(i))) {
            continue;
        }
        else {
            if (monthly_sales.at(i) == '.') {

                // Note: Accept decimal point as long as only one exists
                // If decimal point occurs more than once, it is considered an invalid input
                if (decimal_point_exist) {
                    std::cout << "INVALID INPUT..." << std::endl;
                    exit(1);
                }
                else {
                    decimal_point_exist = true;
                    continue;
                }
            }
            else {
                std::cout << "INVALID INPUT..." << std::endl;
                exit(2);
            }
        }
    }
    return;
}

// Computes income
double compute_income(double monthly_sales) {
    if (monthly_sales >= 50000) {
        return 575 + (0.16 * monthly_sales);
    }
    else if (monthly_sales >= 40000 && monthly_sales <= 50000) {
        return 550 + (0.14 * monthly_sales);
    }
    else if (monthly_sales >= 30000 && monthly_sales <= 40000) {
        return 525 + (0.12 * monthly_sales);
    }
    else if (monthly_sales >= 20000 && monthly_sales <= 30000) {
        return 500 + (0.09 * monthly_sales);
    }
    else if (monthly_sales >= 10000 && monthly_sales <= 20000) {
        return 450 + (0.05 * monthly_sales);
    }
    else {
        return 400 + (0.03 * monthly_sales);
    }
}

