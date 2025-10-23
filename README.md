# 📚 CyberEX Library Management System (C++)

A simple **command-line library management system** written in C++.  
It allows users to **add**, **borrow**, and **return** books using plain text file storage — no database required.

---

## 🧠 Overview

This program simulates a small-scale library system that manages book records through files:

- `books.txt` — contains available books.  
- `borrowed_books.txt` — contains borrowed books.  
- `temp.txt` — used internally for safe file updates.

Users can:
- Add new books to the collection.
- Borrow a book (moves it from `books.txt` to `borrowed_books.txt`).
- Return a book (moves it back to `books.txt`).
- View book lists dynamically from files.

---

## ⚙️ Features

| Feature | Description |
|----------|--------------|
| ➕ **Add Books** | Add one or multiple books with unique IDs and names. |
| 📖 **Borrow Book** | Select a book by ID to borrow; removes it from the available list. |
| 🔁 **Return Book** | Return a borrowed book; restores it to the available list. |
| 💾 **Persistent Storage** | All data is stored in `.txt` files (no data loss between runs). |
| 🧩 **Menu-Driven Interface** | Simple text-based navigation with numeric options. |

🗂️ File Structure
📁 CyberEX-Library/
├── main.cpp # Main program

├── books.txt # Available books (auto-created)

├── borrowed_books.txt # Borrowed books (auto-created)

├── temp.txt # Temporary file for safe updates

└── README.md # Project documentation


Menu Options
1. Borrow Book
2. Return Book
3. Add Book
4. Quit

Example flow:

Add books → creates books.txt

Borrow a book → moves it to borrowed_books.txt

Return a book → moves it back to books.txt

🧩 Example Files

books.txt

101 C++ Programming
102 Data Structures
103 Algorithms Unlocked


borrowed_books.txt

101 C++ Programming

🧠 Key Concepts Used

File I/O (ifstream, ofstream)

String handling with getline

Condition checking and control flow

Array-based user input

Safe file replacement using temp files

Simple menu-driven logic

🧱 Future Enhancements

Add user authentication

Use classes and OOP structure

Replace text files with SQLite or JSON storage

Add search and delete functionality

🧑‍💻 Author

Mohsan CyberEX
Cyber Security Student & C++ Learner
📘 "Building engineers who reason from first principles."

🪪 License

This project is open-source and free to use for educational purposes.


## 🚀 How to Run

### 1. Compile the Code
Using g++
```bash
g++ main.cpp -o library
./library
