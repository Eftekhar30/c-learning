# Investment Management System - Algorithms Documentation

## Table of Contents
1. [Calculate Returns Algorithm](#calculate-returns-algorithm)
2. [Add Investment Algorithm](#add-investment-algorithm)
3. [Update Investment Algorithm](#update-investment-algorithm)
4. [Search Investment Algorithm](#search-investment-algorithm)
5. [Delete Investment Algorithm](#delete-investment-algorithm)
6. [Save Investment Data Algorithm](#save-investment-data-algorithm)
7. [Load Investment Data Algorithm](#load-investment-data-algorithm)
8. [Display Investment Algorithm](#display-investment-algorithm)

---

## Calculate Returns Algorithm

### Purpose
Calculate and display investment returns based on a fixed return rate (5% default).

### Flowchart Logic
```
START
  ↓
INPUT investment ID
  ↓
SEARCH for investment in array
  ↓
IF investment found?
  ├─ YES → Authenticate user
  │         ↓
  │    IF login successful?
  │      ├─ YES → GET investment amount
  │      │         ↓
  │      │    CALCULATE returns:
  │      │    returns = investmentAmount × 0.05
  │      │         ↓
  │      │    DISPLAY result
  │      └─ NO → DISPLAY "Login failed"
  └─ NO → DISPLAY "Investment not found"
  ↓
END
```

### Pseudocode
```
FUNCTION calculateReturns():
    INPUT investmentID
    found = FALSE
    investmentIndex = -1
    
    // Search for investment
    FOR i = 0 TO size-1:
        IF investments[i].investmentID == investmentID:
            IF customer[i].login():
                found = TRUE
                investmentIndex = i
                BREAK
    
    IF found:
        // Get investment amount
        investmentAmount = investments[investmentIndex].getInvestmentAmount()
        
        // Calculate returns (5% fixed rate)
        returns = investmentAmount * 0.05
        
        DISPLAY "Total return on your investment is $" + returns
    ELSE:
        DISPLAY "Investment ID not found"
END FUNCTION
```

### Return Calculation Formula

**Simple Returns Formula:**
```
Returns = Investment Amount × Return Rate

Where:
- Investment Amount = Principal invested
- Return Rate = 0.05 (5% fixed)

Total Value = Investment Amount + Returns
```

### Example Calculation
```
Investment Amount: $10,000
Return Rate: 5%

Returns = $10,000 × 0.05
Returns = $500

Total Value = $10,000 + $500 = $10,500
```

### Time Complexity
- **Search**: O(n)
- **Calculation**: O(1)
- **Total**: O(n)

### Space Complexity
- O(1) - Only temporary variables

---

## Add Investment Algorithm

### Purpose
Register a new investment account with relative beneficiary information.

### Flowchart Logic
```
START
  ↓
OPEN investment file in append mode
  ↓
IF file opened successfully?
  ├─ YES → DO
  │         ↓
  │    INPUT investment details:
  │    - First name, Last name
  │    - Username, Password
  │    - Investment ID
  │    - Investment amount
  │    - Relative name
  │    - Risk level
  │    - Email, Phone number
  │         ↓
  │    CREATE new Customer object
  │         ↓
  │    CREATE new RelativeInvestment object
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

### Pseudocode
```
FUNCTION addInvestment():
    OPEN investmentFile in APPEND mode
    
    IF NOT file.isOpen():
        DISPLAY "File not open!"
        RETURN
    
    DO:
        // Input investor information
        INPUT firstName, lastName
        INPUT username, password
        INPUT riskLevel  // Low, Medium, High
        INPUT investmentID
        INPUT investmentAmount
        INPUT email
        INPUT relativeName  // Beneficiary name
        INPUT phoneNumber
        
        // Validate inputs
        IF investmentAmount <= 0:
            DISPLAY "Invalid amount"
            CONTINUE
        
        IF riskLevel NOT IN ["Low", "Medium", "High"]:
            DISPLAY "Invalid risk level"
            CONTINUE
        
        // Create new objects
        customer[size] = NEW Customer(username, password)
        investments[size] = NEW RelativeInvestment(firstName, lastName,
                                                     investmentID,
                                                     investmentAmount,
                                                     relativeName,
                                                     riskLevel,
                                                     email, phoneNumber)
        
        size++
        
        DISPLAY "Investment registered at [timestamp]"
        
        INPUT "Add another? (Y/N)" → choice
    WHILE choice == 'Y' OR choice == 'y'
    
    // Write all new records
    FOR i = size-1 TO size-1:  // Just the new one
        WRITE investment data to file
    
    CLOSE file
END FUNCTION
```

### Data Validation Rules

| Field | Validation Rule |
|-------|----------------|
| Investment Amount | > 0 |
| Risk Level | Must be "Low", "Medium", or "High" |
| Investment ID | Unique, positive integer |
| Email | Valid email format |
| Phone Number | Valid phone format |
| Relative Name | Not empty |

### Time Complexity
- **Per Investment**: O(1)
- **For n investments**: O(n)

### Space Complexity
- O(n) - New objects for each investment

---

## Update Investment Algorithm

### Purpose
Modify existing investment details including beneficiary information.

### Flowchart Logic
```
START
  ↓
DISPLAY all investments
  ↓
INPUT investment ID to update
  ↓
SEARCH for investment
  ↓
IF investment found?
  ├─ YES → DISPLAY current details
  │         ↓
  │    INPUT new values for all fields:
  │    - First name, Last name
  │    - Username, Password
  │    - Investment ID
  │    - Investment amount
  │    - Relative name
  │    - Risk level
  │    - Email, Phone number
  │         ↓
  │    UPDATE all fields using setters
  │         ↓
  │    SAVE data to file
  │         ↓
  │    DISPLAY "Updated at [timestamp]"
  └─ NO → DISPLAY "Investment not found"
  ↓
END
```

### Pseudocode
```
FUNCTION updateInvestment():
    CALL display()  // Show all investments
    
    INPUT investmentID
    found = FALSE
    updateIndex = -1
    
    // Search for investment
    FOR i = 0 TO size-1:
        IF investments[i].investmentID == investmentID:
            // Display current information
            DISPLAY investments[i].getFirstName() + " " + investments[i].getLastName()
            DISPLAY "Username: " + customer[i].getUsername()
            DISPLAY "Investment ID: " + investments[i].investmentID
            DISPLAY "Amount: $" + investments[i].investmentAmount
            DISPLAY "Relative: " + investments[i].relativeName
            DISPLAY "Email: " + investments[i].getEmail()
            DISPLAY "Phone: " + investments[i].getPhoneNumber()
            
            found = TRUE
            updateIndex = i
            BREAK
    
    IF found:
        // Input new values
        INPUT newFirstName, newLastName
        INPUT newUsername, newPassword
        INPUT newRelativeName
        INPUT newInvestmentID
        INPUT newInvestmentAmount
        INPUT newRiskLevel
        INPUT newEmail, newPhoneNumber
        
        // Update using setter methods
        investments[updateIndex].setFirstName(newFirstName)
        investments[updateIndex].setLastName(newLastName)
        customer[updateIndex].setUsername(newUsername)
        customer[updateIndex].setPassword(newPassword)
        investments[updateIndex].setRiskLevel(newRiskLevel)
        investments[updateIndex].setRelativeName(newRelativeName)
        investments[updateIndex].setInvestmentID(newInvestmentID)
        investments[updateIndex].setInvestmentAmount(newInvestmentAmount)
        investments[updateIndex].setEmail(newEmail)
        investments[updateIndex].setPhoneNumber(newPhoneNumber)
        
        DISPLAY "Account updated at [timestamp]"
        CALL saveInvestmentData()
    ELSE:
        DISPLAY "Investment not found"
END FUNCTION
```

### Update Validation
- Verify new investment ID is unique
- Validate new amount > 0
- Check risk level is valid
- Confirm all required fields present

### Time Complexity
- **Search**: O(n)
- **Update**: O(1)
- **Save**: O(n)
- **Total**: O(n)

---

## Search Investment Algorithm

### Purpose
Find and display specific investment details with authentication.

### Flowchart Logic
```
START
  ↓
INPUT investment ID
  ↓
SET found = FALSE
  ↓
FOR each investment in array
  ↓
  IF investment ID matches?
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
  ├─ YES → DISPLAY investment details:
  │         - Name
  │         - Username
  │         - Investment ID
  │         - Investment amount
  │         - Relative name
  │         - Risk level
  │         - Email, Phone
  └─ NO → DISPLAY "Investment not found"
  ↓
END
```

### Pseudocode
```
FUNCTION searchInvestment():
    INPUT investmentID
    found = FALSE
    investmentIndex = -1
    
    // Search with authentication
    FOR i = 0 TO size-1:
        IF investments[i].investmentID == investmentID:
            IF customer[i].login():
                found = TRUE
                investmentIndex = i
                BREAK  // Found and authenticated
    
    IF found:
        inv = investments[investmentIndex]
        cust = customer[investmentIndex]
        
        DISPLAY "Name: " + inv.getFirstName() + " " + inv.getLastName()
        DISPLAY "Username: " + cust.getUsername()
        DISPLAY "Investment ID: " + inv.investmentID
        DISPLAY "Investment Amount: $" + inv.investmentAmount
        DISPLAY "Relative Name: " + inv.relativeName
        DISPLAY "Risk Level: " + inv.getRiskLevel()
        DISPLAY "Email: " + inv.getEmail()
        DISPLAY "Phone: " + inv.getPhoneNumber()
    ELSE:
        DISPLAY "Investment not found or authentication failed"
END FUNCTION
```

### Security Features
- Requires customer authentication
- Only account owner can view details
- Login verification before display
- Failed login doesn't reveal if investment exists

### Time Complexity
- O(n) - Linear search with authentication

---

## Delete Investment Algorithm

### Purpose
Remove an investment from the system with admin authorization.

### Flowchart Logic
```
START
  ↓
VERIFY admin login
  ↓
IF admin authenticated?
  ├─ YES → DISPLAY all investments
  │         ↓
  │    INPUT investment ID to delete
  │         ↓
  │    SEARCH for investment
  │         ↓
  │    IF investment found?
  │      ├─ YES → DISPLAY investment details
  │      │         ↓
  │      │    CONFIRM deletion (Y/N)
  │      │         ↓
  │      │    IF confirmed?
  │      │      ├─ YES → DELETE customer object
  │      │      │         ↓
  │      │      │    DELETE investment object
  │      │      │         ↓
  │      │      │    SHIFT remaining elements
  │      │      │         ↓
  │      │      │    DECREMENT size
  │      │      │         ↓
  │      │      │    SAVE data
  │      │      │         ↓
  │      │      │    DISPLAY success
  │      │      └─ NO → DISPLAY "Cancelled"
  │      └─ NO → DISPLAY "Not found"
  └─ NO → DISPLAY "Auth failed"
  ↓
END
```

### Pseudocode
```
FUNCTION deleteInvestment(filename, currentSize):
    // Require admin authentication
    IF NOT admin.login():
        DISPLAY "Authentication failed"
        RETURN
    
    CALL display()  // Show all investments
    
    INPUT investmentID
    found = FALSE
    deleteIndex = -1
    
    // Search for investment
    FOR i = 0 TO size-1:
        IF investments[i].investmentID == investmentID:
            // Display details for confirmation
            DISPLAY "Account Found"
            DISPLAY investments[i].getDetails()
            
            found = TRUE
            deleteIndex = i
            BREAK
    
    IF found:
        INPUT "Enter Y to delete" → confirmation
        
        IF confirmation == 'Y' OR confirmation == 'y':
            // Free memory
            DELETE customer[deleteIndex]
            DELETE investments[deleteIndex]
            
            // Shift array left
            FOR i = deleteIndex TO size-2:
                customer[i] = customer[i+1]
                investments[i] = investments[i+1]
            
            size--
            
            CALL saveInvestmentData()
            DISPLAY "Investment deleted at [timestamp]"
        ELSE:
            DISPLAY "Deletion cancelled"
    ELSE:
        DISPLAY "Investment not found"
END FUNCTION
```

### Safety Measures
1. **Admin-only**: Prevents unauthorized deletion
2. **Display first**: Shows what will be deleted
3. **Confirmation**: Requires explicit yes
4. **Audit trail**: Logs timestamp of deletion

### Time Complexity
- **Authentication**: O(1)
- **Search**: O(n)
- **Delete & Shift**: O(n)
- **Save**: O(n)
- **Total**: O(n)

### Memory Management
```cpp
// Proper cleanup sequence
delete customer[deleteIndex];      // Free customer object
delete investments[deleteIndex];   // Free investment object

// Shift pointers (not objects)
for (int i = deleteIndex; i < size-1; i++) {
    customer[i] = customer[i+1];       // Move pointer
    investments[i] = investments[i+1]; // Move pointer
}

size--;  // Update count
```

---

## Save Investment Data Algorithm

### Purpose
Persist all investment records to file storage.

### Flowchart Logic
```
START
  ↓
OPEN investment file in output mode
  ↓
IF file opened?
  ├─ YES → FOR each investment (i = 0 to size-1)
  │         ↓
  │    GET customer[i] data
  │         ↓
  │    GET investment[i] data
  │         ↓
  │    WRITE formatted data:
  │    firstName lastName username password
  │    investmentID amount relativeName
  │    riskLevel email phoneNumber
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

### Pseudocode
```
FUNCTION saveInvestmentData():
    OPEN investmentFile in OUTPUT mode
    
    IF NOT file.isOpen():
        RETURN  // Silent fail (could log error)
    
    // Write all investment records
    FOR i = 0 TO size-1:
        cust = customer[i]
        inv = investments[i]
        
        WRITE_TO_FILE (space-separated with formatting):
            LEFT_ALIGN(20) inv.getFirstName()
            LEFT_ALIGN(20) inv.getLastName()
            LEFT_ALIGN(20) cust.getUsername()
            LEFT_ALIGN(20) cust.getPassword()
            LEFT_ALIGN(20) inv.getInvestmentID()
            LEFT_ALIGN(20) inv.getInvestmentAmount()
            LEFT_ALIGN(30) inv.getRelativeName()
            LEFT_ALIGN(25) inv.getRiskLevel()
            LEFT_ALIGN(30) inv.getEmail()
            LEFT_ALIGN(30) inv.getPhoneNumber()
            NEWLINE
    
    CLOSE file
END FUNCTION
```

### File Format
```
FirstName LastName Username Password InvestmentID Amount RelativeName RiskLevel Email Phone
```

### Example File Content
```
John          Smith         jsmith123   pass123   1001    10000   JaneDoe          Low       john@email.com     555-1234
Mary          Johnson       mjohn456    pass456   1002    25000   RobertJohnson    Medium    mary@email.com     555-5678
```

### Time Complexity
- O(n) - Must write all n investments

### Data Formatting
- Left-aligned columns
- Fixed-width spacing
- Space-separated values
- One record per line

---

## Load Investment Data Algorithm

### Purpose
Read investment records from file at program initialization.

### Flowchart Logic
```
START
  ↓
ALLOCATE arrays for investments and customers
  ↓
INITIALIZE all elements to nullptr
  ↓
OPEN investment file for reading
  ↓
IF file opened?
  ├─ YES → SET index = 0
  │         ↓
  │    WHILE NOT end of file AND index < size
  │      ↓
  │      READ line from file
  │      ↓
  │      PARSE line into variables:
  │      firstName, lastName, username, password
  │      investmentID, amount, relativeName
  │      riskLevel, email, phoneNumber
  │      ↓
  │      CREATE Customer object
  │      ↓
  │      CREATE RelativeInvestment object
  │      ↓
  │      STORE in arrays at index
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

### Pseudocode
```
FUNCTION loadInvestmentData(filename, size):
    // Allocate dynamic arrays
    customers = NEW Customer*[size]
    investments = NEW RelativeInvestment*[size]
    
    // Initialize to null
    FOR i = 0 TO size-1:
        customers[i] = nullptr
        investments[i] = nullptr
    
    OPEN filename FOR INPUT
    
    IF NOT file.isOpen():
        DISPLAY "Failed to open investment data file"
        RETURN
    
    index = 0
    WHILE getline(file, line) AND index < size:
        CREATE stringstream SS from line
        
        // Parse all fields
        SS >> firstName >> lastName
        SS >> username >> password
        SS >> investmentID >> investmentAmount
        SS >> relativeName
        SS >> riskLevel
        SS >> email >> phoneNumber
        
        // Create objects
        customers[index] = NEW Customer(username, password)
        investments[index] = NEW RelativeInvestment(firstName, lastName,
                                                     investmentID,
                                                     investmentAmount,
                                                     relativeName,
                                                     riskLevel,
                                                     email, phoneNumber)
        
        index++
        
        // Safety check
        IF index >= size:
            BREAK
    
    CLOSE file
END FUNCTION
```

### Error Handling
- File existence verification
- Parse error handling
- Boundary checking (index < size)
- nullptr initialization
- Format validation

### Time Complexity
- O(n) - Read all n investments

### Space Complexity
- O(n) - Allocate arrays and objects

---

## Display Investment Algorithm

### Purpose
Show formatted list of all investments in the system.

### Flowchart Logic
```
START
  ↓
DISPLAY header with title
  ↓
DISPLAY column headers:
- Investment Number
- Name
- Investment Amount
- Relative Info
- Email Address
- Phone Number
- Risk Level
  ↓
FOR each investment (i = 0 to size-1)
  ↓
  DISPLAY formatted row:
  - investmentID
  - firstName + lastName
  - investmentAmount
  - relativeName
  - email
  - phoneNumber
  - riskLevel
  ↓
END FOR
  ↓
END
```

### Pseudocode
```
FUNCTION display():
    DISPLAY "============Investment Type: Relative Investment============="
    
    // Display column headers
    DISPLAY LEFT_ALIGN(15) "Investment NO"
    DISPLAY LEFT_ALIGN(18) "Name"
    DISPLAY LEFT_ALIGN(20) "Investment Amount"
    DISPLAY LEFT_ALIGN(20) "Relative Info"
    DISPLAY LEFT_ALIGN(30) "Email Address"
    DISPLAY LEFT_ALIGN(30) "Phone No."
    DISPLAY LEFT_ALIGN(20) "Risk Level"
    DISPLAY NEWLINE
    
    // Display each investment
    FOR i = 0 TO size-1:
        inv = investments[i]
        
        DISPLAY LEFT_ALIGN(15) inv.getInvestmentID()
        DISPLAY LEFT_ALIGN(18) inv.getFirstName() + " " + inv.getLastName()
        DISPLAY LEFT_ALIGN(20) "$" + inv.getInvestmentAmount()
        DISPLAY LEFT_ALIGN(20) inv.getRelativeName()
        DISPLAY LEFT_ALIGN(30) inv.getEmail()
        DISPLAY LEFT_ALIGN(30) inv.getPhoneNumber()
        DISPLAY LEFT_ALIGN(20) inv.getRiskLevel()
        DISPLAY NEWLINE
END FUNCTION
```

### Display Format Example
```
============Investment Type: Relative Investment=============
Investment NO  Name              Investment Amount Relative Info        Email Address                  Phone No.                      Risk Level
1001           John Smith        $10000           Jane Doe             john@email.com                 555-1234                       Low
1002           Mary Johnson      $25000           Robert Johnson       mary@email.com                 555-5678                       Medium
1003           Bob Wilson        $50000           Alice Wilson         bob@email.com                  555-9012                       High
```

### Time Complexity
- O(n) - Display all n investments

---

## Performance Summary

| Operation | Time Complexity | Space Complexity | Authentication Required |
|-----------|-----------------|------------------|------------------------|
| Calculate Returns | O(n) | O(1) | Yes (User) |
| Add Investment | O(1) per record | O(n) total | No |
| Update Investment | O(n) | O(1) | No (Admin portal) |
| Search Investment | O(n) | O(1) | Yes (User) |
| Delete Investment | O(n) | O(1) | Yes (Admin) |
| Save Data | O(n) | O(1) | No |
| Load Data | O(n) | O(n) | No |
| Display | O(n) | O(1) | No |

## Investment Return Calculations

### Fixed Rate Returns (Current Implementation)
```
Returns = Investment Amount × 0.05
Return Rate = 5%

Example:
Investment: $10,000
Returns: $10,000 × 0.05 = $500
Total Value: $10,500
```

### Risk Level Impact (Future Enhancement)
```
Returns based on risk level:
- Low Risk: 3% return
- Medium Risk: 5% return
- High Risk: 8% return

High Risk Example:
Investment: $10,000
Returns: $10,000 × 0.08 = $800
Total Value: $10,800
```

### Compound Returns (Future Enhancement)
```
A = P(1 + r/n)^(nt)

Where:
A = Final amount
P = Principal (initial investment)
r = Annual interest rate (decimal)
n = Compounds per year
t = Time in years

Example (5% compounded annually for 5 years):
A = $10,000(1 + 0.05/1)^(1×5)
A = $10,000(1.05)^5
A = $10,000 × 1.2763
A = $12,763
```

## Data Relationships

```
RelativeInvestment
├── Customer (Account holder)
│   ├── username
│   └── password
├── Investment Details
│   ├── investmentID
│   ├── investmentAmount
│   └── riskLevel
└── Beneficiary
    └── relativeName
```

## Optimization Opportunities

1. **Hash Map Lookup**: O(1) investment search by ID
2. **Risk-based Returns**: Variable return rates
3. **Compound Interest**: More realistic calculations
4. **Portfolio View**: Aggregate investor holdings
5. **Historical Tracking**: Track value over time
6. **Rebalancing**: Automatic risk management
7. **Reporting**: Generate investment statements
8. **Tax Calculations**: Integrate tax implications

## Security Considerations

1. **Authentication**: User login for viewing
2. **Authorization**: Admin-only deletion
3. **Data Privacy**: Beneficiary information protected
4. **Audit Trail**: Log all modifications
5. **Encryption**: Consider encrypting sensitive data
6. **Validation**: Prevent negative amounts
7. **Session Management**: Timeout inactive sessions