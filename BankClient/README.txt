# 🏦 Bank Management System (C++ OOP)

A comprehensive, console-based Bank Management System built with **Modern C++**. This project demonstrates advanced Object-Oriented Programming (OOP) concepts, file handling, and a robust permission-based security system.

## 🚀 Key Features

* **User Management:** Full CRUD operations for system users.
* **Client Management:** Manage bank clients (Add, Delete, Update, Find).
* **Transaction System:**
    * Deposit and Withdraw.
    * Transfer funds between accounts with real-time balance validation.
    * Detailed **Transfer Log** for auditing.
* **Security & Permissions:**
    * Secure Login system with 3-trial lockout.
    * Fine-grained permissions (Bit-masking) for each user.
    * **Login Register** to track user access history.
* **Currency Exchange System:**
    * Update currency rates.
    * Automated Currency Calculator for international transfers.
* **Utility Library:** Custom-built classes for Input Validation, String Manipulation, and Date/Time handling.

## 🏗️ System Architecture

The project follows a modular architecture:
- **Core Logic:** Classes like `clsBankClient`, `clsUser`, and `clsCurrency` handle data and business rules.
- **Presentation Layer:** Each screen is encapsulated in its own class (e.g., `clsMainScreen`, `clsTransferScreen`) inherited from a base `clsScreen`.
- **Data Layer:** Flat-file database system (`.txt` files) with specialized parsing logic.



## 🛠️ Technical Stack

- **Language:** C++
- **Concepts:** Inheritance, Polymorphism, Encapsulation, Abstraction.
- **Advanced Techniques:** Templates, Bitwise Permissions, Static Methods, File I/O.
- **Environment:** Designed for Windows (uses `system("cls")` and `system("pause")`).

## 📂 Project Structure

- `clsPerson.h`: The base class for both Clients and Users.
- `clsBankClient.h`: Logic for bank account operations.
- `clsUser.h`: Logic for user roles and permissions.
- `clsInputValidate.h`: Template-based robust input validation.
- `Screens/`: A directory (or logical split) containing all UI logic.

## 🎮 How to Run

1.  Clone the repository: `git clone https://github.com/YourUsername/BankSystem.git`
2.  Open the project in **Visual Studio** or any C++ IDE.
3.  Ensure `Clients.txt`, `Users.txt`, `Currencies.txt`, and other log files are in the executable directory.
4.  Compile and Run `BankClient.cpp`.

## 👤 Author

**[اسمك هنا]**
- LinkedIn: [رابط حسابك]
- Portfolio: [رابط معرض أعمالك]

---
*Generated as part of the Programming Advices course requirements.*