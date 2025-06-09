#include "Welcomepage.c"
#include "login_page.c"
#include "patient.c"
#include "bill.c"

int menu();

int main()
{
    welcomePage();
    system("cls");

    return 0;
}

int menu()
{
    head();
    printf("--------------------------------------------------\n");
    printf("Welcome to Main Section.\n");
    printf("--------------------------------------------------\n\n");
    // printf("--------------------------------------------------\n");
    printf("1. Patient Mangement\n");
    printf("2. Appointments\n");
    printf("3. Billing\n");
    printf("4. back to login page\n");
    printf("0. exit\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        printf("You selected Patient Management.\n");
        Sleep(1000); // Pause for 1 second
        system("cls");
        patientmenu(); // Call the patient management menu
        break;
    case 2:
        printf("You selected Appointments.\n");
        Sleep(1000); // Pause for 1 second
        system("cls");
        appointments();
        break;
    case 3:
        printf("You selected Billing.\n");
        Sleep(1000); // Pause for 1 second
        system("cls");
        billMenu(); // Call the billing menu
        break;
    case 4:
        printf("Exiting the system. Back to login paga\n");
        menuLogin();
    case 0:
        printf("Exiting the system. Goodbye!\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        menu();
    }
    printf("--------------------------------------------------\n");
}