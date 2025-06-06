#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "patient.c"

FILE *fptr;

// Function prototypes
int menu();
void welcomePage();
void subparts(int x);
void appointments();
void bookappointment();
void cancelappointment();
void searchAppointments();
void viewAppointments();


// void patientManagement();

// Structure to hold patient information
struct patient
{
    char name[50];
    int age;
    int id;
    char doctor[50];
    char appointmentDate[20];
};

// #include <stdio.h>
// int main()
// {
//     welcomePage();
//     getch();
//     system("cls");
//     int x = menu();
//     subparts(x);
//     return 0;
// }

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
        
        getch();
        system("cls");
        patientmenu();
        break;
    case 2:
        system("cls");
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
    printf("3. Search Appointments\n");
    printf("4. View Appointments\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        bookappointment();
        break;
    case 2:
        cancelappointment();
        break;
    case 3:
        searchAppointments();
        break;
    case 4:
        viewAppointments();
        break;
        return;
    default:
        printf("Invalid choice. Please try again.\n");
        appointments();
    }
}

void bookappointment()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Book Appointment Section.\n");
    printf("--------------------------------------------------\n");
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
    if (fptr != NULL)
    {
        fprintf(fptr, "Name : %s, Age : %d, Id : %d, Doctor : %s, Date : %s\n", newPatient.name, newPatient.age, newPatient.id, newPatient.doctor, newPatient.appointmentDate);
        fclose(fptr);
        printf("New appointment booked successfully!\n");
    }
    else
    {
        printf("Error opening patients.txt for writing!\n");
    }
}

void cancelappointment()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Cancel Appointment Section.\n");
    printf("--------------------------------------------------\n");
    int id;
    printf("Enter the patient ID to cancel the appointment: ");
    scanf("%d", &id);
    
    FILE *fptr = fopen("patients.txt", "r");
    FILE *tempFptr = fopen("temp.txt", "w");
    if (fptr == NULL || tempFptr == NULL)
    {
        printf("Error opening files!\n");
        return;
    }
    struct patient tempPatient;
    int found = 0;          
    char buffer[256]; 
    while (fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
        
        if (tempPatient.id == id)
        {
            found = 1; 
            continue; 
        }
        fprintf(tempFptr, "%s", buffer); 
    }
   
    
    fclose(fptr);
    fclose(tempFptr); 
    if (found)
    {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        printf("Appointment for patient ID %d has been cancelled successfully.\n", id);
    }
    else
    {
        printf("No appointment found for patient ID %d.\n", id);
        remove("temp.txt"); // Clean up the temporary file
    }
    
}

void searchAppointments()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Search Appointments Section.\n");
    printf("--------------------------------------------------\n");
    FILE *fptr = fopen("patients.txt", "r");
    if (fptr == NULL)
    {
        printf("No appointments found.\n");
        return;
    }
    struct patient tempPatient;
    char name[50];
    char id;
    CHOICE:
    printf("Enter Choice one of the following:\n");
    printf("1. By Name to view Appointments\n");
    printf("2. By ID to view Appointments\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    fflush(stdin);
    int choice;

    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("Enter the name of the patient: ");
        fflush(stdin);
        scanf("%[^\n]s", name);
        break;
    case 2:
        printf("Enter the ID of the patient: ");
        scanf("%d", id);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        goto CHOICE;
    }

    char buffer[256];
    while (fgets (buffer, sizeof(buffer), fptr) != NULL)
    {
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
        switch (choice)
        {
        case 1:
            if (strcmp(tempPatient.name, name) == 0)
            {
                printf("Appointment found: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
            }
            break;
        case 2: 
            if (id == tempPatient.id)
            {
                printf("Appointment found: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
                fclose(fptr);
                return;
            }
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            fclose(fptr);
            return;
        }
    }
    fclose(fptr);
    
    
}

 void viewAppointments()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to View Appointments Section.\n");
    printf("--------------------------------------------------\n");
    FILE *fptr = fopen("patients.txt", "r");
    if (fptr == NULL)
    {
        printf("No appointments found.\n");
        return;
    }
    struct patient tempPatient;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
        printf("Appointment: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
    }
    fclose(fptr);
}
// void patientManagement()
// {
//     printf("--------------------------------------------------\n");
//     printf("Welcome to Patient Management Section.\n");
//     printf("--------------------------------------------------\n");
//     printf("1. Add New Patient\n");
//     printf("2. View Patients\n");
//     printf("3. Update Patient Information\n");
//     printf("4. Back to Main Menu\n");
//     printf("--------------------------------------------------\n");
//     printf("Please select an option: ");
//     int choice;
//     scanf("%d", &choice);
//     system("cls");
//     switch (choice)
//     {
//     case 1:
//     break;
//         printf("You selected to add a new patient.\n");
//         struct patient newPatient;
//         printf("Enter patient name: ");
//         fflush(stdin);
//         scanf("%[^\n]s", newPatient.name);
//         fflush(stdin);
//         printf("Enter patient age: ");
//         scanf("%d", &newPatient.age);
//         printf("Enter patient ID: ");
//         scanf("%d", &newPatient.id);
//         fflush(stdin);
//         printf("Enter doctor's name: ");
//         scanf(" %[^\n]s", newPatient.doctor);
//         fflush(stdin);
//         printf("Enter appointment date (DD/MM/YYYY): ");
//         scanf(" %[^\n]s", newPatient.appointmentDate);

//         FILE *fptr = fopen("patients.txt", "a");
//         if (fptr != NULL) {
//             fprintf(fptr, "Name : %s,\nAge : %d,\nId : %d,\nDoctor : %s,\nDate : %s\n", newPatient.name, newPatient.age, newPatient.id, newPatient.doctor, newPatient.appointmentDate);
//             fclose(fptr);
//         } else {
//             printf("Error opening patients.txt for writing!\n");
//         }
//         printf("New patient added successfully!\n");

//         break;
//     case 2:
//         printf("You selected to view patients.\n");
//         break;
//     case 3:
//         printf("You selected to update patient information.\n");
//         break;
//     case 4:
//         printf("Returning to the main menu.\n");
//         menu();
//         return;
//     default:
//         printf("Invalid choice. Please try again.\n");
//         patientManagement();
//     }
// }