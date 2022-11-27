#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

#define CURRENCY "Php "

/**
 * A class that represents an expense.
 *
 * @param description The description of the expense.
 * @param amount The amount of the expense.
 * @param month The month of the expense.
 * @param day The day of the expense.
 * @param year The year of the expense.
 *
 * @returns None
 */
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

/**
 * A class that represents a department project.
 *
 * @param project_name The name of the project.
 * @param alloted_budget The budget allocated to the project.
 * @param ExpenseVector The vector of expenses.
 */
class DepartmentProject {
public:
    string project_name;
    float alloted_budget;
    vector<ExpenseClass*> ExpenseVector;

    float current_balance();
};

/**
 * A class that represents a DepartmentAccount.
 *
 * @param email The email address of the DepartmentAccount.
 * @param password The password of the DepartmentAccount.
 * @param DepartmentProjectVector The vector of DepartmentProjects.
 */
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

/**
 * The main menu of the program.
 *
 * @param DepartmentAccountClass The list of DepartmentAccountClass objects.
 *
 * @returns None
 */
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

/**
 * Displays the login menu and processes the user's input.
 *
 * @param DepartmentAccountVector A vector of DepartmentAccountClass objects.
 *
 * @returns None
 */
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

/**
 * Sign up menu for the business department.
 *
 * @param DepartmentAccountVector The vector of business department accounts.
 *
 * @returns None
 */
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
        std::cerr << "\t�Must contain at least 1 lowercase letter.\n";
        std::cerr << "\t�Must contain at least 1 uppercase letter.\n";
        std::cerr << "\t�Must contain at least 1 number.\n";
        std::cerr << "\t�Must contain at least 1 of the following symbols (~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/).\n";
        std::cerr << "\t�Must contain at least 8 characters.\n" << std::flush;
        return;
    }

    DepartmentAccountVector.push_back(new_department);
    std::cout << "\nYour business department account has been created...\n";

    return;
}

/**
 * Displays the project menu.
 *
 * @param department The department account class.
 * @param DepartmentAccountVector The vector of department account classes.
 *
 * @returns None
 */
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

/**
 * Displays the expense menu.
 *
 * @param index The index of the project in the vector.
 * @param departmentProject The project to display.
 * @param department_ProjectVector The vector of projects.
 *
 * @returns None
 */
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

/**
 * Selects the account for the department.
 *
 * @param department The department to select the account for.
 * @param DepartmentAccountVector The vector of department accounts.
 *
 * @returns The index of the account in the vector.
 */
int selectAccount(DepartmentAccountClass*& department, std::vector<DepartmentAccountClass*>& DepartmentAccountVector) {
    for (int i = 0; i < DepartmentAccountVector.size(); i++) {
        if (DepartmentAccountVector[i]->email == department->email) {
            return i + 1;
        }
    }

    return 0;
}

/**
 * Checks if a username already exists.
 *
 * @param new_department The new department to be added.
 * @param DepartmentAccountVector The vector of department accounts.
 *
 * @returns True if the username already exists, false otherwise.
 */
bool isUsernameExists(std::string new_department, std::vector<DepartmentAccountClass*> DepartmentAccountVector) {
    for (auto& account : DepartmentAccountVector) {
        if (new_department == account->email) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if a password is valid.
 *
 * @param password The password to check.
 *
 * @returns True if the password is valid, false otherwise.
 */
bool isValidPassword(std::string password) {
    bool containsSymbol = false;
    bool containsNumber = false;
    bool containsLowercase = false;
    bool containsUppercase = false;

    std::string validSymbols = R"()~`!@#$%^&*()_-+={[}]|\:;"'<,>.?/)";

    /**
	 * Check if the password contains at least 1 lowercase letter.
	 * Check if the password contains at least 1 uppercase letter.
	 * Check if the password contains at least 1 number.
	 * Check if the password contains at least 1 of the following symbols (~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/).
	 * Check if the password contains at least 8 characters.
	 */
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

/**
 * Adds a new project to the department.
 *
 * @param department_ProjectVector The vector of projects in the department.
 *
 * @returns None
 */
void addProject(vector<DepartmentProject*>& department_ProjectVector) {
    system("CLS");

    DepartmentProject* placeholder = new DepartmentProject();

    cout << "ADD PROJECT\n\n";
    cout << "Project Name: ";
    getline(cin >> ws, placeholder->project_name);
    cout << "Allotted Budget: " << CURRENCY;
    cin >> placeholder->alloted_budget;

    /**
     * Check if project name already exists.
     */
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

/**
 * Displays the selected project details.
 *
 * @param department_ProjectVector The vector of department projects.
 *
 * @returns None
 */
int displaySelectProject(vector<DepartmentProject*>& department_ProjectVector) {
    system("CLS");

    int n = 0, selected_project = 0;

    cout << "YOUR PROJECTS\n\n";

    /**
	 * Displays the projects in the department account.
     */
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

/**
 * Adds an expense to the department's expense vector.
 *
 * @param department_ExpenseVector The department's expense vector.
 *
 * @returns None
 */
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


/**
 * Displays all the expenses in the department.
 *
 * @param department_ExpenseVector The vector of expenses in the department.
 *
 * @returns None
 */
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


/**
 * Displays the filtered expenses for a department.
 *
 * @param department_ExpenseVector The vector of expenses for a department.
 *
 * @returns None
 */
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

    /**
	 * This is a lambda function that checks if the date is within the range.
	 */
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

/**
 * Checks if an expense is in a given date range.
 *
 * @param expense The expense to check.
 * @param starting_month The starting month of the date range.
 * @param starting_day The starting day of the date range.
 * @param starting_year The starting year of the date range.
 * @param end_month The ending month of the date range.
 * @param end_day The ending day of the date range.
 * @param end_year The ending year of the date range.
 *
 * @returns True if the expense is in the date range, false otherwise.
 */
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

/**
 * Renames a project in a department.
 *
 * @param departmentProject The project to rename.
 * @param department_ProjectVector The vector of all projects in the department.
 *
 * @returns None
 */
void renameProject(DepartmentProject*& departmentProject, vector<DepartmentProject*> department_ProjectVector) {
    system("CLS");

    string new_project_name;

    cout << "RENAME PROJECT\n\n";
    cout << "New Project Name: ";
    getline(cin >> ws, new_project_name);

    /**
	 * Check if the new project name is already taken.
	 */
    for (auto project : department_ProjectVector) {
        if (new_project_name == project->project_name) {
            cerr << "\nError... Project name already exists!\n";
            return;
        }
    }

    /**
	 * Rename the project.
	 */
    departmentProject->project_name = new_project_name;
    cout << "\nProject renamed successfully!\n";

    return;
}

/**
 * Pauses the program until the user presses a key.
 *
 * @returns None
 */
void pause() {
    cout << "\nPress any key to continue..." << flush;
    _getch();
    return;
}

/**
 * Gets the day of the month.
 *
 * @param day The day of the month.
 *
 * @returns None
 */
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

/**
 * Gets the month from the user.
 *
 * @param month The month to be returned.
 *
 * @returns None
 */
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

/**
 * Gets the year of the expense.
 *
 * @param year The year of the expense.
 *
 * @returns None
 */
void ExpenseClass::get_year(int& year) {
    cout << "Year: ";
    cin >> year;

    return;
}

/**
 * Gets the description of the expense.
 *
 * @param description The description of the expense.
 *
 * @returns None
 */
float DepartmentProject::current_balance() {
    float expense_sum = 0;
	
    /**
	 * Loops through the vector of expenses and adds the amount of each expense to the expense_sum.
     */
    for (auto expense : ExpenseVector) {
        expense_sum += expense->amount;
    }
    return alloted_budget - expense_sum;
}
