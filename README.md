# Console-BMS-Banking-Management-System-Cpp

A CLI banking management system using C++, OOP principles, and file I/O for data persistence.
This project demonstrates fundamental banking operations with secure multi-tiered access control.

## Key Features & Technical Highlights

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
   g++ src\*.cpp -o output\bank_app
4. Run the compiled executable (bank_app.exe) to start the banking management system.

## Known Issues and Future Roadmap for V2.0:-

This project is fully functional (V1.0) but has planned architectural improvements. Contributors are welcome!

- Input Validation: Implement do-while loops with robust type-checking (cin.fail()) for all user input (amounts, numbers, IDs) to prevent crashes from non-numeric input.

- Full CRUD: Implement the ability for Managers/Staff to permanently delete and modify existing customer and employee records from the main data vectors.

- Database Integration: Replace File I/O (.csv files) with a proper database connection for scalable and transactional data handling.

- GUI Interface: Develop a graphical user interface (GUI) for improved user experience over the command-line interface.

## Features

- Create and manage bank accounts.

- Deposit and withdraw funds.

- View account details and transaction history.

- Simple and user-friendly command-line interface.

## License

This project is licensed under the MIT License, see the LICENSE file for details.


For any queries or contributions, please contact <codedbykush3@gmail.com>.
