#include <iostream>
#include <string>
#include "Utils.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "StudentFeeLoan.h"
#include "PersonalLoan.h"
#include "RelativeInvestment.h"

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showAboutUs() {
    cout << "\n\t\t\t====================================================\n";
    cout << "\t\t\t              ABOUT US\n";
    cout << "\t\t\t====================================================\n\n";
    cout << "\t\t\tBank Management System - OOP Project\n";
    cout << "\t\t\t2nd Semester C++ Programming\n";
    cout << "\t\t\tDaffodil International University\n\n";
    cout << "\t\t\tTeam Warriors:\n";
    cout << "\t\t\t[1] Umair Inayat\n\n";
}

void pauseSystem() {
    cout << "\n\t\t\tPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Admin Menu Functions
void adminAccountMenu(Account* account, int& size, const string& filename) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         ACCOUNT ADMIN PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] View Accounts\n";
        cout << "\t\t\t[2] Register Account\n";
        cout << "\t\t\t[3] Edit Account\n";
        cout << "\t\t\t[4] Delete Account\n";
        cout << "\t\t\t[5] Search Account\n";
        cout << "\t\t\t[6] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                account->display();
                pauseSystem();
                break;
            case 2:
                clearScreen();
                account->addAccount(size);
                pauseSystem();
                break;
            case 3:
                clearScreen();
                account->updateAccount();
                pauseSystem();
                break;
            case 4:
                clearScreen();
                account->deleteAccount(filename, size);
                pauseSystem();
                break;
            case 5:
                clearScreen();
                account->searchAccount();
                pauseSystem();
                break;
            case 6:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

void adminLoanMenu(Loan* loan, int& size, const string& filename) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         LOAN ADMIN PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] View Loans\n";
        cout << "\t\t\t[2] Register Loan\n";
        cout << "\t\t\t[3] Edit Loan\n";
        cout << "\t\t\t[4] Delete Loan\n";
        cout << "\t\t\t[5] Search Loan\n";
        cout << "\t\t\t[6] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                loan->display();
                pauseSystem();
                break;
            case 2:
                clearScreen();
                loan->addLoan();
                pauseSystem();
                break;
            case 3:
                clearScreen();
                loan->updateLoan();
                pauseSystem();
                break;
            case 4:
                clearScreen();
                loan->deleteLoan(filename, size);
                pauseSystem();
                break;
            case 5:
                clearScreen();
                loan->searchLoan();
                pauseSystem();
                break;
            case 6:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

void adminInvestmentMenu(Investment* investment, int& size, const string& filename) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t      INVESTMENT ADMIN PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] View Investments\n";
        cout << "\t\t\t[2] Register Investment\n";
        cout << "\t\t\t[3] Edit Investment\n";
        cout << "\t\t\t[4] Delete Investment\n";
        cout << "\t\t\t[5] Search Investment\n";
        cout << "\t\t\t[6] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                investment->display();
                pauseSystem();
                break;
            case 2:
                clearScreen();
                investment->addInvestment();
                pauseSystem();
                break;
            case 3:
                clearScreen();
                investment->updateInvestment();
                pauseSystem();
                break;
            case 4:
                clearScreen();
                investment->deleteInvestment(filename, size);
                pauseSystem();
                break;
            case 5:
                clearScreen();
                investment->searchInvestment();
                pauseSystem();
                break;
            case 6:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

// User Menu Functions
void userAccountMenu(Account* account) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         ACCOUNT USER PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] Balance Inquiry\n";
        cout << "\t\t\t[2] Deposit\n";
        cout << "\t\t\t[3] Withdraw\n";
        cout << "\t\t\t[4] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                account->searchAccount();
                pauseSystem();
                break;
            case 2: {
                clearScreen();
                double amount;
                cout << "\t\t\tEnter amount to deposit: ";
                cin >> amount;
                account->deposit(amount);
                pauseSystem();
                break;
            }
            case 3: {
                clearScreen();
                double amount;
                cout << "\t\t\tEnter amount to withdraw: ";
                cin >> amount;
                account->withdraw(amount);
                pauseSystem();
                break;
            }
            case 4:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

void userLoanMenu(Loan* loan) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         LOAN USER PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] Loan Inquiry\n";
        cout << "\t\t\t[2] Calculate Interest\n";
        cout << "\t\t\t[3] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                loan->searchLoan();
                pauseSystem();
                break;
            case 2:
                clearScreen();
                loan->calculateInterest();
                pauseSystem();
                break;
            case 3:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

void userInvestmentMenu(Investment* investment) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t      INVESTMENT USER PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] Investment Inquiry\n";
        cout << "\t\t\t[2] Calculate Returns\n";
        cout << "\t\t\t[3] Back to Main Menu\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                clearScreen();
                investment->searchInvestment();
                pauseSystem();
                break;
            case 2:
                clearScreen();
                investment->calculateReturns();
                pauseSystem();
                break;
            case 3:
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

// Main Admin Portal
void adminPortal(Account* savings, Account* checking, Loan* student, Loan* personal, Investment* relative,
                 int& saveSize, int& checkSize, int& studentSize, int& personalSize, int& relativeSize) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         ADMIN PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] Savings Account\n";
        cout << "\t\t\t[2] Checking Account\n";
        cout << "\t\t\t[3] Student Loan\n";
        cout << "\t\t\t[4] Personal Loan\n";
        cout << "\t\t\t[5] Relative Investment\n";
        cout << "\t\t\t[6] About Us\n";
        cout << "\t\t\t[7] Logout\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                adminAccountMenu(savings, saveSize, "data/save.txt");
                break;
            case 2:
                adminAccountMenu(checking, checkSize, "data/check.txt");
                break;
            case 3:
                adminLoanMenu(student, studentSize, "data/student.txt");
                break;
            case 4:
                adminLoanMenu(personal, personalSize, "data/personal.txt");
                break;
            case 5:
                adminInvestmentMenu(relative, relativeSize, "data/invest.txt");
                break;
            case 6:
                clearScreen();
                showAboutUs();
                pauseSystem();
                break;
            case 7:
                cout << "\n\t\t\tAdmin logged out at " << getCurrentTime() << endl;
                pauseSystem();
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

// Main User Portal
void userPortal(Account* savings, Account* checking, Loan* student, Loan* personal, Investment* relative) {
    while (true) {
        clearScreen();
        cout << "\n\t\t\t====================================================\n";
        cout << "\t\t\t         USER PORTAL\n";
        cout << "\t\t\t====================================================\n";
        cout << "\t\t\t[1] Savings Account\n";
        cout << "\t\t\t[2] Checking Account\n";
        cout << "\t\t\t[3] Student Loan\n";
        cout << "\t\t\t[4] Personal Loan\n";
        cout << "\t\t\t[5] Relative Investment\n";
        cout << "\t\t\t[6] About Us\n";
        cout << "\t\t\t[7] Logout\n";
        cout << "\t\t\tChoice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1:
                userAccountMenu(savings);
                break;
            case 2:
                userAccountMenu(checking);
                break;
            case 3:
                userLoanMenu(student);
                break;
            case 4:
                userLoanMenu(personal);
                break;
            case 5:
                userInvestmentMenu(relative);
                break;
            case 6:
                clearScreen();
                showAboutUs();
                pauseSystem();
                break;
            case 7:
                cout << "\n\t\t\tUser logged out at " << getCurrentTime() << endl;
                pauseSystem();
                return;
            default:
                cout << "\t\t\tInvalid choice!\n";
                pauseSystem();
        }
    }
}

int main() {
    clearScreen();
    
    cout << "\n\t\t\t====================================================\n";
    cout << "\t\t\t    WELCOME TO BANK MANAGEMENT SYSTEM\n";
    cout << "\t\t\t====================================================\n\n";
    
    // Count records in files
    int saveSize = countLinesInFile("data/save.txt");
    int checkSize = countLinesInFile("data/check.txt");
    int studentSize = countLinesInFile("data/student.txt");
    int personalSize = countLinesInFile("data/personal.txt");
    int relativeSize = countLinesInFile("data/invest.txt");
    
    // Create all objects
    Account* savings = new SavingsAccount("data/save.txt", &saveSize);
    Account* checking = new CheckingAccount("data/check.txt", &checkSize);
    Loan* student = new StudentFeeLoan("data/student.txt", &studentSize);
    Loan* personal = new PersonalLoan("data/personal.txt", &personalSize);
    Investment* relative = new RelativeInvestment("data/invest.txt", &relativeSize);
    
    // Main menu
    cout << "\t\t\tAccount Type:\n";
    cout << "\t\t\t[1] Administrator\n";
    cout << "\t\t\t[2] User\n";
    cout << "\t\t\tChoice: ";
    
    int choice;
    cin >> choice;
    
    switch (choice) {
        case 1:
            adminPortal(savings, checking, student, personal, relative,
                       saveSize, checkSize, studentSize, personalSize, relativeSize);
            break;
        case 2:
            userPortal(savings, checking, student, personal, relative);
            break;
        default:
            cout << "\t\t\tInvalid choice!\n";
    }
    
    // Cleanup
    delete savings;
    delete checking;
    delete student;
    delete personal;
    delete relative;
    
    cout << "\n\t\t\tThank you for using Bank Management System!\n\n";
    
    return 0;
}