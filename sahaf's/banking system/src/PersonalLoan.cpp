#include "PersonalLoan.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

PersonalLoan::PersonalLoan() 
    : Loan(), loanDuration(0), dataFile(""), size(nullptr), 
      customers(nullptr), loans(nullptr) {}

PersonalLoan::PersonalLoan(const std::string& filename, int* sizePtr)
    : Loan(), dataFile(filename), size(sizePtr) {
    
    customers = new Customer*[*size];
    loans = new PersonalLoan*[*size];
    for (int i = 0; i < *size; i++) { customers[i] = nullptr; loans[i] = nullptr; }
    
    std::ifstream file(filename);
    if (!file.is_open()) { std::cout << "\t\t\tFailed to open " << filename << std::endl; return; }
    
    int index = 0;
    std::string line;
    while (std::getline(file, line) && index < *size) {
        std::istringstream iss(line);
        std::string fname, lname, uname, pword, mail, phone;
        int loanNum, duration;
        double amount, rate;
        iss >> fname >> lname >> uname >> pword >> loanNum >> amount >> rate >> duration >> mail >> phone;
        
        customers[index] = new Customer(uname, pword);
        loans[index] = new PersonalLoan(fname, lname, loanNum, amount, rate, duration, mail, phone);
        index++;
    }
    file.close();
}

PersonalLoan::PersonalLoan(const std::string& firstname, const std::string& lastname,
                           int loanNumber, double loanAmount, double interestRate,
                           int loanDuration, const std::string& email,
                           const std::string& phonenumber)
    : Loan(firstname, lastname, loanNumber, loanAmount, interestRate, email, phonenumber),
      loanDuration(loanDuration), dataFile(""), size(nullptr), customers(nullptr), loans(nullptr) {}

int PersonalLoan::findLoan(int loanNum) {
    for (int i = 0; i < *size; i++) {
        if (loans[i] && loans[i]->loanNumber == loanNum) return i;
    }
    return -1;
}

void PersonalLoan::calculateInterest() {
    int loanNum;
    std::cout << "\t\t\tEnter loan number: "; std::cin >> loanNum;
    int idx = findLoan(loanNum);
    
    if (idx != -1 && customers[idx]->login()) {
        double interest = (loans[idx]->loanAmount * loans[idx]->interestRate) / 100;
        std::cout << "\t\t\tLoan Amount: $" << loans[idx]->loanAmount << std::endl;
        std::cout << "\t\t\tInterest Rate: " << loans[idx]->interestRate << "%\n";
        std::cout << "\t\t\tTotal Interest: $" << interest << std::endl;
    } else {
        std::cout << "\t\t\tLoan not found or authentication failed!\n";
    }
}

void PersonalLoan::display() {
    std::cout << "\n\t\t\t=== PERSONAL LOAN LIST ===\n";
    std::cout << std::left << std::setw(15) << "Loan No" << std::setw(20) << "Name"
              << std::setw(20) << "Username" << std::setw(15) << "Amount"
              << std::setw(10) << "Rate" << std::setw(15) << "Duration"
              << std::setw(30) << "Email" << std::setw(15) << "Phone" << std::endl;
    std::cout << std::string(150, '=') << std::endl;
    
    for (int i = 0; i < *size; i++) {
        std::cout << std::left << std::setw(15) << loans[i]->loanNumber
                  << std::setw(20) << (loans[i]->firstname + " " + loans[i]->lastname)
                  << std::setw(20) << customers[i]->getUsername()
                  << std::setw(15) << loans[i]->loanAmount
                  << std::setw(10) << loans[i]->interestRate
                  << std::setw(15) << loans[i]->loanDuration
                  << std::setw(30) << loans[i]->email
                  << std::setw(15) << loans[i]->phonenumber << std::endl;
    }
}

void PersonalLoan::saveLoanData() {
    std::ofstream file(dataFile);
    if (!file.is_open()) return;
    for (int i = 0; i < *size; i++) {
        file << std::left << std::setw(20) << loans[i]->firstname << std::setw(20) << loans[i]->lastname
             << std::setw(20) << customers[i]->getUsername() << std::setw(20) << customers[i]->getPassword()
             << std::setw(20) << loans[i]->loanNumber << std::setw(20) << loans[i]->loanAmount
             << std::setw(20) << loans[i]->interestRate << std::setw(20) << loans[i]->loanDuration
             << std::setw(30) << loans[i]->email << std::setw(20) << loans[i]->phonenumber << std::endl;
    }
    file.close();
}

void PersonalLoan::searchLoan() {
    int loanNum;
    std::cout << "\t\t\tEnter loan number: "; std::cin >> loanNum;
    int idx = findLoan(loanNum);
    if (idx != -1 && customers[idx]->login()) {
        std::cout << "\n\t\t\t=== Loan Details ===\n";
        std::cout << "\t\t\tName: " << loans[idx]->firstname << " " << loans[idx]->lastname << std::endl;
        std::cout << "\t\t\tLoan Number: " << loans[idx]->loanNumber << std::endl;
        std::cout << "\t\t\tAmount: $" << loans[idx]->loanAmount << std::endl;
        std::cout << "\t\t\tRate: " << loans[idx]->interestRate << "%\n";
        std::cout << "\t\t\tDuration: " << loans[idx]->loanDuration << " years\n";
    } else {
        std::cout << "\t\t\tLoan not found!\n";
    }
}

void PersonalLoan::addLoan() {
    std::ofstream file(dataFile, std::ios::app);
    if (!file.is_open()) { std::cout << "\t\t\tFile error!\n"; return; }
    
    char choice;
    do {
        std::string fname, lname, uname, pword, mail, phone;
        int loanNum, duration;
        double amount, rate;
        std::cout << "\n\t\t\t=== PERSONAL LOAN REGISTRATION ===\n";
        std::cout << "\t\t\tFirst name: "; std::cin >> fname;
        std::cout << "\t\t\tLast name: "; std::cin >> lname;
        std::cout << "\t\t\tUsername: "; std::cin >> uname;
        std::cout << "\t\t\tPassword: "; std::cin >> pword;
        std::cout << "\t\t\tLoan Number: "; std::cin >> loanNum;
        std::cout << "\t\t\tLoan Amount: "; std::cin >> amount;
        std::cout << "\t\t\tInterest Rate (%): "; std::cin >> rate;
        std::cout << "\t\t\tLoan Duration (years): "; std::cin >> duration;
        std::cout << "\t\t\tEmail: "; std::cin >> mail;
        std::cout << "\t\t\tPhone: "; std::cin >> phone;
        
        file << std::left << std::setw(20) << fname << std::setw(20) << lname << std::setw(20) << uname
             << std::setw(20) << pword << std::setw(20) << loanNum << std::setw(20) << amount
             << std::setw(20) << rate << std::setw(20) << duration << std::setw(30) << mail
             << std::setw(20) << phone << std::endl;
        
        std::cout << "\t\t\tLoan registered at " << getCurrentTime() << std::endl;
        std::cout << "\t\t\tAdd another? (Y/N): "; std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    file.close();
}

void PersonalLoan::updateLoan() {
    display();
    int loanNum;
    std::cout << "\t\t\tEnter loan number to update: "; std::cin >> loanNum;
    int idx = findLoan(loanNum);
    if (idx == -1) { std::cout << "\t\t\tLoan not found!\n"; return; }
    
    std::string fname, lname, uname, pword, mail, phone;
    int newLoanNum, duration;
    double amount, rate;
    std::cout << "\t\t\tFirst name: "; std::cin >> fname;
    std::cout << "\t\t\tLast name: "; std::cin >> lname;
    std::cout << "\t\t\tUsername: "; std::cin >> uname;
    std::cout << "\t\t\tPassword: "; std::cin >> pword;
    std::cout << "\t\t\tLoan Number: "; std::cin >> newLoanNum;
    std::cout << "\t\t\tAmount: "; std::cin >> amount;
    std::cout << "\t\t\tRate: "; std::cin >> rate;
    std::cout << "\t\t\tDuration: "; std::cin >> duration;
    std::cout << "\t\t\tEmail: "; std::cin >> mail;
    std::cout << "\t\t\tPhone: "; std::cin >> phone;
    
    customers[idx]->setUsername(uname);
    customers[idx]->setPassword(pword);
    loans[idx]->setFirstName(fname);
    loans[idx]->setLastName(lname);
    loans[idx]->setLoanNumber(newLoanNum);
    loans[idx]->setLoanAmount(amount);
    loans[idx]->setInterestRate(rate);
    loans[idx]->setLoanDuration(duration);
    loans[idx]->setEmail(mail);
    loans[idx]->setPhoneNumber(phone);
    std::cout << "\t\t\tLoan updated!\n";
    saveLoanData();
}

void PersonalLoan::shiftLoansLeft(int index) {
    for (int i = index; i < *size - 1; i++) {
        customers[i] = customers[i + 1];
        loans[i] = loans[i + 1];
    }
}

void PersonalLoan::deleteLoan(const std::string& filename, int& sizeRef) {
    if (!admin.login()) return;
    display();
    int loanNum;
    std::cout << "\t\t\tEnter loan number to delete: "; std::cin >> loanNum;
    int idx = findLoan(loanNum);
    if (idx == -1) { std::cout << "\t\t\tLoan not found!\n"; return; }
    
    char confirm;
    std::cout << "\t\t\tConfirm deletion? (Y/N): "; std::cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        delete customers[idx];
        delete loans[idx];
        shiftLoansLeft(idx);
        (*size)--;
        saveLoanData();
        std::cout << "\t\t\tDeleted at " << getCurrentTime() << std::endl;
    }
}

PersonalLoan::~PersonalLoan() {
    if (customers) {
        for (int i = 0; i < *size; i++) delete customers[i];
        delete[] customers;
    }
    if (loans) {
        for (int i = 0; i < *size; i++) delete loans[i];
        delete[] loans;
    }
}