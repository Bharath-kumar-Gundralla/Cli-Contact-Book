# 📇 Contact Manager in C 

A command-line based contact management system written in **C**, with support for creating, searching, editing, and deleting contacts. The program ensures **phone numbers and email addresses are unique**, and includes proper input validation for all fields.

---

## ✨ Features

- ✅ Add new contacts with:
  - Name
  - Phone Number (must be unique)
  - Email ID (must be unique)
    
- 🔍 Search contacts by:
  - Name (partial match supported)
  - Phone Number
  - Email ID
    
- ✏️ Edit existing contact details:
  - Change name, phone number, or email
  - All changes validated for correctness and uniqueness
    
- 🗑️ Delete contact:
  - Search and delete any contact from the list
    
- 🧠 Input validations:
  - Name should only contain alphabets and spaces
  - Phone number should be digits and of correct length
  - Email must follow basic format rules
- 🧵 CLI-based menu navigation using `switch-case` structure
- 📁 **Data Persistence**: All contacts are saved to and loaded from a `.csv` file

---

## 🧠 Technologies Used

- **Language**: C
- **Platform**: Linux / Ubuntu (GCC)
- **Editor**: VS Code / CLI
- **Tools**: GCC Compiler.

---

## 🚀 How to Compile and Run

### 🔧 Compile
```bash
gcc main.c contact.c -o contact_manager  or gcc *.c
