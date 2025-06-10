# Hospital Management System

A C-based console application for managing hospital operations, including patient management, appointments, billing, and user authentication.

---

Created by Team Elite.

## Features

- **User Authentication**: Sign up and login system with password strength validation.
- **Patient Management**: Add, search, view, edit, and delete patient records.
- **Appointment Management**: Book, cancel, search, view, and update appointments.
- **Billing System**: Create, search, view, edit, delete, and print patient bills.

## File Structure

- `main.c` - Entry point and main menu logic.
- `Welcomepage.c` - Welcome screen and appointment management.
- `login_page.c` - User login and signup functionality.
- `patient.c` - Patient record management.
- `bill.c` - Billing menu and bill management.
- `createbill.c` - Bill creation logic.
- `impfunc.h` - Shared function declarations and input helpers.
- `login.txt` - Stores user login/signup information.
- `patient.txt` - Stores patient records.
- `patients.txt` - Stores appointment records.
- `bill.txt` - Stores billing records.

## How to Build

1. Open the project folder in your C IDE (e.g., Visual Studio Code).
2. Compile all `.c` files together. Example using GCC:
   ```
   gcc main.c -o main.exe
   ```
3. Run the executable:
   ```
   ./main.exe
   ```

## Usage

- On launch, the welcome page appears.
- Sign up or log in to access the main menu.
- Navigate between Patient Management, Appointments, and Billing using the menu options.
- Data is stored in plain text files in the project directory.

## Notes

- Make sure all `.txt` files are present and writable in the project directory.
- The application uses Windows-specific functions (`system("cls")`, `Sleep`, `getch`).

# Hospital Management System - Login & Signup Module

This module handles user authentication for the Hospital Management System. It provides a simple console-based interface for users to sign up, log in, and store their credentials securely in a text file.

## Features

- **Sign Up:**  
  - Collects user's full name, mobile number, email, username, and password.
  - Validates mobile number (must be exactly 10 digits).
  - Validates email (must contain `@gmail.com`).
  - Username must be at least 4 characters.
  - Password strength checker (requires a mix of uppercase, lowercase, digits, and special characters, minimum 8 characters).
  - Stores user information in `login.txt`.

- **Login:**  
  - Prompts for username and password.
  - Checks credentials against stored data in `login.txt`.
  - Displays a welcome message on successful login.
  - Allows retry on failure.

- **Data Storage:**  
  - User data is stored in a human-readable format in `login.txt`.
  - Each user entry is separated by lines for clarity.

- **Input Validation:**  
  - Ensures all fields are entered correctly.
  - Provides user-friendly error messages and prompts for re-entry.

## File Structure

- `login_page.c` - Contains all logic for sign up, login, and password validation.
- `login.txt` - Stores user credentials and information.

## How It Works

1. **Main Menu:**  
   On running the program, users are presented with options to Sign Up, Login, or Exit.

2. **Sign Up:**  
   - User enters their details.
   - The program validates each field.
   - If all validations pass, the data is appended to `login.txt`.
   - User is prompted to log in after successful sign up.

3. **Login:**  
   - User enters their username and password.
   - The program searches `login.txt` for a matching entry.
   - On success, a welcome message is displayed.
   - On failure, the user is prompted to try again.

4. **Password Strength:**  
   - Passwords are checked for length and character variety.
   - Feedback is given on password strength.

## Example User Data Format in `login.txt`

```
--------------------------
Name      : John Doe
Mobile    : 9876543210
Email     : johndoe@gmail.com
Username  : johndoe
Password  : Example@123
--------------------------
```

## How to Run

1. Compile the code:
   ```
   gcc login_page.c -o login_page.exe
   ```
2. Run the executable:
   ```
   ./login_page.exe
   ```

## Notes

- This module is designed for educational/demo purposes and stores passwords in plain text. For real-world applications, always hash and salt passwords.
- The program uses Windows-specific commands (`system("cls")`).
