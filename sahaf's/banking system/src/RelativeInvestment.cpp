#include "RelativeInvestment.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

RelativeInvestment::RelativeInvestment() 
    : Investment(), riskLevel(""), relativeName(""), dataFile(""), 
      size(nullptr), customers(nullptr), investments(nullptr) {}

RelativeInvestment::RelativeInvestment(const std::string& filename, int* sizePtr)
    : Investment(), dataFile(filename), size(sizePtr) {
    
    customers = new Customer*[*size];
    investments = new RelativeInvestment*[*size];
    for (int i = 0; i < *size; i++) { customers[i] = nullptr; investments[i] = nullptr; }
    
    std::ifstream file(filename);
    if (!file.is_open()) { std::cout << "\t\t\tFailed to open " << filename << std::endl; return; }
    
    int index = 0;
    std::string line;
    while (std::getline(file, line) && index < *size) {
        std::istringstream iss(line);
        std::string fname, lname, uname, pword, relName, risk, mail, phone;
        int invID;
        double amount;
        iss >> fname >> lname >> uname >> pword >> invID >> amount >> relName >> risk >> mail >> phone;
        
        customers[index] = new Customer(uname, pword);
        investments[index] = new RelativeInvestment(fname, lname, invID, amount, relName, risk, mail, phone);
        index++;
    }
    file.close();
}

RelativeInvestment::RelativeInvestment(const std::string& firstname, const std::string& lastname,
                                       int investmentID, double investmentAmount,
                                       const std::string& relativeName, const std::string& riskLevel,
                                       const std::string& email, const std::string& phonenumber)
    : Investment(firstname, lastname, investmentID, investmentAmount, email, phonenumber),
      relativeName(relativeName), riskLevel(riskLevel), dataFile(""), 
      size(nullptr), customers(nullptr), investments(nullptr) {}

int RelativeInvestment::findInvestment(int investmentNum) {
    for (int i = 0; i < *size; i++) {
        if (investments[i] && investments[i]->investmentID == investmentNum) return i;
    }
    return -1;
}

void RelativeInvestment::calculateReturns() {
    int invID;
    std::cout << "\t\t\tEnter investment ID: "; std::cin >> invID;
    int idx = findInvestment(invID);
    
    if (idx != -1 && customers[idx]->login()) {
        double returns = investments[idx]->investmentAmount * 0.05; // 5% return
        std::cout << "\t\t\tInvestment Amount: $" << investments[idx]->investmentAmount << std::endl;
        std::cout << "\t\t\tReturn Rate: 5%\n";
        std::cout << "\t\t\tTotal Returns: $" << returns << std::endl;
        std::cout << "\t\t\tTotal Value: $" << (investments[idx]->investmentAmount + returns) << std::endl;
    } else {
        std::cout << "\t\t\tInvestment not found or authentication failed!\n";
    }
}

void RelativeInvestment::display() {
    std::cout << "\n\t\t\t=== RELATIVE INVESTMENT LIST ===\n";
    std::cout << std::left << std::setw(15) << "Investment ID" << std::setw(20) << "Name"
              << std::setw(20) << "Username" << std::setw(15) << "Amount"
              << std::setw(20) << "Relative" << std::setw(15) << "Risk Level"
              << std::setw(30) << "Email" << std::setw(15) << "Phone" << std::endl;
    std::cout << std::string(160, '=') << std::endl;
    
    for (int i = 0; i < *size; i++) {
        std::cout << std::left << std::setw(15) << investments[i]->investmentID
                  << std::setw(20) << (investments[i]->firstname + " " + investments[i]->lastname)
                  << std::setw(20) << customers[i]->getUsername()
                  << std::setw(15) << investments[i]->investmentAmount
                  << std::setw(20) << investments[i]->relativeName
                  << std::setw(15) << investments[i]->riskLevel
                  << std::setw(30) << investments[i]->email
                  << std::setw(15) << investments[i]->phonenumber << std::endl;
    }
}

void RelativeInvestment::saveData() {
    std::ofstream file(dataFile);
    if (!file.is_open()) return;
    for (int i = 0; i < *size; i++) {
        file << std::left << std::setw(20) << investments[i]->firstname << std::setw(20) << investments[i]->lastname
             << std::setw(20) << customers[i]->getUsername() << std::setw(20) << customers[i]->getPassword()
             << std::setw(20) << investments[i]->investmentID << std::setw(20) << investments[i]->investmentAmount
             << std::setw(30) << investments[i]->relativeName << std::setw(25) << investments[i]->riskLevel
             << std::setw(30) << investments[i]->email << std::setw(20) << investments[i]->phonenumber << std::endl;
    }
    file.close();
}

void RelativeInvestment::searchInvestment() {
    int invID;
    std::cout << "\t\t\tEnter investment ID: "; std::cin >> invID;
    int idx = findInvestment(invID);
    if (idx != -1 && customers[idx]->login()) {
        std::cout << "\n\t\t\t=== Investment Details ===\n";
        std::cout << "\t\t\tName: " << investments[idx]->firstname << " " << investments[idx]->lastname << std::endl;
        std::cout << "\t\t\tInvestment ID: " << investments[idx]->investmentID << std::endl;
        std::cout << "\t\t\tAmount: $" << investments[idx]->investmentAmount << std::endl;
        std::cout << "\t\t\tRelative: " << investments[idx]->relativeName << std::endl;
        std::cout << "\t\t\tRisk Level: " << investments[idx]->riskLevel << std::endl;
    } else {
        std::cout << "\t\t\tInvestment not found!\n";
    }
}

void RelativeInvestment::addInvestment() {
    std::ofstream file(dataFile, std::ios::app);
    if (!file.is_open()) { std::cout << "\t\t\tFile error!\n"; return; }
    
    char choice;
    do {
        std::string fname, lname, uname, pword, relName, risk, mail, phone;
        int invID;
        double amount;
        std::cout << "\n\t\t\t=== INVESTMENT REGISTRATION ===\n";
        std::cout << "\t\t\tFirst name: "; std::cin >> fname;
        std::cout << "\t\t\tLast name: "; std::cin >> lname;
        std::cout << "\t\t\tUsername: "; std::cin >> uname;
        std::cout << "\t\t\tPassword: "; std::cin >> pword;
        std::cout << "\t\t\tInvestment ID: "; std::cin >> invID;
        std::cout << "\t\t\tInvestment Amount: "; std::cin >> amount;
        std::cout << "\t\t\tRelative Name: "; std::cin >> relName;
        std::cout << "\t\t\tRisk Level (Low/Medium/High): "; std::cin >> risk;
        std::cout << "\t\t\tEmail: "; std::cin >> mail;
        std::cout << "\t\t\tPhone: "; std::cin >> phone;
        
        file << std::left << std::setw(20) << fname << std::setw(20) << lname << std::setw(20) << uname
             << std::setw(20) << pword << std::setw(20) << invID << std::setw(20) << amount
             << std::setw(30) << relName << std::setw(25) << risk << std::setw(30) << mail
             << std::setw(20) << phone << std::endl;
        
        std::cout << "\t\t\tInvestment registered at " << getCurrentTime() << std::endl;
        std::cout << "\t\t\tAdd another? (Y/N): "; std::cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    file.close();
}

void RelativeInvestment::updateInvestment() {
    display();
    int invID;
    std::cout << "\t\t\tEnter investment ID to update: "; std::cin >> invID;
    int idx = findInvestment(invID);
    if (idx == -1) { std::cout << "\t\t\tInvestment not found!\n"; return; }
    
    std::string fname, lname, uname, pword, relName, risk, mail, phone;
    int newInvID;
    double amount;
    std::cout << "\t\t\tFirst name: "; std::cin >> fname;
    std::cout << "\t\t\tLast name: "; std::cin >> lname;
    std::cout << "\t\t\tUsername: "; std::cin >> uname;
    std::cout << "\t\t\tPassword: "; std::cin >> pword;
    std::cout << "\t\t\tInvestment ID: "; std::cin >> newInvID;
    std::cout << "\t\t\tAmount: "; std::cin >> amount;
    std::cout << "\t\t\tRelative Name: "; std::cin >> relName;
    std::cout << "\t\t\tRisk Level: "; std::cin >> risk;
    std::cout << "\t\t\tEmail: "; std::cin >> mail;
    std::cout << "\t\t\tPhone: "; std::cin >> phone;
    
    customers[idx]->setUsername(uname);
    customers[idx]->setPassword(pword);
    investments[idx]->setFirstName(fname);
    investments[idx]->setLastName(lname);
    investments[idx]->setInvestmentID(newInvID);
    investments[idx]->setInvestmentAmount(amount);
    investments[idx]->setRelativeName(relName);
    investments[idx]->setRiskLevel(risk);
    investments[idx]->setEmail(mail);
    investments[idx]->setPhoneNumber(phone);
    std::cout << "\t\t\tInvestment updated!\n";
    saveData();
}

void RelativeInvestment::shiftInvestmentsLeft(int index) {
    for (int i = index; i < *size - 1; i++) {
        customers[i] = customers[i + 1];
        investments[i] = investments[i + 1];
    }
}

void RelativeInvestment::deleteInvestment(const std::string& filename, int& sizeRef) {
    if (!admin.login()) return;
    display();
    int invID;
    std::cout << "\t\t\tEnter investment ID to delete: "; std::cin >> invID;
    int idx = findInvestment(invID);
    if (idx == -1) { std::cout << "\t\t\tInvestment not found!\n"; return; }
    
    char confirm;
    std::cout << "\t\t\tConfirm deletion? (Y/N): "; std::cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        delete customers[idx];
        delete investments[idx];
        shiftInvestmentsLeft(idx);
        (*size)--;
        saveData();
        std::cout << "\t\t\tDeleted at " << getCurrentTime() << std::endl;
    }
}

RelativeInvestment::~RelativeInvestment() {
    if (customers) {
        for (int i = 0; i < *size; i++) delete customers[i];
        delete[] customers;
    }
    if (investments) {
        for (int i = 0; i < *size; i++) delete investments[i];
        delete[] investments;
    }
}