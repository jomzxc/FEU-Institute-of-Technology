#include <cstdlib>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::cerr;
using std::cin;
using std::flush;
using std::ws;
using std::string;
using std::vector;

#define CURRENCY "Php "

class ExpenseClass {
public:
    string description;
    float amount;
};

class BudgetClass {
public:
    string budget_name;
    float budgeted_amount;
    vector<ExpenseClass*> ExpenseVector;
    float current_balance() {
        float expense_sum = 0;
        for (auto expense : ExpenseVector) {
            expense_sum += expense->amount;
        }
        return budgeted_amount - expense_sum;
    }

};

class AccountClass {
public:
    string username;
    string password;
    vector<BudgetClass*> BudgetVector;
};

void pause();

void signUpMenu(vector<AccountClass*>& AccountVector);
bool isUsernameExists(string new_user, vector<AccountClass*> AccountVector);
bool isValidPassword(string password);

void loginMenu(vector<AccountClass*>& AccountVector);
bool selectAccount(AccountClass*& user, std::vector<AccountClass*>& AccountVector);

void budgetMenu(AccountClass*& user, std::vector<AccountClass*>& AccountVector);
void addBudget(vector<BudgetClass*>& user_BudgetVector);
bool displaySelectBudget(vector<BudgetClass*>& user_BudgetVector);
void openBudget(int index, BudgetClass*& userBudget, vector<BudgetClass*> user_BudgetVector);

void expenseMenu(int index, BudgetClass*& userBudget, vector<BudgetClass*> user_BudgetVector);
void addExpense(vector<ExpenseClass*>& user_ExpenseVector);
void displayExpense(vector<ExpenseClass*> user_ExpenseVector);
void renameBudget(BudgetClass*& userBudget, vector<BudgetClass*> user_BudgetVector);


int main()
{
    vector<AccountClass*> AccountVector; // Vector of AccountClass

    while (true) { 
        system("CLS");
        cout << "WELCOME TO XYZ BUDGET PLANNER!\n\n";
        cout << "Press the number of the action you want to do.\n\n";
        cout << "[1] Login.\n";
        cout << "[2] Sign up.\n";
        cout << "[3] Exit.\n\n";

        char action = _getch();

        switch (action) {
        case '1':
            loginMenu(AccountVector);
            pause();
            break;
        case '2':
            signUpMenu(AccountVector);
            pause();
            break;
        case '3':

            cout << "Thank you for using XYZ Budget Planner!\n";
            exit(EXIT_SUCCESS);
        default:
            cerr << "Error... Invalid Action. Try Again!\n" << flush;
            pause();
            break;
        }
    }
}

void pause() {
    cout << "\nPress any key to continue..." << flush;
    _getch();
    return;
}

void signUpMenu(vector<AccountClass*>& AccountVector) {
    system("CLS");

    AccountClass* new_user = new AccountClass();

    std::string confirm_password = "\n";

    cout << "SIGN IN\n\n";
    cout << "Username: ";
    cin >> new_user->username;
    cout << "Password: ";
    cin >> new_user->password;
    cout << "Confirm Password: ";
    cin >> confirm_password;

    if (new_user->password != confirm_password) {
        cerr << "\nError...Password does not match!\n" << flush;
        return;
    }
    if (isUsernameExists(new_user->username, AccountVector)) {
        cerr << "\nError... Username already Exists!\n" << flush;
        return;
    }
    if (!isValidPassword(new_user->password)) {
        std::cerr << "\nError... Invalid Password.\n";
        std::cerr << "Password Requirements:\n";
        std::cerr << "\t•Must contain at least 1 lowercase letter.\n";
        std::cerr << "\t•Must contain at least 1 uppercase letter.\n";
        std::cerr << "\t•Must contain at least 1 number.\n";
        std::cerr << "\t•Must contain at least 1 of the following symbols (~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/).\n";
        std::cerr << "\t•Must contains at least 8 characters.\n" << std::flush;
        return;
    }

    AccountVector.push_back(new_user);
    std::cout << "\nYour account has been created...\n";

    return;
}

bool isUsernameExists(std::string new_user, std::vector<AccountClass*> AccountVector) {
    for (auto& account : AccountVector) {
        if (new_user == account->username) {
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

void loginMenu(vector<AccountClass*>& AccountVector) {
    system("CLS");

    AccountClass* user = new AccountClass();

    cout << "LOG IN\n\n";
    cout << "Username: ";
    cin >> user->username;
    cout << "Password: ";
    cin >> user->password;

    if (!selectAccount(user, AccountVector)) {
        std::cerr << "\nError... Invalid username or password!\n" << std::flush;
        return;
    }

    std::cout << "\nLogging in...\n";
    pause();

    budgetMenu(user, AccountVector);

    return;
}

bool selectAccount(AccountClass*& user, std::vector<AccountClass*>& AccountVector) {
    for (auto account : AccountVector) {
        if ((user->username == account->username) && (user->password == account->password)) {
            user->username = account->username;
            user->password = account->password;
            user->BudgetVector = account->BudgetVector;
            return true;
        }
    }
    return false;
}

void budgetMenu(AccountClass*& user, std::vector<AccountClass*>& AccountVector) {
    while (true) {
        system("CLS");

        std::cout << "WELCOME TO XYZ BUDGET PLANNER\n\n";
        std::cout << "Press the number of the action you want to do.\n\n";
        std::cout << "[1] Open a budget\n";
        std::cout << "[2] Add a budget\n";
        std::cout << "[3] Sign out\n";
        std::cout << "[4] Exit\n\n";

        char action = _getch();

        switch (action) {
        case '1': {
            int index = displaySelectBudget(user->BudgetVector);
            if (index) {
                expenseMenu(index, user->BudgetVector[index-1], user->BudgetVector);
            }
            pause();
            break;
        }
        case '2':
            addBudget(user->BudgetVector);
            pause();
            break;
        case '3':
            cout << "Signing out...\n";
            return;
        case '4':
        default:
            cerr << "Error... Invalid Action. Try Again!\n" << flush;
            pause();
            break;
        }
    }
}

void addBudget(vector<BudgetClass*>& user_BudgetVector) {
    system("CLS");

    BudgetClass* placeholder = new BudgetClass();

    cout << "ADD BUDGET\n\n";
    cout << "Budget Name: ";
    getline(cin >> ws, placeholder->budget_name);
    cout << "Budgeted Amount: ";
    cin >> placeholder->budgeted_amount;

    for (auto budget : user_BudgetVector) {
        if (placeholder->budget_name == budget->budget_name) {
            cerr << "\nError... Budget already exists!\n" << flush;
            return;
        }
    }

    user_BudgetVector.push_back(placeholder);
    cout << "\nYour budget has been added...\n";

    return;
}

bool displaySelectBudget(vector<BudgetClass*>& user_BudgetVector) {
    system("CLS");

    int n = 0, selected_budget = 0;

    cout << "YOUR BUDGETS\n\n";

    for (auto budget : user_BudgetVector) {
        cout << "[" << ++n << "] " << budget->budget_name << ".\n";
    }
    
    cout << "[0] Go back.\n\n";
    cout << "Enter the number of the budget you want to open: ";
    cin >> selected_budget;

    if (selected_budget == 0) {
        cout << "\nGoing back...\n";
        return false;
    }
    
    return selected_budget;
}

void expenseMenu(int index, BudgetClass*& userBudget, vector<BudgetClass*> user_BudgetVector) {
    while (true) {
        system("CLS");

        cout << "BUDGET: " << userBudget->budget_name << "\n";
        cout << "Remaining Balance: " << userBudget->current_balance() << "\n\n";
        cout << "Press the number of the action you want to do.\n\n";
        cout << "[1] Add Expense\n";
        cout << "[2] Open Expense\n";
        cout << "[3] Edit Budgeted Amount\n";
        cout << "[4] Rename\n";
        cout << "[5] Go Back\n\n";

        char action = _getch();

        switch (action) {
        case '1':
            addExpense(userBudget->ExpenseVector);
            pause();
            break;
        case '2':
            displayExpense(userBudget->ExpenseVector);
            pause();
            break;
        case '3':
            system("CLS");

            cout << "EDIT BUDGETED AMOUNT\n\n";
            cout << "New Budgeted Amount: ";
            cin >> userBudget->budgeted_amount;
            cout << "\nBudgeted amount changed successfully!\n\n";
            pause();
            break;
        case '4': {
            renameBudget(userBudget, user_BudgetVector);            
            pause();
            break;
        }
        case '5':
            return;
        }
    }
}

void addExpense(vector<ExpenseClass*>& user_ExpenseVector) {
    system("CLS");
    
    ExpenseClass* placeholder = new ExpenseClass();

    cout << "ADD EXPENSE\n\n";
    cout << "Description: ";
    getline(cin >> ws, placeholder->description);
    cout << "Amount: ";
    cin >> placeholder->amount;

    for (auto expense : user_ExpenseVector) {
        if (placeholder->description == expense->description) {
            expense->amount += placeholder->amount;
            cout << "\nExpense added successfully!\n";
            return;
        }
    }

    user_ExpenseVector.push_back(placeholder);
    cout << "\nExpense added successfully!\n";
    
    return;
}

void displayExpense(vector<ExpenseClass*> user_ExpenseVector) {
    system("CLS");

    cout << "YOUR EXPENSES\n\n";

    int counter = 0;
    for (auto expense : user_ExpenseVector) {
        cout << "-> " << expense->description << " : " << expense->amount << "\n";
    }

    cout << "[0] Go back.\n\n";

    while (true) {
        if (_getch() == '0') {
            cout << "\nGoing back...\n";
            break;
        }
    }

    return;
}

void renameBudget(BudgetClass*& userBudget, vector<BudgetClass*> user_BudgetVector) {
    system("CLS");

    string new_budget_name;
    
    cout << "New Budget Name: ";
    getline(cin >> ws, new_budget_name);

    for (auto budget : user_BudgetVector) {
        if (new_budget_name == budget->budget_name) {
            cerr << "\nError... Budget name already exists!\n";
            return;
        }
    }

    userBudget->budget_name = new_budget_name;
    cout << "\nBudget name renamed successfully!\n";

    return;
}
