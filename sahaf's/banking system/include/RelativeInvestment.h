#ifndef RELATIVE_INVESTMENT_H
#define RELATIVE_INVESTMENT_H

#include "Investment.h"
#include "Customer.h"
#include "Admin.h"

class RelativeInvestment : public Investment {
private:
    std::string riskLevel;
    std::string relativeName;
    std::string dataFile;
    int* size;
    Customer** customers;
    RelativeInvestment** investments;
    Admin admin;
    
    int findInvestment(int investmentNum);
    void shiftInvestmentsLeft(int index);

public:
    RelativeInvestment();
    RelativeInvestment(const std::string& filename, int* sizePtr);
    RelativeInvestment(const std::string& firstname, const std::string& lastname,
                       int investmentID, double investmentAmount,
                       const std::string& relativeName, const std::string& riskLevel,
                       const std::string& email, const std::string& phonenumber);
    
    std::string getRelativeName() const { return relativeName; }
    std::string getRiskLevel() const { return riskLevel; }
    void setRelativeName(const std::string& name) { relativeName = name; }
    void setRiskLevel(const std::string& level) { riskLevel = level; }
    
    void calculateReturns() override;
    void display() override;
    void searchInvestment() override;
    void saveData() override;
    void addInvestment() override;
    void deleteInvestment(const std::string& filename, int& size) override;
    void updateInvestment() override;
    
    ~RelativeInvestment();
};

#endif