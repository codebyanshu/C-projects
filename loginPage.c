#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct signinformation {
    char name[50];
    char username[50];
    char mobile_no[15];
    char email[50];
    char password[50];
};

void menu();
void login();
void signUp();
void checkInfo();

// Function 1: Main Menu
void menu()
{
    int choice;
    printf("\n---------------------------------WELCOME--------------------------------------\n");
    printf("~ Options :-\n\n");
    printf("1. Sign Up\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("\n~ Please select an option: \t");
    scanf("%d", &choice);
    getchar(); // clear input buffer
    system("cls");  // Clears screen (Windows only)

    switch (choice)
    {
    case 1:
        signUp();  // Sign Up
        break;
    case 2:
        login();   // Login
        break;
    case 3:
        printf("Exiting the system. Goodbye!\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        menu();
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

    printf("Enter full name: ");
    scanf(" %[^\n]", user.name);

    // Mobile number validation
    int valid = 0;
    while (!valid) {
        printf("Enter 10-digit mobile number: ");
        scanf("%s", user.mobile_no);

        valid = 1;
        if (strlen(user.mobile_no) != 10) valid = 0;
        for (int i = 0; i < 10 && valid; i++) {
            if (!isdigit(user.mobile_no[i])) valid = 0;
        }
        if (!valid) printf("Mobile number must be exactly 10 digits (numbers only).\n");
    }

    printf("Enter email: ");
    scanf("%s", user.email);

    printf("Enter username: ");
    scanf("%s", user.username);

    printf("Enter password: ");
    scanf("%s", user.password);

    // Save all info in one line
    fprintf(fptr, "Name      : %s\n", user.name);
    fprintf(fptr, "Mobile    : %s\n", user.mobile_no);
    fprintf(fptr, "Email     : %s\n", user.email);
    fprintf(fptr, "Username  : %s\n", user.username);
    fprintf(fptr, "Password  : %s\n", user.password);
    fprintf(fptr, "--------------------------\n");
    fclose(fptr);

    printf("\nSign-up successful! You can now log in.\n");
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
    printf("\n--------------------------------------------------------------------------------\n");
    printf("Enter username: \t");
    scanf("%s", user.username);
    printf("Enter password: \t");
    scanf("%s", user.password);
    printf("\n");

    char line[100];
    char username[50], pass[50], name[50];
    int found = 0;

    while (fgets(line, sizeof(line), fptr)) {
        // Line 1: Name
        sscanf(line, "Name      : %[^\n]", name);
        fgets(line, sizeof(line), fptr); // Mobile (skip)
        fgets(line, sizeof(line), fptr); // Email (skip)
        fgets(line, sizeof(line), fptr); // Username
        sscanf(line, "Username  : %s", username);
        fgets(line, sizeof(line), fptr); // Password
        sscanf(line, "Password  : %s", pass);
        fgets(line, sizeof(line), fptr); // Separator (skip)

        if (strcmp(user.username, username) == 0 && strcmp(user.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fptr);

    if (found)
    {
        printf(" Login successful!!\n\n");
        printf("Welcome, %s!\n", name);
    }
    else
    {
        printf(" Invalid username or password. Try again.\n\n");
        login();
        return;
    }

    menu();  // Return to menu after login
}

// Main function
int main()
{
    menu();
    return 0;
}
void checkInfo(){
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
   while (!valid) {
       printf("Enter 10-digit mobile number: ");
       scanf("%s", mobile_no);

       if (strlen(mobile_no) != 10) {
           printf("Mobile number must be exactly 10 digits.\n");
           continue;
       }
 valid = 1;
   }

    printf("Enter email: ");
    scanf("%s", email);
    
    fprintf(fptr, "%s\t%s\t%s\n",name, mobile_no, email);
    fclose(fptr);
}