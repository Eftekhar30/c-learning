# Bank Management System

A comprehensive C++ bank management system with account management, loan processing, and investment tracking capabilities.

## Features

### Account Management
- **Savings Account**: Interest-bearing accounts with deposit/withdrawal functionality
- **Checking Account**: Transaction accounts with service fees

### Loan Management
- **Student Fee Loans**: Educational financing with enrollment year tracking
- **Personal Loans**: General purpose loans with flexible terms

### Investment Management
- **Relative Investment**: Investment accounts with risk level tracking and relative beneficiary information

## Project Structure

```
BankManagementSystem/
├── include/          # Header files
├── src/             # Implementation files
├── data/            # Data storage files
├── docs/            # Documentation
└── README.md        # This file
```

## Prerequisites

- C++ Compiler (GCC 7.0+ or MSVC 2017+)
- Standard C++ Library
- Windows OS (for `_strdate_s` and `_strtime_s` functions)

## Compilation

### Using g++
```bash
g++ -std=c++11 -I include src/*.cpp -o BankManagementSystem
```

### Using Visual Studio
1. Create a new C++ Console Application project
2. Add all `.h` files to the project (include folder)
3. Add all `.cpp` files to the project (src folder)
4. Build and run

## Usage

### Admin Portal
- View all accounts/loans/investments
- Add new records
- Update existing records
- Delete records
- Search functionality

**Default Admin Credentials:**
- Username: `admin`
- Password: `admin`

### User Portal
- Check balance
- Deposit money
- Withdraw money
- View loan details
- Calculate loan interest
- View investment returns

**Default User Credentials:**
- Username: `user`
- Password: `user`

## Data Files

The system uses text files for data persistence:

- `save.txt` - Savings account data
- `check.txt` - Checking account data
- `student.txt` - Student loan data
- `personal.txt` - Personal loan data
- `invest.txt` - Investment data

### Data Format

**Savings/Checking Account:**
```
FirstName LastName Username Password AccountNumber Balance CardType Email PhoneNumber
```

**Student Loan:**
```
FirstName LastName Username Password LoanNumber Amount Rate EnrollmentYear Email PhoneNumber
```

**Personal Loan:**
```
FirstName LastName Username Password LoanNumber Amount Rate LoanTime Email PhoneNumber
```

**Investment:**
```
FirstName LastName Username Password InvestmentID Amount RelativeName RiskLevel Email PhoneNumber
```

## Class Hierarchy

### User Classes
```
User (Abstract)
├── Customer
└── Admin
```

### Account Classes
```
Account (Abstract)
├── SavingsAccount
└── CheckingAccount
```

### Loan Classes
```
Loan (Abstract)
├── StudentFeeLoan
└── PersonalLoan
```

### Investment Classes
```
Investment (Abstract)
└── RelativeInvestment
```

## Key Features by Module

### Account Module
- Polymorphic account management
- File I/O for data persistence
- Transaction logging with timestamps
- Balance validation
- Exception handling for insufficient funds

### Loan Module
- Interest calculation
- Loan term tracking
- Multiple loan type support
- Enrollment year tracking (Student loans)
- Flexible repayment periods (Personal loans)

### Investment Module
- Risk level assessment
- Return calculation (5% default)
- Beneficiary tracking
- Investment portfolio management

## Security Features

- Password-protected access
- Admin/User role separation
- Login validation
- Account authentication for transactions

## Error Handling

- File operation validation
- Input validation
- Exception handling for withdrawals
- Boundary checks for array operations

## Future Enhancements

- [ ] Password encryption
- [ ] Transaction history
- [ ] Interest rate configuration
- [ ] Multi-currency support
- [ ] Report generation
- [ ] Database integration
- [ ] GUI interface

## Contributing

This is an academic project. For improvements:
1. Follow existing code structure
2. Maintain class hierarchy
3. Add proper error handling
4. Document new features

## Authors

**Team Warriors**
- Umair Inayat

## License

This project is created for educational purposes.

## Acknowledgments


## Contact

For questions or issues, please contact the project maintainers.

---

**Note:** This system uses Windows-specific functions (`_strdate_s`, `_strtime_s`). For cross-platform compatibility, replace these with C++11 `<chrono>` library functions.