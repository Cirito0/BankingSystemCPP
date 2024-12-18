# BankingSystemCPP

# Overview
This project is a simple banking system developed in C++ as part of a university assignment. It simulates basic banking operations such as account creation, deposit, withdrawal, transaction generation, and transaction analysis.
The system is built using only the iostream library, focusing on core C++ concepts like object-oriented programming, data structures, and file handling, without relying on any external libraries.


# How to Run
Clone this repository to your local machine.
Open the project folder in a C++ IDE or compile the files using a C++ compiler.
Compile and run client_manager.cpp to create and manage clients, transaction_generator.cpp to generate transactions, and analyst.cpp to analyze transaction data.
Follow the on-screen prompts to interact with the banking system and perform the required operations.


# Example Usage
Create Clients: Use client_manager.cpp to create new clients and assign them accounts.
Generate Transactions: Use transaction_generator.cpp to simulate various transactions like deposits and withdrawals.
Analyze Transactions: Use analyst.cpp to analyze all the transactions and user activity stored in .dat files.
Balance Management: Check account balances after transactions to see the changes made by deposits and withdrawals.

# Features
 Account Creation: Create and manage multiple bank accounts.
Deposit and Withdrawal: Deposit funds into an account and withdraw them, provided the balance is sufficient.
Balance Inquiry: Check the current balance of any account.
Transaction Generation: Simulate and generate transactions for deposits and withdrawals.
Transaction and User Data Analysis: Analyze all transactions and user data stored in .dat files.
Basic Error Handling: Validates inputs, ensuring there are no negative amounts or invalid actions.
Console-based Interface: A simple text-based interface using standard input and output for user interaction.


# File Structure
client_manager.cpp: Manages the creation and details of client accounts. It handles client registration and stores the necessary information.
analyst.cpp: Analyzes all transactions and user data stored in .dat files, providing insights into account activity and transactions.
transaction_generator.cpp: Generates and simulates various transactions such as deposits and withdrawals, modifying client balances accordingly.


# Constraints
This project was developed as part of a university assignment and adheres to the following constraints:
Language: C++.
Libraries: Only the iostream library is used (no external libraries or third-party dependencies).
Focus: Emphasis on basic C++ concepts, object-oriented programming, and managing simple data structures.


# Notes
This banking system is designed to provide a basic understanding of banking operations and account management through programming.
Due to project constraints, advanced features such as encryption, multi-threading, or database integration are not included.
