# Apex Ledger - Banking Management System

Console based BMS (Banking-Management-System) using C++
A CLI banking management system using C++, OOP principles, and file I/O for data persistence.
This project demonstrates fundamental banking operations with secure multi-tiered access control.

## Technologies Used

* C++ (Standard Library)
* File I/O for data persistence (.csv files)
* Object-Oriented Programming (OOP) principles

## Key Features

* **Tiered Access Control**: Implements secure separation of duties for Customer, Staff, and Manager modes, each with distinct permissions.
* **Data Persistence (File I/O):** All customer and employee data is dynamically loaded from and saved to dedicated `.csv` files upon program launch and exit.
* **Object-Oriented Design (OOP):** Built around separate, encapsulated classes (`BankAccount`, `Employee`, `Manager`) for modular, reusable, and maintainable code.
* **Full CRUD Functionality:** Supports Create, Read, Update, and Delete operations on both customer accounts and employee records.
* **Unique ID Generation:** Uses static member variables and file I/O to ensure account and employee IDs are unique and sequential across multiple program sessions.
* **Clean Architecture:** Functions are organized across multiple source (`.cpp`) and header (`.h`) files for clarity and maintainability.

## Instructions for Setup & Execution:-

1. Clone the repository to your local device.
2. Navigate to the project directory.
3. Compile the C++ files using a compiler (e.g. g++):-
   Use this command in terminal/cmd:
   g++ src/*.cpp -o output/bank_app
4. Run the compiled executable (bank_app.exe) to start the banking management system.

## Issues and Future Roadmap for V2.0:-

This project is fully functional (V1.0) but has planned architectural improvements. Contributors are welcome!

* String Input Validation: add input specific parsing functions, for fields like date, email.[WORKING]

* Enable Wrong Password Count: if limit reached, account lockout after n failed attempts. [PLANNED]

* Concurrency Handling: Implement file locks or database transactions to manage simultaneous access in multi-user environments. [PLANNED]

* Database Integration: Replace File I/O (.csv files) with a proper database connection for scalable data handling. [PLANNED]

* GUI Interface: Develop a graphical user interface (GUI) for improved user experience over the command-line interface, using Qt or Iamgui. [IN_PROGRESS]

## Functionality Overview

* Create and manage bank accounts.
* Deposit and withdraw funds.
* View account details and transaction history.
* Employee management (add, view, remove employees).
* Managerial oversight (view all accounts, employees, and balancesheet).
* Simple and user-friendly command-line interface.

## License

This project is licensed under the MIT License, see the LICENSE file for details.

For any queries or contributions, please contact <codedbykush3@gmail.com>.
