# Smart Digital Identity Verification System

A console-based Digital Identity Verification System built in modern C++ (C++17), simulating a real-world citizen identity management platform. Citizens can register, log in, manage their profile, and apply for identity verification. Administrators can review citizens, verify or reject identities, search records, delete accounts, and generate/export reports — all backed by simple, transparent text-file storage.

This project was built as a final-year / college-level demonstration of Object-Oriented Programming, modular software architecture, and file-based data persistence in C++.

---

## Features

### Citizen Features
- Registration with full validation (name, age, gender, DOB, mobile, email, Aadhaar, address, password, security question/answer)
- Auto-generated Citizen ID and Registration Date
- Secure login with masked password input and a 3-attempt limit
- Forgot Password recovery flow (Email → Security Question → Security Answer → New Password)
- Dashboard: View Profile, Update Profile (mobile/email/address/password only), Apply for Verification, View Verification Status, View Digital Identity Card, Logout
- Aadhaar number is **always masked** on screen (e.g. `1234********9012`) — it is never displayed in full, under any circumstance

### Admin Features
- Default admin account (`admin` / `admin123`), auto-created on first run
- Dashboard: View All Citizens, Search Citizen (by ID/Name/Email/Mobile/Aadhaar), Verify Citizen, Reject Citizen, Delete Citizen (with Y/N confirmation), Reports, Export Report, Logout
- Automated verification rule checks: Aadhaar (12 digits), Mobile (10 digits), valid email format, age ≥ 18, and uniqueness of Aadhaar/Email/Mobile across all citizens

### System Features
- Colored console UI (Cyan titles, Blue menus, Green success, Yellow warnings, Red errors)
- Text-file persistence with Save/Read/Update/Delete, using a safe "rewrite whole file" strategy
- Graceful handling of corrupted data rows — a single bad line is skipped with a warning instead of crashing
- Basic exception handling throughout (invalid numeric input, malformed file records)

---

## Folder Structure

```
Smart_Digital_Identity_Verification_System/
│
├── src/
│   ├── main.cpp
│   ├── Person.h / Person.cpp
│   ├── Citizen.h / Citizen.cpp
│   ├── Admin.h / Admin.cpp
│   ├── Authentication.h / Authentication.cpp
│   ├── Verification.h / Verification.cpp
│   ├── FileManager.h / FileManager.cpp
│   ├── ReportManager.h / ReportManager.cpp
│   └── Utility.h / Utility.cpp
│
├── data/
│   ├── citizens.txt
│   ├── admins.txt
│   └── report.txt
│
└── README.md
```

---

## OOP Concepts Demonstrated

| Concept | Where |
|---|---|
| **Inheritance** | `Person → Citizen → Admin` three-level hierarchy |
| **Encapsulation** | All class data is `protected`/`private`, accessed only via getters/controlled setters |
| **Polymorphism** | `Person::displayProfile()` is pure virtual; `Citizen` and `Admin` each override it with completely different output, dispatched correctly through base-class pointers/references |
| **Constructors** | Default and parameterized constructors in every class, including a dedicated "reconstruct from file" constructor in `Citizen` |
| **File Handling** | `FileManager` centralizes all text-file Save/Read/Update/Delete operations |
| **Modular Programming** | Each class lives in its own `.h`/`.cpp` pair with a single, clear responsibility |
| **Exception Handling** | `try/catch` around numeric parsing and malformed file-record parsing, so bad input or corrupted data never crashes the program |

---

## How to Compile

This project requires a C++17-capable compiler (developed and tested with `g++`).

From the `src/` directory, run:

```bash
g++ -std=c++17 -Wall -o SmartIdentitySystem main.cpp Person.cpp Citizen.cpp Admin.cpp Authentication.cpp Verification.cpp FileManager.cpp ReportManager.cpp Utility.cpp
```

This produces an executable named `SmartIdentitySystem` (or `SmartIdentitySystem.exe` on Windows).

> **VS Code users:** open the project folder, ensure the MinGW/g++ toolchain is on your PATH, then run the command above in the integrated terminal (or configure a `tasks.json` build task using the same command).

---

## How to Run

The program expects the `data/` folder to sit **alongside** the executable (i.e. run it from the project root, not from inside `src/`):

```bash
cd Smart_Digital_Identity_Verification_System
./src/SmartIdentitySystem
```

On first run, `data/admins.txt` is created automatically with the default admin account:
- **Username:** `admin`
- **Password:** `admin123`

All citizen and admin data is saved automatically as you use the system — no manual save step is required.

---

## Screenshots

> _Add screenshots of the welcome banner, Citizen Dashboard, Admin Dashboard, and Digital ID Card here._

---

## Future Scope

- Migrate storage from flat text files to a lightweight embedded database (e.g. SQLite) for better scalability and concurrent access
- Add OTP-based two-factor verification for login and password reset
- Export reports in additional formats (CSV, PDF)
- Add an audit log of admin actions (who verified/rejected/deleted which citizen and when)
- Support multiple admin accounts with role-based permissions

---

## Author

Developed as a final-year / college project demonstrating Object-Oriented Programming and modular C++ software design.
