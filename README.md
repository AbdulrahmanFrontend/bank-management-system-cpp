# Bank Management System (C++)

A **console-based Bank Management System** developed in C++ that simulates core banking workflows for learning and demonstration purposes such as managing client accounts, deposits, withdrawals, and balance inquiries using file-based persistence.

## 🚀 Features
- 🧾 Client account management
- 🔐 Basic authentication logic
- 💰 Banking operations:
  - Deposit funds
  - Withdraw funds
  - Check account balance
- 📂 Persistent storage using file I/O
- 🧠 Input validation and error handling
- 🖥️ Simple and clear console interface

## 🛠️ Tech Stack
- **Language:** C++
- **Standard:** C++11 or later
- **Storage:** Text files (File I/O)
- **Compiler:** GCC / Clang / MSVC

## 📦 Build & Run
Compile and run using any C++ compiler supporting C++11 or later:

```bash
g++ main.cpp -o bank-system -std=c++11
```

Run the application:
```bash
BankClient.slnx
```

## 📁 Project Structure
```css
BankClient/
├── BankClient.cpp
├── Clients.txt
├── README.md
```

## 📌 Client Data Format
```swift
AccountNumber#//#PIN#//#FullName#//#Balance
```

## 🎯 Learning Outcomes

- This project demonstrates:
- Structured programming in C++
- Business logic implementation
- File handling and data persistence
- User interaction and input validation
- Building a complete console-based system

---

## 📌 Project Scope
This project focuses on:
- Core banking logic
- File-based persistence
- Console interaction

It does NOT aim to be:
- A production banking system
- A secure financial application
- A replacement for database-driven systems

---

## 🤝 Contribution
Feel free to fork this repository and enhance its features.
