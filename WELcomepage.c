#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>

FILE *fptr;

// Function prototypes
int menu();
void welcomePage();
void subparts(int x);
void appointments();
void patientManagement();

// Structure to hold patient information
struct patient
{
    char name[50];
    int age;
    int id;
    char doctor[50];
    char appointmentDate[20];
};


int main()
{
    welcomePage();
    getch();
    system("cls");
    int x = menu();
    subparts(x);
    fclose(fptr);
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
        getch();    
        system("cls");
        patientManagement();
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

void patientManagement()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Patient Management Section.\n");
    printf("--------------------------------------------------\n");
    printf("1. Add New Patient\n");
    printf("2. View Patients\n");
    printf("3. Update Patient Information\n");
    printf("4. Back to Main Menu\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        printf("You selected to add a new patient.\n");
        struct patient newPatient;
        printf("Enter patient name: ");
        fflush(stdin); 
        scanf("%[^\n]s", newPatient.name);
        fflush(stdin); 
        printf("Enter patient age: ");
        scanf("%d", &newPatient.age);  
        printf("Enter patient ID: ");
        scanf("%d", &newPatient.id);
        fflush(stdin); 
        printf("Enter doctor's name: ");
        scanf(" %[^\n]s", newPatient.doctor);
        fflush(stdin); 
        printf("Enter appointment date (DD/MM/YYYY): ");
        scanf(" %[^\n]s", newPatient.appointmentDate);

       
        FILE *fptr = fopen("patients.txt", "a");
        if (fptr != NULL) {
            fprintf(fptr, "%s,%d,%d,%s,%s\n", newPatient.name, newPatient.age, newPatient.id, newPatient.doctor, newPatient.appointmentDate);
            fclose(fptr);
        } else {
            printf("Error opening patients.txt for writing!\n");
        }
        printf("New patient added successfully!\n"); 
        
        break;
    case 2:
        printf("You selected to view patients.\n");
        break;
    case 3:
        printf("You selected to update patient information.\n");
        break;
    case 4:
        printf("Returning to the main menu.\n");
        menu();
        return;
    default:
        printf("Invalid choice. Please try again.\n");
        patientManagement();
    }
}
