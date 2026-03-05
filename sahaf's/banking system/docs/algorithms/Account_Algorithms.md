# Account Management System - Algorithms Documentation

## Table of Contents
1. [Deposit Algorithm](#deposit-algorithm)
2. [Withdrawal Algorithm](#withdrawal-algorithm)
3. [Add Account Algorithm](#add-account-algorithm)
4. [Update Account Algorithm](#update-account-algorithm)
5. [Delete Account Algorithm](#delete-account-algorithm)
6. [Search Account Algorithm](#search-account-algorithm)
7. [Save Account Data Algorithm](#save-account-data-algorithm)
8. [Load Account Data Algorithm](#load-account-data-algorithm)

---

## Deposit Algorithm

### Purpose
Add money to a customer's account after authentication.

### Flowchart Logic
```
START
  ↓
INPUT account number
  ↓
SEARCH for account in array
  ↓
IF account found?
  ├─ YES → Authenticate user
  │         ↓
  │    IF login successful?
  │      ├─ YES → Add amount to balance
  │      │        ↓
  │      │   UPDATE balance
  │      │        ↓
  │      │   SAVE data to file
  │      │        ↓
  │      │   DISPLAY success message
  │      └─ NO → DISPLAY login failed
  └─ NO → DISPLAY account not found
  ↓
END
```

### Pseudocode
```
FUNCTION deposit(amount):
    INPUT accountNumber
    found = FALSE
    accountIndex = -1
    
    FOR i = 0 TO size-1:
        IF accounts[i].accountNumber == accountNumber:
            found = TRUE
            accountIndex = i
            BREAK
    
    IF found:
        IF customer[accountIndex].login():
            accounts[accountIndex].balance += amount
            
            // Apply fee for checking accounts
            IF account type is CheckingAccount:
                amount -= feeCharge
                accounts[accountIndex].balance += amount
            
            DISPLAY "Deposit successful"
            CALL saveAccountData()
        ELSE:
            DISPLAY "Login failed"
    ELSE:
        DISPLAY "Account not found"
END FUNCTION
```

### Time Complexity
- **Best Case**: O(1) - Account found at first position
- **Average Case**: O(n) - Linear search through array
- **Worst Case**: O(n) - Account at end or not found

### Space Complexity
- O(1) - Only temporary variables used

---

## Withdrawal Algorithm

### Purpose
Withdraw money from a customer's account with balance validation.

### Flowchart Logic
```
START
  ↓
INPUT account number
  ↓
SEARCH for account
  ↓
IF account found?
  ├─ YES → Authenticate user
  │         ↓
  │    IF login successful?
  │      ├─ YES → CHECK if balance >= amount
  │      │         ↓
  │      │    IF sufficient balance?
  │      │      ├─ YES → Deduct amount
  │      │      │        ↓
  │      │      │   SAVE data
  │      │      │        ↓
  │      │      │   DISPLAY success
  │      │      └─ NO → THROW InsufficientBalance exception
  │      │                ↓
  │      │           CATCH exception
  │      │                ↓
  │      │           PROMPT for valid amount
  │      │                ↓
  │      │           RETRY withdrawal
  │      └─ NO → DISPLAY login failed
  └─ NO → DISPLAY account not found
  ↓
END
```

### Pseudocode
```
FUNCTION withdraw(amount):
    INPUT accountNumber
    found = FALSE
    accountIndex = -1
    
    FOR i = 0 TO size-1:
        IF accounts[i].accountNumber == accountNumber:
            found = TRUE
            accountIndex = i
            BREAK
    
    IF found:
        IF customer[accountIndex].login():
            TRY:
                IF accounts[accountIndex].balance < amount:
                    THROW InsufficientBalanceException
                ELSE:
                    accounts[accountIndex].balance -= amount
                    
                    // Apply fee for checking accounts
                    IF account type is CheckingAccount:
                        accounts[accountIndex].balance -= feeCharge
                    
                    DISPLAY "Withdrawal successful"
                    CALL saveAccountData()
            CATCH InsufficientBalanceException:
                DISPLAY "Insufficient balance"
                INPUT newAmount
                CALL withdraw(newAmount)  // Recursive retry
        ELSE:
            DISPLAY "Login failed"
    ELSE:
        DISPLAY "Account not found"
END FUNCTION
```

### Time Complexity
- **Search**: O(n)
- **Withdrawal**: O(1)
- **Total**: O(n)

### Error Handling
- Exception thrown for insufficient balance
- Recursive retry mechanism
- Transaction rollback on failure

---

## Add Account Algorithm

### Purpose
Register a new customer account in the system.

### Flowchart Logic
```
START
  ↓
OPEN file in append mode
  ↓
IF file opened successfully?
  ├─ YES → DO
  │         ↓
  │    INPUT customer details:
  │    - First name, Last name
  │    - Username, Password
  │    - Account number
  │    - Initial balance
  │    - Card type
  │    - Email, Phone number
  │         ↓
  │    CREATE new Customer object
  │         ↓
  │    CREATE new Account object
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
FUNCTION addAccount(currentSize):
    OPEN dataFile in APPEND mode
    
    IF file not opened:
        DISPLAY "File open failed"
        RETURN
    
    DO:
        INPUT firstName, lastName
        INPUT username, password
        INPUT cardType
        INPUT accountNumber
        INPUT initialBalance
        INPUT email, phoneNumber
        
        // Create new objects
        customer[size] = NEW Customer(username, password)
        account[size] = NEW Account(firstName, lastName, accountNumber, 
                                     initialBalance, cardType, email, phoneNumber)
        
        // Increment counter
        size++
        
        // Write to file
        WRITE account data to file
        
        DISPLAY "Account registered successfully at [timestamp]"
        
        INPUT "Add another? (Y/N)" → choice
    WHILE choice == 'Y' OR choice == 'y'
    
    CLOSE file
END FUNCTION
```

### Time Complexity
- **Per Account**: O(1) - Direct array access
- **For n accounts**: O(n)

### Space Complexity
- O(n) - New objects created for each account

---

## Update Account Algorithm

### Purpose
Modify existing account information.

### Flowchart Logic
```
START
  ↓
DISPLAY all accounts
  ↓
INPUT account number to update
  ↓
SEARCH for account
  ↓
IF account found?
  ├─ YES → DISPLAY current details
  │         ↓
  │    INPUT new details for each field:
  │    - First name, Last name
  │    - Username, Password
  │    - Card type
  │    - Account number
  │    - Balance
  │    - Email, Phone
  │         ↓
  │    UPDATE all fields using setters
  │         ↓
  │    SAVE data to file
  │         ↓
  │    DISPLAY "Account updated successfully"
  └─ NO → DISPLAY "Account not found"
  ↓
END
```

### Pseudocode
```
FUNCTION updateAccount():
    CALL display()  // Show all accounts
    
    INPUT accountNumber
    found = FALSE
    updateIndex = -1
    
    FOR i = 0 TO size-1:
        IF accounts[i].accountNumber == accountNumber:
            // Display current information
            DISPLAY accounts[i].details
            found = TRUE
            updateIndex = i
            BREAK
    
    IF found:
        // Input new values
        INPUT newFirstName, newLastName
        INPUT newUsername, newPassword
        INPUT newCardType
        INPUT newAccountNumber
        INPUT newBalance
        INPUT newEmail, newPhoneNumber
        
        // Update using setter methods
        customer[updateIndex].setUsername(newUsername)
        customer[updateIndex].setPassword(newPassword)
        accounts[updateIndex].setFirstName(newFirstName)
        accounts[updateIndex].setLastName(newLastName)
        accounts[updateIndex].setCardType(newCardType)
        accounts[updateIndex].setAccountNumber(newAccountNumber)
        accounts[updateIndex].setBalance(newBalance)
        accounts[updateIndex].setEmail(newEmail)
        accounts[updateIndex].setPhoneNumber(newPhoneNumber)
        
        DISPLAY "Account updated successfully"
        CALL saveAccountData()
    ELSE:
        DISPLAY "Account not found"
END FUNCTION
```

### Time Complexity
- **Search**: O(n)
- **Update**: O(1)
- **Save**: O(n) - rewrites entire file
- **Total**: O(n)

---

## Delete Account Algorithm

### Purpose
Remove an account from the system (Admin only).

### Flowchart Logic
```
START
  ↓
VERIFY admin login
  ↓
IF admin authenticated?
  ├─ YES → DISPLAY all accounts
  │         ↓
  │    INPUT account number to delete
  │         ↓
  │    SEARCH for account
  │         ↓
  │    IF account found?
  │      ├─ YES → DISPLAY account details
  │      │         ↓
  │      │    CONFIRM deletion (Y/N)
  │      │         ↓
  │      │    IF confirmed?
  │      │      ├─ YES → DELETE customer object
  │      │      │         ↓
  │      │      │    DELETE account object
  │      │      │         ↓
  │      │      │    SHIFT remaining elements left
  │      │      │         ↓
  │      │      │    DECREMENT size
  │      │      │         ↓
  │      │      │    SAVE data
  │      │      │         ↓
  │      │      │    DISPLAY success with timestamp
  │      │      └─ NO → DISPLAY "Deletion cancelled"
  │      └─ NO → DISPLAY "Account not found"
  └─ NO → DISPLAY "Authentication failed"
  ↓
END
```

### Pseudocode
```
FUNCTION deleteAccount(filename, currentSize):
    IF NOT admin.login():
        DISPLAY "Admin authentication failed"
        RETURN
    
    CALL display()  // Show all accounts
    
    INPUT accountNumber
    found = FALSE
    deleteIndex = -1
    
    FOR i = 0 TO size-1:
        IF accounts[i].accountNumber == accountNumber:
            DISPLAY accounts[i].details
            found = TRUE
            deleteIndex = i
            BREAK
    
    IF found:
        INPUT "Confirm deletion? (Y/N)" → confirmation
        
        IF confirmation == 'Y' OR confirmation == 'y':
            // Delete objects
            DELETE customer[deleteIndex]
            DELETE accounts[deleteIndex]
            
            // Shift elements left
            FOR i = deleteIndex TO size-2:
                customer[i] = customer[i+1]
                accounts[i] = accounts[i+1]
            
            // Decrement size
            size--
            
            CALL saveAccountData()
            DISPLAY "Account deleted at [timestamp]"
        ELSE:
            DISPLAY "Deletion cancelled"
    ELSE:
        DISPLAY "Account not found"
END FUNCTION
```

### Time Complexity
- **Search**: O(n)
- **Shift**: O(n)
- **Save**: O(n)
- **Total**: O(n)

### Space Complexity
- O(1) - In-place deletion

---

## Search Account Algorithm

### Purpose
Find and display specific account information.

### Flowchart Logic
```
START
  ↓
INPUT account number
  ↓
SET found = FALSE
  ↓
FOR each account in array
  ↓
  IF account number matches?
    ├─ YES → SET found = TRUE
    │         ↓
    │    STORE index
    │         ↓
    │    BREAK loop
    └─ NO → CONTINUE
  ↓
IF found?
  ├─ YES → DISPLAY account details:
  │         - Name
  │         - Username
  │         - Account number
  │         - Balance
  │         - Card type
  │         - Email
  │         - Phone number
  └─ NO → DISPLAY "Account not found"
  ↓
END
```

### Pseudocode
```
FUNCTION searchAccount():
    INPUT accountNumber
    found = FALSE
    accountIndex = -1
    
    FOR i = 0 TO size-1:
        IF accounts[i].accountNumber == accountNumber:
            found = TRUE
            accountIndex = i
            BREAK
    
    IF found:
        DISPLAY "Name: " + accounts[accountIndex].getFirstName() + 
                " " + accounts[accountIndex].getLastName()
        DISPLAY "Username: " + customer[accountIndex].getUsername()
        DISPLAY "Account Number: " + accounts[accountIndex].getAccountNumber()
        DISPLAY "Balance: $" + accounts[accountIndex].getBalance()
        DISPLAY "Card Type: " + accounts[accountIndex].getCardType()
        DISPLAY "Email: " + accounts[accountIndex].getEmail()
        DISPLAY "Phone: " + accounts[accountIndex].getPhoneNumber()
    ELSE:
        DISPLAY "Account not found"
END FUNCTION
```

### Time Complexity
- **Linear Search**: O(n)

### Optimization Opportunities
- Use hash table: O(1) average case
- Use binary search tree: O(log n) if sorted
- Implement indexing by account number

---

## Save Account Data Algorithm

### Purpose
Persist all account data to file storage.

### Flowchart Logic
```
START
  ↓
OPEN file in output mode (overwrite)
  ↓
IF file opened successfully?
  ├─ YES → FOR each account (i = 0 to size-1)
  │         ↓
  │    GET customer[i] data
  │         ↓
  │    GET account[i] data
  │         ↓
  │    WRITE formatted data to file:
  │    firstName lastName username password
  │    accountNumber balance cardType
  │    email phoneNumber
  │         ↓
  │    END FOR loop
  │         ↓
  │    CLOSE file
  └─ NO → DISPLAY "Failed to open file"
  │         ↓
  │    RETURN (exit function)
  ↓
END
```

### Pseudocode
```
FUNCTION saveAccountData():
    OPEN dataFile in OUTPUT mode
    
    IF NOT file.isOpen():
        DISPLAY "Failed to open data file"
        RETURN
    
    FOR i = 0 TO size-1:
        customer_data = customer[i]
        account_data = accounts[i]
        
        WRITE_TO_FILE:
            account_data.getFirstName() + " " +
            account_data.getLastName() + " " +
            customer_data.getUsername() + " " +
            customer_data.getPassword() + " " +
            account_data.getAccountNumber() + " " +
            account_data.getBalance() + " " +
            account_data.getCardType() + " " +
            account_data.getEmail() + " " +
            account_data.getPhoneNumber() + "\n"
    
    CLOSE file
END FUNCTION
```

### Time Complexity
- O(n) - Must write all n accounts

### Data Format
```
FirstName LastName Username Password AccountNumber Balance CardType Email PhoneNumber
```

### File Handling
- Overwrites existing file
- Called after every modification
- Ensures data persistence

---

## Load Account Data Algorithm

### Purpose
Read account data from file at program startup.

### Flowchart Logic
```
START
  ↓
SET filename and size
  ↓
ALLOCATE arrays for accounts and customers
  ↓
INITIALIZE all array elements to nullptr
  ↓
OPEN file for reading
  ↓
IF file opened successfully?
  ├─ YES → SET index = 0
  │         ↓
  │    WHILE NOT end of file AND index < size
  │      ↓
  │      READ line from file
  │      ↓
  │      PARSE line into variables:
  │      firstName, lastName, username, password
  │      accountNumber, balance, cardType
  │      email, phoneNumber
  │      ↓
  │      CREATE new Customer object
  │      ↓
  │      CREATE new Account object
  │      ↓
  │      STORE in arrays at index
  │      ↓
  │      INCREMENT index
  │      ↓
  │    END WHILE
  │         ↓
  │    CLOSE file
  └─ NO → DISPLAY "Failed to open file"
  │         ↓
  │    RETURN
  ↓
END
```

### Pseudocode
```
FUNCTION loadAccountData(filename, size):
    // Allocate dynamic arrays
    accounts = NEW Account*[size]
    customers = NEW Customer*[size]
    
    // Initialize to null
    FOR i = 0 TO size-1:
        accounts[i] = nullptr
        customers[i] = nullptr
    
    // Open file
    OPEN filename FOR INPUT
    
    IF NOT file.isOpen():
        DISPLAY "Failed to open file"
        RETURN
    
    index = 0
    WHILE getline(file, line) AND index < size:
        // Parse line
        CREATE stringstream from line
        
        READ firstName, lastName
        READ username, password
        READ accountNumber, balance
        READ cardType, email, phoneNumber
        
        // Create objects
        customers[index] = NEW Customer(username, password)
        accounts[index] = NEW Account(firstName, lastName, accountNumber,
                                       balance, cardType, email, phoneNumber)
        
        index++
    
    CLOSE file
END FUNCTION
```

### Time Complexity
- O(n) - Must read all n accounts

### Error Handling
- File existence check
- Format validation
- Boundary checking (index < size)

---

## Performance Analysis Summary

| Operation | Time Complexity | Space Complexity |
|-----------|-----------------|------------------|
| Deposit | O(n) | O(1) |
| Withdrawal | O(n) | O(1) |
| Add Account | O(1) per account | O(n) total |
| Update Account | O(n) | O(1) |
| Delete Account | O(n) | O(1) |
| Search Account | O(n) | O(1) |
| Save Data | O(n) | O(1) |
| Load Data | O(n) | O(n) |

## Improvement Recommendations

1. **Use Hash Table**: Replace linear search with O(1) lookup
2. **Database**: Replace file I/O with SQL database
3. **Indexing**: Add secondary indices for faster searches
4. **Batch Operations**: Reduce file I/O frequency
5. **Caching**: Keep frequently accessed accounts in memory
6. **Validation**: Add input validation at all entry points
7. **Logging**: Implement transaction logging for audit trail