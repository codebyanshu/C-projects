#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "impfunc.h"

struct signinformation
{
    char name[50];
    char username[50];
    char mobile_no[15];
    char email[50];
    char password[50];
};

void menuLogin();
void login();
void signUp();
void information();
int checkPasswordStrength(const char password[]);

// Function 1: Main Menu
void menuLogin()
{
    int choice;
    printf("\n---------------------------------WELCOME--------------------------------------\n");
    printf("~ Options :-\n\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("\n~ Please select an option: \t");
    scanf("%d", &choice);
    getchar();     // clear input buffer
    system("cls"); // Clears screen (Windows only)

    switch (choice)
    {
    case 1:
        signUp(); // Sign Up
        break;
    case 2:
        login(); // Login
        break;
    case 3:
        printf("Exiting the system. Goodbye!\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        menuLogin();
        break;
    }
}

// Function 2: Sign Up
void signUp()
{
    struct signinformation user;
    FILE *fptr = fopen("login.txt", "a");

    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\t\t\t~ Welcome!!, To Sign-Up Page ~\n\n");

    printf("Enter full name :- \t ");
    scanf(" %[^\n]", user.name);

    // Mobile number validation
    int valid = 0;
    while (!valid)
    {
        printf("Enter mobile number :- \t ");
        scanf("%s", user.mobile_no);

        valid = 1;
        if (strlen(user.mobile_no) != 10)
            valid = 0;
        int i;
        for (i = 0; i < 10 && valid; i++)
        {
            if (!isdigit(user.mobile_no[i]))
                valid = 0;
        }
        if (!valid)
            printf("Mobile number must be exactly 10 digits (numbers only).\n");
    }

    printf("Enter email: ");
    scanf("%s", user.email);

    while (strstr(user.email, "@gmail.com") == NULL)
    {
        printf("Invalid email! Email must contain '@gmail.com'.\n\n Enter again email:- ");
        scanf("%s", user.email);
    }

    printf("Enter username: ");
    scanf("%s", user.username);

    while (strlen(user.username) < 4)
    {
        printf("Username must be at least 4 characters long.\n\n Enter again username :- ");
        scanf("%s", user.username);
    }

    // Password input and strength check
    do
    {
        printf("Enter password :- \t ");
        scanf("%s", user.password);
    } while (!checkPasswordStrength(user.password));

    // Save all info in one line
    fprintf(fptr, "--------------------------\n");
    fprintf(fptr, "Name      : %s\n", user.name);
    fprintf(fptr, "Mobile    : %s\n", user.mobile_no);
    fprintf(fptr, "Email     : %s\n", user.email);
    fprintf(fptr, "Username  : %s\n", user.username);
    fprintf(fptr, "Password  : %s\n", user.password);
    fprintf(fptr, "--------------------------\n");
    fclose(fptr);

    printf("\nSign-up successful! You can go to log in.\n\n");
    login();
}

// Function 3: Login
void login()
{
    struct signinformation user;
    FILE *fptr = fopen("login.txt", "r");

    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\t\t\t\t~ Welcome to Login Page ~\n");
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);

    char line[100];
    char file_username[50], file_password[50], file_name[50];
    int found = 0;

    while (fgets(line, sizeof(line), fptr))
    {
        // Read name
        printf("enter in while \n");
        if (sscanf(line, "Name      : %[^\n]", file_name) != 1)
            continue;

        // Skip Mobile & Email
        fgets(line, sizeof(line), fptr); // Mobile
        fgets(line, sizeof(line), fptr); // Email

        // Read Username
        fgets(line, sizeof(line), fptr);
        sscanf(line, "Username  : %s", file_username);

        // Read Password
        fgets(line, sizeof(line), fptr);
        sscanf(line, "Password  : %s", file_password);

        // Skip separator
        fgets(line, sizeof(line), fptr);

        // Match username and password
        if (strcmp(user.username, file_username) == 0 &&
            strcmp(user.password, file_password) == 0)
        {
            found = 1;
            break;
        }
    }
    if (found)
    {
        printf("Login successful!\n\n");
        printf("Welcome, %s!\n", file_name);
    }
    else
    {
        printf("Invalid username or password. Try again.\n");
        login(); // Careful: recursion
    }

    fclose(fptr);
}

void information()
{
    char name[20];
    char email[30];
    char mobile_no[15];

    FILE *fptr = fopen("login.txt", "a");

    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter full name: ");
    scanf(" %[^\n]", name);

    // Mobile number validation
    int valid = 0;
    while (!valid)
    {
        printf("Enter 10-digit mobile number: ");
        scanf("%s", mobile_no);

        if (strlen(mobile_no) != 10)
        {
            printf("Mobile number must be exactly 10 digits.\n");
            continue;
        }
        valid = 1;
    }

    printf("Enter email: ");
    scanf("%s", email);

    fprintf(fptr, "%s\t%s\t%s\n", name, mobile_no, email);
    fclose(fptr);
}

// Function: Check Password Strength
int checkPasswordStrength(const char password[])
{
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    int length = strlen(password);

    int i;
    for (i = 0; i < length; i++)
    {
        if (isupper(password[i]))
            hasUpper = 1;
        else if (islower(password[i]))
            hasLower = 1;
        else if (isdigit(password[i]))
            hasDigit = 1;
        else
            hasSpecial = 1;
    }

    if (length < 8)
    {
        printf("\nPassword is too short. Minimum 8 characters required.\n");
        return 0;
    }

    if (hasUpper && hasLower && hasDigit && hasSpecial)
    {
        printf("Password Strength: Strong\n");
        return 1;
    }
    else if ((hasUpper && hasLower && hasDigit) ||
             (hasLower && hasDigit && hasSpecial) ||
             (hasUpper && hasDigit && hasSpecial))
    {
        printf("Password Strength: Good (consider adding more variety)\n");
        return 1;
    }
    else
    {
        printf("\nPassword is weak. Include upper, lower, digit, and special character.\n");
        return 0;
    }
}