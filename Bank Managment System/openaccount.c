#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "encryption.h"
long long unsigned int generateRandomNumber(int no);
int is_valid_word(const char *str);
void account();
void account_menu();
void print_sorted_accounts();
void modify();
void delete_account();
#define MAX_RECORDS 100

struct accountcreate
{
    char name[50];
    char father_name[50];
    char mobile_no[15];
    char email[50];
    char date_of_birth[50];
    char account_no[20];
};

int is_valid_word(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (!isalpha(str[i]) && str[i] != ' ')
            return 0;
    return 1;
}

long long unsigned int generateRandomNumber(int no)
{
    srand(time(NULL));
    int ran;
    long long unsigned int num = 1;
    for (int i = 0; i < no - 1; i++)
    {
        ran = rand() % 10;
        num = num * 10 + ran;
    }
    return num;
}

// function no 1, create account.
void account()
{
    struct accountcreate user;
    char encrypted_mobile[15], encrypted_email[50];
    int shift_mobile[15], shift_email[50];

    printf("~~~Welcome To Account Managment Page~~~ \n");
    do
    {
        printf("Enter your Name: ");
        scanf(" %[^\n]%*c", user.name);
        if (strlen(user.name) < 4)
            printf("Name must be at least 4 characters long.\n");
        else if (!is_valid_word(user.name))
            printf("Name must contain only letters and spaces.\n");
        else
            break;
    } while (1);

    do
    {
        printf("Enter your Father's Name: ");
        scanf(" %[^\n]%*c", user.father_name);
        if (strlen(user.father_name) < 4)
            printf("Father's name must be at least 4 characters long.\n");
        else if (!is_valid_word(user.father_name))
            printf("Father's name must contain only letters and spaces.\n");
        else
            break;
    } while (1);

    printf("Enter your Mobile Number:-");
    scanf("%s", user.mobile_no);
    while (strlen(user.mobile_no) < 10)
    {
        printf("Mobile No. must be at least 10 characters long.\n ");
        scanf("%s", user.mobile_no);
    }

    printf("Enter your Email:-");
    scanf("%s", user.email);
    while (strstr(user.email, "@gmail.com") == NULL)
    {
        printf("Invalid email! Email must contain '@gmail.com'.\n ");
        scanf("%s", user.email);
    }

    printf("Enter your Date Of Birth:-");
    scanf("%s", user.date_of_birth);

    sprintf(user.account_no, "%llu", generateRandomNumber(12));
    printf("Your Generated Account no. is: %s\n", user.account_no);

    // Encrypt only mobile and email, NOT account_no
    srand(time(NULL));
    encrypt(user.mobile_no, encrypted_mobile, shift_mobile);
    encrypt(user.email, encrypted_email, shift_email);

    FILE *fptr = fopen("login1.txt", "a");
    if (fptr == NULL)
    {
        printf("error in file opening \n");
        return;
    }
    fprintf(fptr,"\n============================================\n");
    fprintf(fptr, "Full Name :- %s\n", user.name);
    fprintf(fptr, "Father Name :- %s\n", user.father_name);
    fprintf(fptr, "Mobile No :- %s\n", encrypted_mobile);
    fprintf(fptr, "Email :- %s\n", encrypted_email);
    fprintf(fptr, "Date Of Birth :- %s\n", user.date_of_birth);
    fprintf(fptr, "Account No :- %s\n", user.account_no); // id -> Account No
    fclose(fptr);
    printf("Your Account Is Successfully Created\n");
}

void account_menu()
{
    int Number;
    while (1)
    {
        printf("~~~Welcome To Account Managment Page~~~  \n\n");
        printf("Options:- \n");
        printf("1. Create Account \n");
        printf("2. View Accounts (Sorted)\n");
        printf("3. Modify \n");
        printf("4. Delete\n");
        printf("5. Exit\n");
        printf("Please Select Any Option:-");
        scanf("%d", &Number);
        switch (Number)
        {
        case 1:
            account();
            break;
        case 2:
            print_sorted_accounts();
            break;
        case 3:
            modify();
            break;
        case 4:
            delete_account();
            break;
        case 5:
            return;
        default:
            printf("invalid input\n");
            break;
        }
    }
}

// Print all accounts sorted by ID
void print_sorted_accounts()
{
    struct accountcreate users[MAX_RECORDS];
    int count = 0;

    FILE *fptr = fopen("login1.txt", "r");
    if (!fptr)
    {
        printf("error in file opening\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fptr))
    {
        if (strstr(line, "Full Name :-") != NULL)
        {
            sscanf(line, "Full Name :- %[^\n]", users[count].name);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Father Name :- %[^\n]", users[count].father_name);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Mobile No :- %[^\n]", users[count].mobile_no);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Email :- %[^\n]", users[count].email);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Date Of Birth :- %[^\n]", users[count].date_of_birth);
            fgets(line, sizeof(line), fptr);
            sscanf(line, "Account No :- %[^\n]", users[count].account_no);
            count++;
        }
    }
    fclose(fptr);

    // Sort by account_no (bubble sort)
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(users[i].account_no, users[j].account_no) > 0)
            {
                struct accountcreate temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    printf("\n--- Sorted Account Records ---\n");
    for (int i = 0; i < count; i++)
    {
        char decrypted_mobile[15], decrypted_email[50];
        decrypt_caesar(users[i].mobile_no, decrypted_mobile, 3);
        decrypt_caesar(users[i].email, decrypted_email, 3);

        printf("============================================\n");
        printf("Full Name :- %s\n", users[i].name);
        printf("Father Name :- %s\n", users[i].father_name);
        printf("Mobile No :- %s\n", decrypted_mobile);
        printf("Email :- %s\n", decrypted_email);
        printf("Date Of Birth :- %s\n", users[i].date_of_birth);
        printf("Account No :- %s\n", users[i].account_no);
    }
}

// Function No.3 , modify account detail:
void modify()
{
    struct accountcreate user;
    char search_accno[15];
    int found = 0;
    FILE *fptr = fopen("login1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }

    printf("Enter your Account No to modify: ");
    scanf("%s", search_accno);
    while (fscanf(fptr, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nAccount No :- %s\n",
                  user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.account_no) != EOF)
    {
        if (strcmp(user.account_no, search_accno) == 0)
        {
            found = 1;
            printf("Account found! Enter new details:\n");
            printf("Enter Name: ");
            scanf("%s", user.name);
            printf("Enter Father Name: ");
            scanf("%s", user.father_name);
            printf("Enter Mobile Number: ");
            scanf("%s", user.mobile_no);
            printf("Enter Email: ");
            scanf("%s", user.email);
            printf("Enter Date Of Birth: ");
            scanf("%s", user.date_of_birth);
        }

        fprintf(temp, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nAccount No :- %s\n",
                user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.account_no);
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("login1.txt");
        rename("temp.txt", "login1.txt");
        printf("Account modified successfully!\n");
    }
    else
    {
        printf("Account No not found.\n");
    }
}

// function no. 4, delete an account:
void delete_account()
{
    struct accountcreate user;
    char search_accno[15];
    int found = 0;
    FILE *fptr = fopen("login1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }

    printf("Enter your Account No for delete an account: ");
    scanf("%s", search_accno);
    while (fscanf(fptr, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nAccount No :- %s\n",
                  user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.account_no) != EOF)
    {
        if (strcmp(user.account_no, search_accno) == 0)
        {
            found = 1;
            printf("Account has been found and deleted.\n");
            continue; // skip writing this record
        }

        fprintf(temp, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nAccount No :- %s\n",
                user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.account_no);
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("login1.txt");
        rename("temp.txt", "login1.txt");
        printf("Account Has Been Deleted Successfully\n");
    }
    else
    {
        printf("Account No not found.\n");
    }
}
