#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
// Function prototypes
int menu();
void welcomePage();
void subparts(int x);
void appointments();


int main()
{
    int x;
    welcomePage();
    getch(); 
    system("cls");
    x = menu();
    subparts(x);
    return 0;
}

int menu()
{
    printf("--------------------------------------------------\n");
    printf("1. Patient Mangement\n");
    printf("2. Appointments\n");
    printf("3. Update Patient\n");
    printf("4. Billing\n");
    printf("5. Exit\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
        case 1:
            printf("You selected Patient Management.\n");
            break;
        case 2:
            printf("You selected Appointments.\n");
            break;
        case 3:
            printf("You selected Update Patient.\n");
            break;
        case 4:
            printf("You selected Billing.\n");
            break;
        case 5:
            printf("Exiting the system. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
            menu();
    }
    printf("--------------------------------------------------\n");
    return choice;
}
void welcomePage()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to the hospital Mangement system\n");
    printf("--------------------------------------------------\n");
}

void subparts(int x)
{
    switch (x)
    {
        case 1:
            printf("You are now in the Patient Management section.\n");
            break;
        case 2:
            appointments();
            break;
        case 3:
            printf("You are now in the Update Patient section.\n");
            break;
        case 4:
            printf("You are now in the Billing section.\n");
            break;
        default:
            printf("No valid section selected.\n");
    }
}       

void appointments()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to appointments Section.\n");
    printf("--------------------------------------------------\n");
    printf("1. Book Appointment\n");
    printf("2. Cancel Appointment\n");
    printf("3. View Appointments\n");
    printf("4. Back to Main Menu\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
        case 1:
            printf("You selected to book an appointment.\n");
            break;
        case 2:
            printf("You selected to cancel an appointment.\n");
            break;
        case 3:
            printf("You selected to view appointments.\n");
            break;
        case 4:
            printf("Returning to the main menu.\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            appointments(); 
    }
}
