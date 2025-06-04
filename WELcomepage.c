#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
// Function prototypes
void menu();
void welcomePage();\

int main()
{
    welcomePage();
    getch(); 
    system("cls");
    menu();
    return 0;
}

void menu()
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
}
void welcomePage()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to the hospital Mangement system\n");
    printf("--------------------------------------------------\n");
}
