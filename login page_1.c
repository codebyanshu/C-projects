#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct signinformation
{
	char username[50];
	char password[50];
};

void menu();
void login();
void signUp();

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
	printf("Enter username: \t");
	scanf("%s", user.username);
	printf("Enter password: \t");
	scanf("%s", user.password);

	fprintf(fptr, "%s %s\n", user.username, user.password);
	fclose(fptr);

	printf(" \n\nSign up successful! You can go to log-in page.\n\n");
	printf("\n--------------------------------------------------------------------------------");
	login();  // Go to login directly after signup
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

	struct signinformation temp;
	int found = 0;

	while (fscanf(fptr, "%s %s", temp.username, temp.password) != EOF)
	{
		if (strcmp(user.username, temp.username) == 0 &&
		    strcmp(user.password, temp.password) == 0)
		{
			found = 1;
			break;
		}
	}

	fclose(fptr);

	if (found)
	{
		printf(" Login successful!!\n\n");
		
	}
	else
	{
		printf(" Invalid username or password. Try again.\n\n");
		login();
		return;
	}

	menu();  // Return to menu after login  [its your chose to call menu or not]
}

// Main function
int main()
{
	menu();
	return 0;
}

