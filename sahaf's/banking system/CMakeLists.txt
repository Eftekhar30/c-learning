cmake_minimum_required(VERSION 3.10)
project(BankManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/Utils.cpp
    src/User.cpp
    src/Customer.cpp
    src/Admin.cpp
    src/Account.cpp
    src/SavingsAccount.cpp
    src/CheckingAccount.cpp
    src/Loan.cpp
    src/StudentFeeLoan.cpp
    src/PersonalLoan.cpp
    src/Investment.cpp
    src/RelativeInvestment.cpp
    src/Main.cpp
)

# Create executable
add_executable(BankManagement ${SOURCES})

# Compiler warnings
if(MSVC)
    target_compile_options(BankManagement PRIVATE /W4)
else()
    target_compile_options(BankManagement PRIVATE -Wall -Wextra -pedantic)
endif()

# Set output directory
set_target_properties(BankManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Create data directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/data)

# Copy data files if they exist
if(EXISTS ${CMAKE_SOURCE_DIR}/data)
    file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
endif()

# Print build information
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")