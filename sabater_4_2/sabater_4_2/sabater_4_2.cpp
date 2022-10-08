#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define PHILHEALTH 1000.00;
#define PAG_IBIG 800.00;
#define SSS 1200.00;

int main()
{
    // Inititiate needed values
    float philhealth = PHILHEALTH;
    float pagibig = PAG_IBIG;
    float sss = SSS;

    // Employee Information
    string payroll_date = "";
    int employee_id = 0;
    string employee_name = "";          
    float monthly_salary = 0;
    float lates_absences = 0; // in minutes

    // Ask the use to input employee information
    cout << "Input the following information." << endl;
    cout << "Payroll Period: ";
    getline(cin >> ws, payroll_date);
    cout << "Employee ID: ";
    cin >> employee_id;
    cout << "Employee Name: ";
    getline(cin >> ws, employee_name);
    cout << "Monthly Salary: ";
    cin >> monthly_salary;
    cout << "Lates and Absences: ";
    cin >> lates_absences;

    // Calculate late and absences, hourly rate, tax, total deductions
    lates_absences = lates_absences / 60; // convert from minutes to hours
    lates_absences = (monthly_salary / 30 / 8) * lates_absences; // Compute total deduction via absences
    float hourly_rate = (monthly_salary / 30) / 8;
    float tax = monthly_salary * (float)0.12;
    float deductions = lates_absences + philhealth + pagibig + sss + tax;

    // Set decimal point values
    cout << fixed << showpoint;
    cout << setprecision(2);

    // Output the result
    cout << endl;
    cout << "Displaying Payslip..." << endl;
    cout << endl;
    cout << string(4, '\t') << "FEU - Institute of Technology" << endl;
    cout << "Employee ID: " << employee_id;
    cout << string(4, '\t') << string(5, ' ') << "Payroll Period: " << payroll_date << endl;
    cout << "Employee Name: " << employee_name << string(1, '\t') << endl << endl;
    cout << "INCOME" << string(3, '\t');
    cout << string(3, '\t') << string(5, ' ') << "DEDUCTIONS" << endl;
    cout << "Monthly Salary Php" << monthly_salary << "\t";
    cout << string(2, '\t') << string(5, ' ') << "Lates and absences" << string(1, '\t') << "(" << lates_absences << ")" << endl;
    cout << string(6, '\t') << string(5, ' ') << "Philhealth" << string(2, '\t') << "(" << philhealth << ")" << endl;
    cout << string(6, '\t') << string(5, ' ') << "Pag-ibig" << string(2, '\t') << "(" << pagibig << ")" << endl;
    cout << string(6, '\t') << string(5, ' ') << "SSS" << string(2, '\t') << "(" << sss << ")" << endl;
    cout << string(6, '\t') << string(5, ' ') << "Withholding tax: " << string(1, '\t') << "(" << tax << ")" << endl;
    cout << "Total Earnings: " << "Php" << monthly_salary << endl;
    cout << "Total Deductions: " << "Php" << deductions << endl;
    cout << "Net Pay: " << monthly_salary - deductions << endl;

    return 0;
}
