#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define CURRENCY "Php "

class ExpenseClass {
public:
    string description;
    float amount;
    int month;
    int day;
    int year;

    void get_day(int& day);
    void get_month(int& month);
    void get_year(int& year);
};

class DepartmentProject {
public:
    string project_name;
    float alloted_budget;
    vector<ExpenseClass*> ExpenseVector;

    float current_balance();
};

class DepartmentAccountClass {
public:
    string email;
    string password;
    vector<DepartmentProject*> DepartmentProjectVector;
};

void loginMenu(vector<DepartmentAccountClass*>& DepartmentAccountVector);
void signUpMenu(vector<DepartmentAccountClass*>& DepartmentAccountVector);
void projectMenu(DepartmentAccountClass*& department, std::vector<DepartmentAccountClass*>& DepartmentAccountVector);
void expenseMenu(int index, DepartmentProject*& departmentProject, vector<DepartmentProject*> department_ProjectVector);

int selectAccount(DepartmentAccountClass*& department, std::vector<DepartmentAccountClass*>& DepartmentAccountVector);

bool isUsernameExists(string new_department, vector<DepartmentAccountClass*> DepartmentAccountVector);
bool isValidPassword(string password);

void addProject(vector<DepartmentProject*>& department_ProjectVector);
int displaySelectProject(vector<DepartmentProject*>& department_ProjectVector);

void addExpense(vector<ExpenseClass*>& department_ExpenseVector);
void displayAllExpense(vector<ExpenseClass*> department_ExpenseVector);
void displayFilteredExpense(vector<ExpenseClass*>& department_ExpenseVector);
bool isInDateRange(ExpenseClass* expense, int starting_month, int starting_day, int starting_year, int end_month, int end_day, int end_year);
void renameProject(DepartmentProject*& departmentProject, vector<DepartmentProject*> department_ProjectVector);


void pause();

int main()
{
    vector<DepartmentAccountClass*> DepartmentAccountClass; // Vector of DepartmentAccountClass

    while (true) {
        system("CLS");
        cout << "WELCOME TO XYZ PROJECT EXPENSE TRACKER\n\n";
        cout << "Press the number of the action you want to do.\n\n";
        cout << "[1] Login.\n";
        cout << "[2] Sign up.\n";
        cout << "[3] Exit.\n\n";

        char action = _getch();

        switch (action) {
        case '1':
            loginMenu(DepartmentAccountClass);
            pause();
            break;
        case '2':
            signUpMenu(DepartmentAccountClass);
            pause();
            break;
        case '3':
            cout << "Thank you for using XYZ Project Expense Tracker!\n";
            exit(EXIT_SUCCESS);
        default:
            cerr << "Error... Invalid Action. Try Again!\n" << flush;
            pause();
            break;
        }
    }
}

void loginMenu(vector<DepartmentAccountClass*>& DepartmentAccountVector) {
    system("CLS");

    DepartmentAccountClass* department = new DepartmentAccountClass();

    cout << "LOG IN\n\n";
    cout << "Email: ";
    cin >> department->email;
    cout << "Password: ";
    cin >> department->password;

    int index = selectAccount(department, DepartmentAccountVector);
    if (!index) {
        std::cerr << "\nError... Invalid email or password!\n" << std::flush;
        return;
    }

    std::cout << "\nLogging in...\n";
    pause();

    projectMenu(DepartmentAccountVector[index - 1], DepartmentAccountVector);

    return;
}

void signUpMenu(vector<DepartmentAccountClass*>& DepartmentAccountVector) {
    system("CLS");

    DepartmentAccountClass* new_department = new DepartmentAccountClass();

    std::string confirm_password = "\n";

    cout << "SIGN IN\n\n";
    cout << "EMAIL: ";
    cin >> new_department->email;
    cout << "Password: ";
    cin >> new_department->password;
    cout << "Confirm Password: ";
    cin >> confirm_password;

    if (new_department->password != confirm_password) {
        cerr << "\nError...Password does not match!\n" << flush;
        return;
    }
    if (isUsernameExists(new_department->email, DepartmentAccountVector)) {
        cerr << "\nError... Business department account already Exists!\n" << flush;
        return;
    }
    if (!isValidPassword(new_department->password)) {
        std::cerr << "\nError... Invalid Password.\n";
        std::cerr << "Password Requirements:\n";
        std::cerr << "\t•Must contain at least 1 lowercase letter.\n";
        std::cerr << "\t•Must contain at least 1 uppercase letter.\n";
        std::cerr << "\t•Must contain at least 1 number.\n";
        std::cerr << "\t•Must contain at least 1 of the following symbols (~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/).\n";
        std::cerr << "\t•Must contain at least 8 characters.\n" << std::flush;
        return;
    }

    DepartmentAccountVector.push_back(new_department);
    std::cout << "\nYour business department account has been created...\n";

    return;
}

void projectMenu(DepartmentAccountClass*& department, std::vector<DepartmentAccountClass*>& DepartmentAccountVector) {
    while (true) {
        system("CLS");

        std::cout << "WELCOME TO XYZ PROJECT EXPENSE TRACKER\n\n";
        std::cout << "Press the number of the action you want to do.\n\n";
        std::cout << "[1] Open a project\n";
        std::cout << "[2] Add a project\n";
        std::cout << "[3] Sign out\n";
        std::cout << "[4] Exit\n\n";

        char action = _getch();

        switch (action) {
        case '1': {
            int index = displaySelectProject(department->DepartmentProjectVector);
            if (index) {
                expenseMenu(index, department->DepartmentProjectVector[index - 1], department->DepartmentProjectVector);
            }
            pause();
            break;
        }
        case '2':
            addProject(department->DepartmentProjectVector);
            pause();
            break;
        case '3':
            cout << "Signing out...\n";
            return;
        case '4':
            cout << "Thank you for using XYZ Project Expense Tracker!\n";
            exit(EXIT_SUCCESS);
        default:
            cerr << "Error... Invalid Action. Try Again!\n" << flush;
            pause();
            break;
        }
    }
}

void expenseMenu(int index, DepartmentProject*& departmentProject, vector<DepartmentProject*> department_ProjectVector) {
    while (true) {
        system("CLS");

        cout << "Project: " << departmentProject->project_name << "\n";
        cout << "Remaining Project Balance: " << CURRENCY << fixed << setprecision(2) << departmentProject->current_balance() << "\n\n";
        cout << "Press the number of the action you want to do.\n\n";
        cout << "[1] Add Expense\n";
        cout << "[2] Display All Expense\n";
        cout << "[3] Display Filtered Expense\n";
        cout << "[4] Edit Allotted Budget\n";
        cout << "[5] Rename\n";
        cout << "[6] Go Back\n\n";

        char action = _getch();

        switch (action) {
        case '1':
            addExpense(departmentProject->ExpenseVector);
            pause();
            break;
        case '2':
            displayAllExpense(departmentProject->ExpenseVector);
            pause();
            break;
        case '3':
            displayFilteredExpense(departmentProject->ExpenseVector);
            pause();
            break;
        case '4':
            system("CLS");

            cout << "EDIT ALLOTED PROJECT BUDGET\n\n";
            cout << "New Alloted Budget:" << CURRENCY;
            cin >> departmentProject->alloted_budget;
            cout << "\nAlloted budget changed successfully!\n\n";
            pause();
            break;
        case '5':
            renameProject(departmentProject, department_ProjectVector);
            pause();
            break;
        case '6':
            return;
        }
    }
}

int selectAccount(DepartmentAccountClass*& department, std::vector<DepartmentAccountClass*>& DepartmentAccountVector) {
    for (int i = 0; i < DepartmentAccountVector.size(); i++) {
        if (DepartmentAccountVector[i]->email == department->email) {
            return i + 1;
        }
    }

    return 0;
}

bool isUsernameExists(std::string new_department, std::vector<DepartmentAccountClass*> DepartmentAccountVector) {
    for (auto& account : DepartmentAccountVector) {
        if (new_department == account->email) {
            return true;
        }
    }
    return false;
}

bool isValidPassword(std::string password) {
    bool containsSymbol = false;
    bool containsNumber = false;
    bool containsLowercase = false;
    bool containsUppercase = false;

    std::string validSymbols = R"()~`!@#$%^&*()_-+={[}]|\:;"'<,>.?/)";

    for (int i = 0; i < password.length(); i++) {
        if (password[i] >= 'a' && password[i] <= 'z')
            containsLowercase = true;
        else if (password[i] >= 'A' && password[i] <= 'Z')
            containsUppercase = true;
        else if (password[i] >= '0' && password[i] <= '9')
            containsNumber = true;
        else
            for (int j = 0; j < validSymbols.length(); j++) {
                if (password[i] == validSymbols[j]) {
                    containsSymbol = true;
                    break;
                }
            }
        if (containsSymbol && containsNumber && containsLowercase && containsUppercase && i >= 7)
            return true;
    }
    return false;
}

void addProject(vector<DepartmentProject*>& department_ProjectVector) {
    system("CLS");

    DepartmentProject* placeholder = new DepartmentProject();

    cout << "ADD PROJECT\n\n";
    cout << "Project Name: ";
    getline(cin >> ws, placeholder->project_name);
    cout << "Allotted Budget: " << CURRENCY;
    cin >> placeholder->alloted_budget;

    for (auto project : department_ProjectVector) {
        if (placeholder->project_name == project->project_name) {
            cerr << "\nError... Project already exists!\n" << flush;
            return;
        }
    }

    department_ProjectVector.push_back(placeholder);
    cout << "\nYour department project has been added...\n";

    return;
}

int displaySelectProject(vector<DepartmentProject*>& department_ProjectVector) {
    system("CLS");

    int n = 0, selected_project = 0;

    cout << "YOUR PROJECTS\n\n";

    for (auto project : department_ProjectVector) {
        cout << "[" << ++n << "] " << project->project_name << ".\n";
    }

    cout << "[0] Go back.\n\n";
    cout << "Enter the number of the project you want to open: ";
    cin >> selected_project;

    if (selected_project == 0) {
        cout << "\nGoing back...\n";
        return 0;
    }

    return selected_project;
}

void addExpense(vector<ExpenseClass*>& department_ExpenseVector) {
    system("CLS");

    ExpenseClass* placeholder = new ExpenseClass();

    cout << "ADD EXPENSE\n\n";
    cout << "Description: ";
    getline(cin >> ws, placeholder->description);
    cout << "Amount: " << CURRENCY;
    cin >> placeholder->amount;
    placeholder->get_month(placeholder->month);;
    placeholder->get_day(placeholder->day);
    placeholder->get_year(placeholder->year);

    department_ExpenseVector.push_back(placeholder);
    cout << "\nExpense added successfully!\n";

    return;
}


void displayAllExpense(vector<ExpenseClass*> department_ExpenseVector) {
    system("CLS");

    cout << "EXPENSES\n\n";

    cout << "Date (DD/MM/YYYY)\t" << left << setw(50) << "Expenses" << "Amount" << endl;

    for (auto expense : department_ExpenseVector) {
        cout << ((expense->day < 10) ? 0 : "") << expense->day << "/" << ((expense->month < 10) ? 0 : "") << expense->month << "/" << expense->year << "\t\t";
        cout << left << setw(50) << expense->description;
        cout << fixed << setprecision(2) << CURRENCY << expense->amount << endl;

    }

    cout << "\n";
    return;
}


void displayFilteredExpense(vector<ExpenseClass*>& department_ExpenseVector) {
    system("CLS");

    int starting_month, starting_day, starting_year;
    int end_month, end_day, end_year;

    cout << "FILTER BY DATE\n\n";

    cout << "Starting Date:\n";
    cout << "Month: ";
    cin >> starting_month;
    cout << "Day: ";
    cin >> starting_day;
    cout << "Year: ";
    cin >> starting_year;
    cout << "\n\n";

    cout << "End Date:\n";
    cout << "Month: ";
    cin >> end_month;
    cout << "Day: ";
    cin >> end_day;
    cout << "Year: ";
    cin >> end_year;
    cout << "\n\n";

    cout << "Date (DD/MM/YYYY)\t" << left << setw(50) << "Expenses" << "Amount" << endl;

    for (auto expense : department_ExpenseVector) {
        if (isInDateRange(expense, starting_month, starting_day, starting_year, end_month, end_day, end_year)) {

            cout << ((expense->day < 10) ? 0 : "") << expense->day << "/" << ((expense->month < 10) ? 0 : "") << expense->month << "/" << expense->year << "\t\t";
            cout << left << setw(50) << expense->description;
            cout << fixed << setprecision(2) << CURRENCY << expense->amount << endl;
        }
    }
    cout << "\n";
    return;
}

bool isInDateRange(ExpenseClass* expense, int starting_month, int starting_day, int starting_year, int end_month, int end_day, int end_year) {
    int entry_date = (expense->year * 10000) + (expense->month * 100) + expense->day;
    int start_date = (starting_year * 10000) + (starting_month * 100) + starting_day;
    int end_date = (end_year * 10000) + (end_month * 100) + end_day;
    
    if (entry_date >= start_date && entry_date <= end_date) {
        return true;
    }
    else {
        return false;
    }
}

void renameProject(DepartmentProject*& departmentProject, vector<DepartmentProject*> department_ProjectVector) {
    system("CLS");

    string new_project_name;

    cout << "RENAME PROJECT\n\n";
    cout << "New Project Name: ";
    getline(cin >> ws, new_project_name);

    for (auto project : department_ProjectVector) {
        if (new_project_name == project->project_name) {
            cerr << "\nError... Project name already exists!\n";
            return;
        }
    }

    departmentProject->project_name = new_project_name;
    cout << "\nProject renamed successfully!\n";

    return;
}

void pause() {
    cout << "\nPress any key to continue..." << flush;
    _getch();
    return;
}

void ExpenseClass::get_day(int& day) {
    while (true) {
        cout << "Day (01 - 31): ";
        cin >> day;

        if (day >= 1 && day <= 31) {
            break;
        }
        else {
            cout << "Error... Invalid Input.\n";
        }
    }
    return;
}

void ExpenseClass::get_month(int& month) {
    while (true) {
        month;

        cout << "Month (01 - 12): ";
        cin >> month;

        if (month >= 1 && month <= 12) {
            break;
        }
        else {
            cout << "Error... Invalid Input.\n";
        }
    }
    return;
}

void ExpenseClass::get_year(int& year) {
    cout << "Year: ";
    cin >> year;

    return;
}

float DepartmentProject::current_balance() {
    float expense_sum = 0;
    for (auto expense : ExpenseVector) {
        expense_sum += expense->amount;
    }
    return alloted_budget - expense_sum;
}
