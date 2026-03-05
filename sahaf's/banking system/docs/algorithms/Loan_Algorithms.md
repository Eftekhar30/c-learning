# Loan Management System - Algorithms Documentation

## Table of Contents
1. [Calculate Interest Algorithm](#calculate-interest-algorithm)
2. [Add Loan Algorithm](#add-loan-algorithm)
3. [Update Loan Algorithm](#update-loan-algorithm)
4. [Search Loan Algorithm](#search-loan-algorithm)
5. [Delete Loan Algorithm](#delete-loan-algorithm)
6. [Save Loan Data Algorithm](#save-loan-data-algorithm)
7. [Load Loan Data Algorithm](#load-loan-data-algorithm)

---

## Calculate Interest Algorithm

### Purpose
Calculate and display the total interest on a loan based on principal amount and interest rate.

### Flowchart Logic
```
START
  ↓
INPUT loan number
  ↓
SEARCH for loan in array
  ↓
IF loan found?
  ├─ YES → Authenticate user
  │         ↓
  │    IF login successful?
  │      ├─ YES → GET loan amount
  │      │         ↓
  │      │    GET interest rate
  │      │         ↓
  │      │    CALCULATE interest:
  │      │    interest = (loanAmount × interestRate) ÷ 100
  │      │         ↓
  │      │    DISPLAY result
  │      └─ NO → DISPLAY "Login failed"
  └─ NO → DISPLAY "Loan not found"
  ↓
END
```

### Pseudocode
```
FUNCTION calculateInterest():
    INPUT loanNumber
    found = FALSE
    loanIndex = -1
    
    // Search for loan
    FOR i = 0 TO size-1:
        IF loans[i].loanNumber == loanNumber:
            IF customer[i].login():
                found = TRUE
                loanIndex = i
                BREAK
    
    IF found:
        // Get loan details
        loanAmount = loans[loanIndex].getLoanAmount()
        interestRate = loans[loanIndex].getInterestRate()
        
        // Calculate simple interest
        interest = (loanAmount * interestRate) / 100
        
        DISPLAY "Total interest on loan " + loanNumber + " is $" + interest
    ELSE:
        DISPLAY "Loan not found"
END FUNCTION
```

### Mathematical Formula

**Simple Interest Formula:**
```
Interest = (Principal × Rate × Time) / 100

Where:
- Principal = Loan Amount
- Rate = Annual Interest Rate (%)
- Time = Loan Duration (years)

For this implementation:
Interest = (Loan Amount × Interest Rate) / 100
```

### Example Calculation
```
Loan Amount: $10,000
Interest Rate: 5%

Interest = (10,000 × 5) / 100
Interest = 50,000 / 100
Interest = $500
```

### Time Complexity
- **Search**: O(n)
- **Calculation**: O(1)
- **Total**: O(n)

### Space Complexity
- O(1) - Only temporary variables used

---

## Add Loan Algorithm

### Purpose
Register a new loan in the system with customer authentication.

### Flowchart Logic
```
START
  ↓
OPEN loan file in append mode
  ↓
IF file opened successfully?
  ├─ YES → DO
  │         ↓
  │    INPUT loan details:
  │    - First name, Last name
  │    - Username, Password
  │    - Loan number
  │    - Loan amount
  │    - Interest rate
  │    - Email, Phone number
  │    - Type-specific data:
  │      * Student: Enrollment year
  │      * Personal: Loan duration
  │         ↓
  │    CREATE new Customer object
  │         ↓
  │    CREATE new Loan object
  │         ↓
  │    ADD to arrays
  │         ↓
  │    INCREMENT size
  │         ↓
  │    WRITE data to file
  │         ↓
  │    DISPLAY success with timestamp
  │         ↓
  │    PROMPT "Add another? (Y/N)"
  │    ↓
  │    WHILE user enters 'Y' or 'y'
  │         ↓
  │    CLOSE file
  └─ NO → DISPLAY "File not open"
  ↓
END
```

### Pseudocode - Student Fee Loan
```
FUNCTION addStudentLoan():
    OPEN studentLoanFile in APPEND mode
    
    IF NOT file.isOpen():
        DISPLAY "File open failed"
        RETURN
    
    DO:
        INPUT firstName, lastName
        INPUT username, password
        INPUT enrollmentYear
        INPUT loanNumber
        INPUT loanAmount
        INPUT email
        INPUT interestRate
        INPUT phoneNumber
        
        // Create objects
        customer[size] = NEW Customer(username, password)
        loans[size] = NEW StudentFeeLoan(firstName, lastName, loanNumber,
                                          loanAmount, interestRate, 
                                          enrollmentYear, email, phoneNumber)
        
        size++
        
        // Write to file
        WRITE loan data to file with formatting
        
        CLOSE file
        
        DISPLAY "Loan registered successfully at [timestamp]"
        
        INPUT "Add another? (Y/N)" → choice
    WHILE choice == 'Y' OR choice == 'y'
END FUNCTION
```

### Pseudocode - Personal Loan
```
FUNCTION addPersonalLoan():
    OPEN personalLoanFile in APPEND mode
    
    IF NOT file.isOpen():
        DISPLAY "File open failed"
        RETURN
    
    DO:
        INPUT firstName, lastName
        INPUT username, password
        INPUT loanDuration  // in years
        INPUT loanNumber
        INPUT loanAmount
        INPUT email
        INPUT interestRate
        INPUT phoneNumber
        
        // Create objects
        customer[size] = NEW Customer(username, password)
        loans[size] = NEW PersonalLoan(firstName, lastName, loanNumber,
                                        loanAmount, interestRate,
                                        loanDuration, email, phoneNumber)
        
        size++
        
        // Write to file
        WRITE loan data to file
        
        CLOSE file
        
        DISPLAY "Loan registered successfully at [timestamp]"
        
        INPUT "Add another? (Y/N)" → choice
    WHILE choice == 'Y' OR choice == 'y'
END FUNCTION
```

### Data Validation
- Loan amount > 0
- Interest rate: 0 < rate < 100
- Loan number: Unique identifier
- Enrollment year/Duration: Valid range

### Time Complexity
- **Per Loan**: O(1)
- **For n loans**: O(n)

---

## Update Loan Algorithm

### Purpose
Modify existing loan information with full data replacement.

### Flowchart Logic
```
START
  ↓
DISPLAY all loans
  ↓
INPUT loan number to update
  ↓
SEARCH for loan
  ↓
IF loan found?
  ├─ YES → DISPLAY current loan details
  │         ↓
  │    INPUT new values for all fields:
  │    - First name, Last name
  │    - Username, Password
  │    - Loan number
  │    - Loan amount
  │    - Interest rate
  │    - Email, Phone number
  │    - Type-specific fields
  │         ↓
  │    UPDATE all fields using setters
  │         ↓
  │    SAVE data to file
  │         ↓
  │    DISPLAY "Loan updated at [timestamp]"
  └─ NO → DISPLAY "Loan not found"
  ↓
END
```

### Pseudocode - Student Loan Update
```
FUNCTION updateStudentLoan():
    CALL display()  // Show all student loans
    
    INPUT loanNumber
    found = FALSE
    updateIndex = -1
    
    FOR i = 0 TO size-1:
        IF loans[i].loanNumber == loanNumber:
            // Display current information
            DISPLAY loans[i].getDetails()
            found = TRUE
            updateIndex = i
            BREAK
    
    IF found:
        // Input new values
        INPUT newFirstName, newLastName
        INPUT newUsername, newPassword
        INPUT newLoanNumber
        INPUT newLoanAmount
        INPUT newInterestRate
        INPUT newEmail, newPhoneNumber
        INPUT newEnrollmentYear
        
        // Replace object completely
        customer[updateIndex] = NEW Customer(newUsername, newPassword)
        loans[updateIndex] = NEW StudentFeeLoan(newFirstName, newLastName,
                                                 newLoanNumber, newLoanAmount,
                                                 newInterestRate, newEnrollmentYear,
                                                 newEmail, newPhoneNumber)
        
        DISPLAY "Loan updated at [timestamp]"
        CALL saveLoanData()
    ELSE:
        DISPLAY "Loan not found"
END FUNCTION
```

### Pseudocode - Personal Loan Update
```
FUNCTION updatePersonalLoan():
    CALL display()
    
    INPUT loanNumber
    found = FALSE
    updateIndex = -1
    
    FOR i = 0 TO size-1:
        IF loans[i].loanNumber == loanNumber:
            DISPLAY loans[i].getDetails()
            found = TRUE
            updateIndex = i
            BREAK
    
    IF found:
        INPUT newUsername, newPassword
        INPUT newLoanNumber
        INPUT newLoanAmount
        INPUT newLoanDuration
        INPUT newEmail, newPhoneNumber
        INPUT newInterestRate
        
        // Update using setters (more efficient than replacement)
        customer[updateIndex].setUsername(newUsername)
        customer[updateIndex].setPassword(newPassword)
        loans[updateIndex].setLoanNumber(newLoanNumber)
        loans[updateIndex].setLoanAmount(newLoanAmount)
        loans[updateIndex].setInterestRate(newInterestRate)
        loans[updateIndex].setDuration(newLoanDuration)
        loans[updateIndex].setEmail(newEmail)
        loans[updateIndex].setPhoneNumber(newPhoneNumber)
        
        DISPLAY "Loan updated at [timestamp]"
        CALL saveLoanData()
    ELSE:
        DISPLAY "Loan not found"
END FUNCTION
```

### Time Complexity
- **Search**: O(n)
- **Update**: O(1)
- **Save**: O(n)
- **Total**: O(n)

---

## Search Loan Algorithm

### Purpose
Find and display specific loan details with authentication.

### Flowchart Logic
```
START
  ↓
INPUT loan number
  ↓
SET found = FALSE
  ↓
FOR each loan in array
  ↓
  IF loan number matches?
    ├─ YES → Authenticate user
    │         ↓
    │    IF login successful?
    │      ├─ YES → SET found = TRUE
    │      │         ↓
    │      │    BREAK loop
    │      └─ NO → CONTINUE searching
    └─ NO → CONTINUE
  ↓
IF found?
  ├─ YES → DISPLAY loan details:
  │         - Name
  │         - Username
  │         - Loan number
  │         - Loan amount
  │         - Interest rate
  │         - Type-specific info
  │         - Email, Phone
  └─ NO → DISPLAY "Loan not found"
  ↓
END
```

### Pseudocode
```
FUNCTION searchLoan():
    INPUT loanNumber
    found = FALSE
    loanIndex = -1
    
    FOR i = 0 TO size-1:
        IF loans[i].loanNumber == loanNumber:
            IF customer[i].login():
                found = TRUE
                loanIndex = i
                BREAK
    
    IF found:
        loan = loans[loanIndex]
        cust = customer[loanIndex]
        
        DISPLAY "Name: " + loan.getFirstName() + " " + loan.getLastName()
        DISPLAY "Username: " + cust.getUsername()
        DISPLAY "Loan Number: " + loan.getLoanNumber()
        DISPLAY "Loan Amount: $" + loan.getLoanAmount()
        DISPLAY "Interest Rate: " + loan.getInterestRate() + "%"
        
        // Type-specific information
        IF loan is StudentFeeLoan:
            DISPLAY "Enrollment Year: " + loan.getEnrollmentYear()
        ELSE IF loan is PersonalLoan:
            DISPLAY "Loan Duration: " + loan.getDuration() + " years"
        
        DISPLAY "Email: " + loan.getEmail()
        DISPLAY "Phone: " + loan.getPhoneNumber()
    ELSE:
        DISPLAY "Loan not found or authentication failed"
END FUNCTION
```

### Security Features
- Requires user authentication
- Only loan owner can view details
- Password verification before display

### Time Complexity
- O(n) - Linear search with authentication

---

## Delete Loan Algorithm

### Purpose
Remove a loan from the system (Admin only) with confirmation.

### Flowchart Logic
```
START
  ↓
VERIFY admin login
  ↓
IF admin authenticated?
  ├─ YES → DISPLAY all loans
  │         ↓
  │    INPUT loan number to delete
  │         ↓
  │    SEARCH for loan
  │         ↓
  │    IF loan found?
  │      ├─ YES → DISPLAY loan details
  │      │         ↓
  │      │    CONFIRM deletion (Y/N)
  │      │         ↓
  │      │    IF confirmed?
  │      │      ├─ YES → DELETE customer object
  │      │      │         ↓
  │      │      │    DELETE loan object
  │      │      │         ↓
  │      │      │    SHIFT remaining elements
  │      │      │         ↓
  │      │      │    DECREMENT size
  │      │      │         ↓
  │      │      │    SAVE data
  │      │      │         ↓
  │      │      │    DISPLAY success
  │      │      └─ NO → DISPLAY "Cancelled"
  │      └─ NO → DISPLAY "Loan not found"
  └─ NO → DISPLAY "Authentication failed"
  ↓
END
```

### Pseudocode
```
FUNCTION deleteLoan(filename, currentSize):
    // Admin authentication
    IF NOT admin.login():
        DISPLAY "Admin authentication failed"
        RETURN
    
    CALL display()  // Show all loans
    
    INPUT loanNumber
    found = FALSE
    deleteIndex = -1
    
    // Search for loan
    FOR i = 0 TO size-1:
        IF loans[i].loanNumber == loanNumber:
            DISPLAY loans[i].getDetails()
            found = TRUE
            deleteIndex = i
            BREAK
    
    IF found:
        INPUT "Enter Y to delete this loan" → confirmation
        
        IF confirmation == 'Y' OR confirmation == 'y':
            // Delete objects
            DELETE customer[deleteIndex]
            DELETE loans[deleteIndex]
            
            // Shift array elements left
            FOR i = deleteIndex TO size-2:
                customer[i] = customer[i+1]
                loans[i] = loans[i+1]
            
            size--
            
            CALL saveLoanData()
            DISPLAY "Loan deleted at [timestamp]"
        ELSE:
            DISPLAY "Deletion cancelled"
    ELSE:
        DISPLAY "Loan not found"
END FUNCTION
```

### Safety Measures
1. **Admin-only access**: Prevents unauthorized deletion
2. **Confirmation prompt**: Prevents accidental deletion
3. **Display before delete**: Shows what will be deleted
4. **Immediate save**: Persists changes right away

### Time Complexity
- **Search**: O(n)
- **Delete & Shift**: O(n)
- **Save**: O(n)
- **Total**: O(n)

### Memory Management
```cpp
// Proper cleanup
delete customer[deleteIndex];  // Free customer memory
delete loans[deleteIndex];     // Free loan memory

// Shift pointers (not copy objects)
for (int i = deleteIndex; i < size-1; i++) {
    customer[i] = customer[i+1];  // Move pointer
    loans[i] = loans[i+1];         // Move pointer
}
```

---

## Save Loan Data Algorithm

### Purpose
Write all loan records to persistent storage.

### Flowchart Logic
```
START
  ↓
OPEN loan file in output mode
  ↓
IF file opened?
  ├─ YES → FOR each loan (i = 0 to size-1)
  │         ↓
  │    GET customer[i] data
  │         ↓
  │    GET loan[i] data
  │         ↓
  │    WRITE formatted data:
  │    firstName lastName username password
  │    loanNumber loanAmount interestRate
  │    [type-specific] email phoneNumber
  │         ↓
  │    END FOR
  │         ↓
  │    CLOSE file
  └─ NO → DISPLAY error
  │         ↓
  │    RETURN
  ↓
END
```

### Pseudocode - Student Loan
```
FUNCTION saveStudentLoanData():
    OPEN studentLoanFile in OUTPUT mode
    
    IF NOT file.isOpen():
        RETURN
    
    FOR i = 0 TO size-1:
        cust = customer[i]
        loan = loans[i]
        
        WRITE_TO_FILE (space-separated):
            loan.getFirstName()
            loan.getLastName()
            cust.getUsername()
            cust.getPassword()
            loan.getLoanNumber()
            loan.getLoanAmount()
            loan.getInterestRate()
            loan.getEnrollmentYear()  // Student-specific
            loan.getEmail()
            loan.getPhoneNumber()
    
    CLOSE file
END FUNCTION
```

### Pseudocode - Personal Loan
```
FUNCTION savePersonalLoanData():
    OPEN personalLoanFile in OUTPUT mode
    
    IF NOT file.isOpen():
        RETURN
    
    FOR i = 0 TO size-1:
        cust = customer[i]
        loan = loans[i]
        
        WRITE_TO_FILE (space-separated):
            loan.getFirstName()
            loan.getLastName()
            cust.getUsername()
            cust.getPassword()
            loan.getLoanNumber()
            loan.getLoanAmount()
            loan.getInterestRate()
            loan.getDuration()  // Personal-specific (years)
            loan.getEmail()
            loan.getPhoneNumber()
    
    CLOSE file
END FUNCTION
```

### File Format

**Student Loan Data:**
```
FirstName LastName Username Password LoanNumber Amount Rate EnrollmentYear Email Phone
```

**Personal Loan Data:**
```
FirstName LastName Username Password LoanNumber Amount Rate Duration Email Phone
```

### Time Complexity
- O(n) - Must write all n loans

---

## Load Loan Data Algorithm

### Purpose
Read loan records from file at program initialization.

### Flowchart Logic
```
START
  ↓
ALLOCATE arrays for loans and customers
  ↓
INITIALIZE all elements to nullptr
  ↓
OPEN loan file for reading
  ↓
IF file opened?
  ├─ YES → SET index = 0
  │         ↓
  │    WHILE NOT end of file AND index < size
  │      ↓
  │      READ line
  │      ↓
  │      PARSE line into variables
  │      ↓
  │      CREATE Customer object
  │      ↓
  │      CREATE Loan object
  │      ↓
  │      STORE in arrays
  │      ↓
  │      INCREMENT index
  │      ↓
  │    END WHILE
  │         ↓
  │    CLOSE file
  └─ NO → DISPLAY error
  │         ↓
  │    RETURN
  ↓
END
```

### Pseudocode - Student Loan
```
FUNCTION loadStudentLoanData(filename, size):
    // Allocate arrays
    customers = NEW Customer*[size]
    loans = NEW StudentFeeLoan*[size]
    
    // Initialize
    FOR i = 0 TO size-1:
        customers[i] = nullptr
        loans[i] = nullptr
    
    OPEN filename FOR INPUT
    
    IF NOT file.isOpen():
        DISPLAY "Failed to open file"
        RETURN
    
    index = 0
    WHILE getline(file, line) AND index < size:
        CREATE stringstream from line
        
        // Parse data
        READ firstName, lastName
        READ username, password
        READ loanNumber, loanAmount, interestRate
        READ enrollmentYear
        READ email, phoneNumber
        
        // Create objects
        customers[index] = NEW Customer(username, password)
        loans[index] = NEW StudentFeeLoan(firstName, lastName, loanNumber,
                                           loanAmount, interestRate,
                                           enrollmentYear, email, phoneNumber)
        
        index++
    
    CLOSE file
END FUNCTION
```

### Pseudocode - Personal Loan
```
FUNCTION loadPersonalLoanData(filename, size):
    customers = NEW Customer*[size]
    loans = NEW PersonalLoan*[size]
    
    FOR i = 0 TO size-1:
        customers[i] = nullptr
        loans[i] = nullptr
    
    OPEN filename FOR INPUT
    
    IF NOT file.isOpen():
        DISPLAY "Failed to open file"
        RETURN
    
    index = 0
    WHILE getline(file, line) AND index < size:
        CREATE stringstream from line
        
        READ firstName, lastName
        READ username, password
        READ loanNumber, loanAmount, interestRate
        READ loanDuration  // in years
        READ email, phoneNumber
        
        customers[index] = NEW Customer(username, password)
        loans[index] = NEW PersonalLoan(firstName, lastName, loanNumber,
                                         loanAmount, interestRate,
                                         loanDuration, email, phoneNumber)
        
        index++
    
    CLOSE file
END FUNCTION
```

### Error Handling
- File existence check
- Parse error handling
- Boundary checking
- nullptr initialization

### Time Complexity
- O(n) - Read all n loans

---

## Performance Summary

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Calculate Interest | O(n) | O(1) | Linear search |
| Add Loan | O(1) per loan | O(n) total | Append operation |
| Update Loan | O(n) | O(1) | Search + update |
| Search Loan | O(n) | O(1) | With authentication |
| Delete Loan | O(n) | O(1) | Search + shift |
| Save Data | O(n) | O(1) | Write all records |
| Load Data | O(n) | O(n) | Read all records |

## Interest Calculation Examples

### Student Fee Loan
```
Loan Amount: $50,000
Interest Rate: 3.5%
Duration: 4 years (implicit)

Annual Interest = $50,000 × 0.035 = $1,750
Total Interest = $1,750 × 4 = $7,000
```

### Personal Loan
```
Loan Amount: $20,000
Interest Rate: 7.5%
Duration: 5 years

Annual Interest = $20,000 × 0.075 = $1,500
Total Interest = $1,500 × 5 = $7,500
```

## Optimization Opportunities

1. **Indexing**: Create hash map for O(1) loan lookup
2. **Caching**: Cache frequently accessed loans
3. **Batch Updates**: Group file operations
4. **Compound Interest**: Implement more complex interest calculations
5. **Amortization**: Add payment schedule generation
6. **Validation**: Strengthen input validation
7. **Audit Trail**: Log all loan modifications