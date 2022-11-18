#include <cstdlib>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>

class ExpenseClass {
public:
    std::string& getDescription();
    float& getAmount();
private:
    std::string description;
    float amount;
};

class BudgetClass {
public:
    const char*& getCurrency();
    std::string& getBudgetName();
    float& getBudgetedAmount();
    float& getCurrentBalance();
    std::vector<ExpenseClass>& getExpenseVector();

private:
    const char* currency = "Php";
    std::string budget_name;
    float budgeted_amount;
    float current_balance;
    std::vector<ExpenseClass> ExpenseVector;
};

class AccountClass {
public:
    std::string username;
    std::string password;
    std::vector<BudgetClass> BudgetVector;
};

void pause();

bool loginMenu(AccountClass user, std::vector<AccountClass>& AccountVector);
bool selectAccount(AccountClass& user, std::vector<AccountClass>& AccountVector);

bool signUpMenu(AccountClass new_user, std::vector<AccountClass>& AccountVector);
bool isUsernameExists(std::string& new_user, std::vector<AccountClass>& AccountVector);
bool isValidPassword(std::string& password);

int displaySelectBudget(std::vector<BudgetClass>& BudgetVector);
bool addBudget(std::vector<BudgetClass>& BudgetVector);
void openBudget(int index, BudgetClass& BudgetClass);

void addExpense(std::vector<ExpenseClass>& ExpenseVector);

int main()
{
    std::vector<AccountClass> AccountVector; // Account-Vector of Account-Class

loginSignUpMenu:
    AccountClass user; // current user

    bool logged_in = false;
    while (!logged_in) {
        system("CLS");

        std::cout << "WELCOME TO XYZ BUDGET PLANNER!\n\n";
        std::cout << "Press the number of the action you want to do.\n";
        std::cout << "[1] Login.\n";
        std::cout << "[2] Sign up.\n";
        std::cout << "[3] Exit.\n\n";

        char action = _getch();
        switch (action) {
        case '1':
            if (loginMenu(user, AccountVector)) { // Only accept successfull logins
                std::cout << "Logging in...\n";
                pause();
                logged_in = true;
            }
            break;
        case '2':
            if (signUpMenu(user, AccountVector)) { // Only accept successful sign ups
                std::cout << "Your account has been created...\n";
                pause();
            }
            break;
        case '3':
            std::cout << "Thank you for using XYZ Budget Planner!" << std::endl;
            exit(EXIT_SUCCESS);
        default:
            std::cerr << "Error... Invalid Action. Try Again!\n" << std::flush; // Don't accept invalid inputs
            pause();
        }
    }  

    ///
    ///
    /// FOR BUDGETING
    /// 
    ///...
    
    budgetMenu:
        system("CLS");
        std::cout << "WELCOME TO XYZ BUDGET PLANNER\n\n";
        std::cout << "Press the number of the action you want to do.\n";
        std::cout << "[1] Open a budget\n";
        std::cout << "[2] Add a budget\n";
        std::cout << "[3] Sign out\n";
        std::cout << "[4] Exit\n\n";

        char action = _getch();
        system("CLS");

        switch (action) {
        case '1' : {
                std::cout << "OPEN BUDGET\n\n";
                int index = displaySelectBudget(user.BudgetVector);
                if (!index) { // Only accept valid budget-vector indec
                    openBudget(index, user.BudgetVector[index]);
                }
                goto budgetMenu;
            }
            break;
        case '2':
            if (addBudget(user.BudgetVector)) { // Only accept successful adding of budget
                std::cout << "Your budget has been created...\n";
            }
            pause();
            goto budgetMenu;
            break;
        case '3':
            goto loginSignUpMenu;
            break;
        case '4':
            std::cout << "Thank you for using XYZ Budget Planner!" << std::endl;
            exit(EXIT_SUCCESS);
        default:
            std::cerr << "Error... Invalid Action. Try Again!\n" << std::flush;
            pause();
        }

}

void pause() {
    std::cout << "\nPress any key to continue..." << std::flush;
    _getch();
    return;
}

bool loginMenu(AccountClass user, std::vector<AccountClass>& AccountVector) {
    system("CLS");

    std::cout << "LOG IN\n";
    std::cout << "Username: ";
    std::cin >> user.username;
    std::cout << "Password: ";
    std::cin >> user.password;

    if (!selectAccount(user, AccountVector)) {
        std::cerr << "Error... Invalid username or password!" << std::flush;
        pause();
        return false;
    }
    return true;
}

bool selectAccount(AccountClass& user, std::vector<AccountClass>& AccountVector) {
    for (auto& account : AccountVector) {
        if ((user.username == account.username) && (user.password == account.password)) {
            user.username = account.username;
            user.password = account.password;
            user.BudgetVector = account.BudgetVector;
            return true;
        }
    }
    return false;
}

bool signUpMenu(AccountClass new_user, std::vector<AccountClass>& AccountVector) {
    system("CLS"); // Clear screen
    
    std::string confirm_password = "\n";

    std::cout << "SIGN IN\n";
    std::cout << "Username: ";
    std::cin >> new_user.username;
    std::cout << "Password: ";
    std::cin >> new_user.password;
    std::cout << "Confirm Password: ";
    std::cin >> confirm_password;

    if (new_user.password != confirm_password) {
        std::cerr << "Error...Password does not match!\n" << std::flush;
        pause();
        return false;
    }
    if (isUsernameExists(new_user.username, AccountVector)) {
        std::cerr << "Error... Username already Exists!\n" << std::flush;
        pause();
        return false;
    }
    if (!isValidPassword(new_user.password)) {
        std::cerr << "Error... Invalid Password.\n";
        std::cerr << "Password Requirements:\n";
        std::cerr << "\t•Must contain at least 1 lowercase letter.\n";
        std::cerr << "\t•Must contain at least 1 uppercase letter.\n";
        std::cerr << "\t•Must contain at least 1 number.\n";
        std::cerr << "\t•Must contain at least 1 of the following symbols (~`!@#$%^&*()_-+={[}]|\\:;\"\'<,>.?/).\n";
        std::cerr << "\t•Must contains at least 8 characters.\n" << std::flush;
        pause();
        return false;
    }
    AccountVector.push_back(new_user);
    return true;
}

bool isUsernameExists(std::string& new_user, std::vector<AccountClass>& AccountVector) {
    for (auto& account : AccountVector) {
        if (new_user == account.username) {
            return true;
        }
    }
    return false;
}

bool isValidPassword(std::string& password) {
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

int displaySelectBudget(std::vector<BudgetClass>& BudgetVector) {
displaySelectBudget:
    system("CLS");

    int n = 0, select_budget = 0;

    std::cout << "YOUR BUDGETS\n";

    for (auto& budget : BudgetVector) {
        std::cout << "[" << ++n << "] " << budget.getBudgetName() << ".\n"; // Diplay in this format: [1] BudgetName.
    }

    std::cout << "[" << ++n << "] " << "Exit." << "\n\n";
    std::cout << "Enter the number of the budget you want to select: ";
    std::cin >> select_budget;
    if (select_budget == n + 1) {
        std::cerr << "Exiting...\n";
        pause();
        return 0;
    }
    else if ((select_budget > n + 1) || (select_budget < n)) {
        std::cerr << "Error... Invalid Action. Try Again!\n" << std::flush;
        pause();
        goto displaySelectBudget;
    }

    return select_budget;
}

void openBudget(int index, BudgetClass& BudgetClass) {
openBudgetMenu:
    system("CLS");
    std::cout << "Your Current Balance: ";
    std::cout << "Press the number of the action you want to do.\n";
    std::cout << "[1] Add Expense\n";
    std::cout << "[2] Open Expense\n";
    std::cout << "[3] Edit Budgeted Amount\n";
    std::cout << "[4] Rename\n";
    std::cout << "[5] Go Back\n";
    
    char action = _getch();
    system("CLS");

    switch (action) {
    case '1':
        addExpense(BudgetClass.getExpenseVector());
        break;
    case '2':
        break;
    case '3':
        std::cout << "New Budgeted Amount: ";
        std::cin >> BudgetClass.getBudgetedAmount();
        break;
    case '4':
        std::cout << "New Budget Name: ";
        getline(std::cin >> std::ws, BudgetClass.getBudgetName());
        break;
    case '5':
        break;
    default:
        std::cerr << "Error... Invalid Action. Try Again!\n" << std::flush;
        pause();
        goto openBudgetMenu;
    }

    return;
}

bool addBudget(std::vector<BudgetClass>& BudgetVector) {
    system("CLS");
    
    BudgetClass placeholder;
    
    std::cout << "ADD BUDGET\n\n";
    std::cout << "Budget Name: ";
    getline(std::cin >> std::ws, placeholder.getBudgetName());
    std::cout << "Budgeted Amount: ";
    std::cin >> placeholder.getBudgetedAmount();

    for (auto& budget : BudgetVector) {
        if (placeholder.getBudgetName() == budget.getBudgetName()) {
            std::cerr << "Error... Budget already exists!\n" << std::flush;
            return false;
        }
    }
    BudgetVector.push_back(placeholder);
    return true;
}

void addExpense(std::vector<ExpenseClass>& ExpenseVector) {
    ExpenseClass placeholder;

    std::cout << "ADD EXPENSE\n\n";
    std::cout << "Description: ";
    getline(std::cin >> std::ws, placeholder.getDescription());
    std::cout << "Amount: ";
    std::cin >> placeholder.getAmount();

    for (auto& expense : ExpenseVector) {
        if (placeholder.getDescription() == expense.getDescription()) {
            expense.getAmount() += placeholder.getAmount();
            return;
        }
    }
    ExpenseVector.push_back(placeholder);
    return;
}

void displayExpense(std::vector<ExpenseClass>& ExpenseVector) {
displayExpense:
    std::cout << "YOUR EXPENSES\n";
    int counter = 0;
    for (auto& expense : ExpenseVector) {
        std::cout << ++counter << ". " << expense.getDescription() << " : " << expense.getAmount() << "\n";
    }
    std::cout << "[0] Exit.\n";
    if (_getch() == '0')
        return;
    goto displayExpense;
}


/*
-------------------------------
Class Methods (Expense Class) 
-------------------------------
*/
std::string& ExpenseClass::getDescription() {
    return description;
}
float& ExpenseClass::getAmount() {
    return amount;
}

/*
-------------------------------
Class Methods (Budget Class)
-------------------------------
*/
const char*& BudgetClass::getCurrency() {
    return currency;
}
std::string& BudgetClass::getBudgetName() {
    return budget_name;
}
float& BudgetClass::getBudgetedAmount() {
    return budgeted_amount;
}
float& BudgetClass::getCurrentBalance() {
    return current_balance;
}
std::vector<ExpenseClass>& BudgetClass::getExpenseVector() {
    return ExpenseVector;
}

