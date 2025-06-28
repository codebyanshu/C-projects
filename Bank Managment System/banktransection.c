#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "encryption.h" // Add this line

void menu();
void deposit();
void withdrawal();
void transaction_view(); // Change prototype
int login(const char *acc, const char *pin, char *name_out);
int pinStrength(const char pin[]);

struct information
{
    char name[50];
    char number[20];
    char pin[30];
    char cash[20];
    char date[10];
};

void menu()
{
    int choice;
    printf("WELCOME TO TRANSACTION PAGE.\n");
    printf("\n~ Options ~\n");
    printf("1. Deposit money\n");
    printf("2. Withdraw money\n");
    printf("3. View Balance\n");
    printf("4. Exit\n");
    printf("\nPlease select an option: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        deposit();
        break;
    case 2:
        withdrawal();
        break;
    case 3:
        transaction_view(); // Change to transaction_view
        break;
    case 4:
        printf("Goodbye!\n");
        break;
    default:
        printf("Invalid choice. Try again.\n");
        menu();
        break;
    }
}

int pinStrength(const char pin[])
{
    int length = strlen(pin);
    if (length < 6)
    {
        printf("\nPin is too short. Minimum 6 characters required.\n");
        return 0;
    }
    return 1;
}

void deposit()
{
    struct information user;
    char encrypted_number[20], encrypted_pin[30];
    int shift_number[20], shift_pin[30];

    printf("\n~ Deposit Section ~\n");

    printf("Enter your name: ");
    scanf("%s", user.name);

    int valid = 0;
    while (!valid)
    {
        printf("Enter your 12-digit account number: ");
        scanf("%s", user.number);
        valid = (strlen(user.number) == 12);
        int i;
        for (i = 0; i < 12 && valid; i++)
            if (!isdigit(user.number[i]))
                valid = 0;
        if (!valid)
            printf("Account number must be exactly 12 digits.\n");
    }

    do
    {
        printf("Enter PIN (min 6 characters): ");
        scanf("%s", user.pin);
    } while (!pinStrength(user.pin));

    printf("Enter the date (dd-mm-yy): ");
    scanf("%s", user.date);
    printf("Enter the deposit amount: ");
    scanf("%s", user.cash);
    int depositAmount = atoi(user.cash);

    // Encrypt account number and pin
    srand(time(NULL));
    encrypt(user.number, encrypted_number, shift_number);
    encrypt(user.pin, encrypted_pin, shift_pin);

    // Read latest balance
    FILE *file = fopen("deposit.txt", "r");
    char line[100], number[20], pin[30];
    int existingBalance = 0;
    while (file && fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Account number") != NULL)
        {
            sscanf(line, "Account number :-%s", number);
            fgets(line, sizeof(line), file);
            sscanf(line, "PIN            :-%s", pin);
            fgets(line, sizeof(line), file); // Date
            fgets(line, sizeof(line), file); // Cash
            fgets(line, sizeof(line), file); // Balance
            if (strcmp(number, encrypted_number) == 0 && strcmp(pin, encrypted_pin) == 0)
                sscanf(line, "Total Balance  :-%d", &existingBalance);
        }
    }
    if (file)
        fclose(file);

    int newBalance = existingBalance + depositAmount;

    FILE *fptr = fopen("deposit.txt", "a");
    fprintf(fptr, "--------------------------\n");
    fprintf(fptr, "Name           :-%s\n", user.name);
    fprintf(fptr, "Account number :-%s\n", encrypted_number);
    fprintf(fptr, "PIN            :-%s\n", encrypted_pin);
    fprintf(fptr, "Date           :-%s\n", user.date);
    fprintf(fptr, "Cash Amount    :-%d\n", depositAmount);
    fprintf(fptr, "Total Balance  :-%d\n", newBalance);
    fprintf(fptr, "--------------------------\n");
    fclose(fptr);

    printf("\nDeposited: %d\n", depositAmount);
    printf("New Balance: %d\n\n", newBalance);
    menu();
}

void withdrawal()
{
    struct information user;
    char encrypted_number[20], encrypted_pin[30];
    int shift_number[20], shift_pin[30];

    printf("\n~ Withdrawal Section ~\n");

    printf("Enter your account number: ");
    scanf("%s", user.number);
    printf("Enter your PIN: ");
    scanf("%s", user.pin);

    // Encrypt input for comparison
    srand(time(NULL));
    encrypt(user.number, encrypted_number, shift_number);
    encrypt(user.pin, encrypted_pin, shift_pin);

    if (!login(encrypted_number, encrypted_pin, user.name))
    {
        printf("Authentication failed.\n");
        menu();
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%s", user.cash);
    printf("Enter date: ");
    scanf("%s", user.date);
    int withdrawalAmount = atoi(user.cash);

    FILE *file = fopen("deposit.txt", "r");
    char line[100], number[20], pin[30];
    int existingBalance = 0;
    while (file && fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Account number") != NULL)
        {
            sscanf(line, "Account number :-%s", number);
            fgets(line, sizeof(line), file);
            sscanf(line, "PIN            :-%s", pin);
            fgets(line, sizeof(line), file); // Date
            fgets(line, sizeof(line), file); // Cash/Withdraw
            fgets(line, sizeof(line), file); // Balance
            if (strcmp(number, encrypted_number) == 0 && strcmp(pin, encrypted_pin) == 0)
                sscanf(line, "Total Balance  :-%d", &existingBalance);
        }
    }
    if (file)
        fclose(file);

    if (withdrawalAmount > existingBalance)
    {
        printf("Insufficient balance! Transaction cancelled.\n");
        return;
    }

    int newBalance = existingBalance - withdrawalAmount;

    FILE *fptr = fopen("deposit.txt", "a");
    fprintf(fptr, "--------------------------\n");
    fprintf(fptr, "Name           :-%s\n", user.name);
    fprintf(fptr, "Account number :-%s\n", encrypted_number);
    fprintf(fptr, "PIN            :-%s\n", encrypted_pin);
    fprintf(fptr, "Date           :-%s\n", user.date);
    fprintf(fptr, "Withdraw Amount:-%d\n", withdrawalAmount);
    fprintf(fptr, "Total Balance  :-%d\n", newBalance);
    fprintf(fptr, "--------------------------\n");
    fclose(fptr);

    printf("\nWithdrawn: %d\n", withdrawalAmount);
    printf("New Balance: %d\n\n", newBalance);
    menu();
}

void transaction_view() // Change definition
{
    FILE *file;
    char line[100], name[50], number[20], pin[30], amount[20], date[20], balance[20];
    char searchNumber[20], searchPin[30];
    char encrypted_number[20], encrypted_pin[30];
    int shift_number[20], shift_pin[30];
    int found = 0;

    printf("\n~ View Account Details ~\n");
    printf("Enter Account Number: ");
    scanf("%s", searchNumber);
    printf("Enter PIN: ");
    scanf("%s", searchPin);

    // Encrypt input for comparison
    srand(time(NULL));
    encrypt(searchNumber, encrypted_number, shift_number);
    encrypt(searchPin, encrypted_pin, shift_pin);

    file = fopen("deposit.txt", "r");
    if (!file)
    {
        printf("Error: deposit.txt not found.\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "Name") != NULL)
        {
            sscanf(line, "Name           :-%s", name);
            fgets(line, sizeof(line), file);
            sscanf(line, "Account number :-%s", number);
            fgets(line, sizeof(line), file);
            sscanf(line, "PIN            :-%s", pin);
            fgets(line, sizeof(line), file);
            sscanf(line, "%*[^:]:-%[^\n]", date);
            fgets(line, sizeof(line), file);
            sscanf(line, "%*[^:]:-%s", amount);
            fgets(line, sizeof(line), file);
            sscanf(line, "Total Balance  :-%s", balance);

            if (strcmp(encrypted_number, number) == 0 && strcmp(encrypted_pin, pin) == 0)
            {
                found = 1;
            }
        }
    }
    fclose(file);

    if (found)
    {
        printf("\n--- Account Found ---\n");
        printf("Name       : %s\n", name);
        printf("Account ID : %s\n", searchNumber); // Show original, not encrypted
        printf("PIN        : %s\n", searchPin);
        printf("Date       : %s\n", date);
        printf("Balance    : %s\n\n", balance);
    }
    else
    {
        printf("\nNo matching account found.\n\n");
    }

    menu();
}

int login(const char *acc, const char *pin, char *name_out)
{
    FILE *fptr = fopen("deposit.txt", "r");
    if (!fptr)
        return 0;

    char line[100], number[20], pin_try[30];
    while (fgets(line, sizeof(line), fptr))
    {
        if (strstr(line, "Name") != NULL)
        {
            sscanf(line, "Name           :-%s", name_out);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Account number :-%s", number);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "PIN            :-%s", pin_try);
            if (strcmp(acc, number) == 0 && strcmp(pin, pin_try) == 0)
            {
                fclose(fptr);
                return 1;
            }
        }
    }

    fclose(fptr);
    return 0;
}

// int main() {
//     menu();
//     return 0;
// }
