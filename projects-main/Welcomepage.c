#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>

FILE *fptr;

// Function prototypes

void welcomePage();
void appointments();
void bookappointment();
void cancelappointment();
void searchAppointments();
void viewAppointments();
void updateAppointment();

// void patientManagement();

// Structure to hold patient information
struct p_atient
{
    char name[50];
    int age;
    int id;
    char doctor[50];
    char appointmentDate[20];
};

void welcomePage()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to the hospital Mangement system\n");
    printf("--------------------------------------------------\n");
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
    printf("5. Update Appointment\n");
    printf("6. Exit\n");
    printf("--------------------------------------------------\n");
    printf("Please select an option: ");
    int choice;
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        printf("You selected Book Appointment.\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        bookappointment();
        break;
    case 2:
        printf("You selected Cancel Appointment.\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        cancelappointment();
        break;
    case 3:
        printf("You selected Search Appointments.\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        searchAppointments();
        break;
    case 4:
        printf("You selected View Appointments.\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        viewAppointments();
        break;
    case 5:
        printf("You selected Update Appointment.\n");

        Sleep(1000); // Pause for 1 seconds
        system("cls");
        updateAppointment();
        break;
    case 6:
        printf("Exiting the system. Goodbye!\n");
        Sleep(1000); // Pause for 1 seconds
        exit(0);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        Sleep(1000); // Pause for 1 seconds
        appointments();
    }
}

void bookappointment()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Book Appointment Section.\n");
    printf("--------------------------------------------------\n");
    Sleep(1000); // Pause for 1 seconds
    system("cls");
    struct p_atient newPatient;
    printf("Enter patient name: ");
    fflush(stdin);
    scanf("%[^\n]s", newPatient.name);
    fflush(stdin);
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    while (1)
    {
        printf("Enter patient ID : ");
        scanf("%d", &newPatient.id);
        if (newPatient.id > 0)
        {
            break;
        }
        else
        {
            printf("Invalid ID. Please enter a positive integer.\n");
        }
    }
    char buffer[256];
    FILE *checkFptr = fopen("patients.txt", "r");
    if (checkFptr != NULL)
    {
        while (fgets(buffer, sizeof(buffer), checkFptr) != NULL)
        {
            struct p_atient tempPatient;
            sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
            if (tempPatient.id == newPatient.id)
            {
                printf("ID already exists. Please enter a unique ID.\n");

                fclose(checkFptr);
                bookappointment(); // Restart the booking process
                return;
            }
        }
        fclose(checkFptr);
    }

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
        printf("--------------------------------------------------\n");
        printf("New appointment booked successfully!\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        printf("--------------------------------------------------\n");
        printf("Patient Details:\n");
        printf("Name: %s\n", newPatient.name);
        printf("Age: %d\n", newPatient.age);
        printf("ID: %d\n", newPatient.id);
        printf("Doctor: %s\n", newPatient.doctor);
        printf("Appointment Date: %s\n", newPatient.appointmentDate);
        printf("--------------------------------------------------\n");
        printf("Thank you for booking an appointment with us!\n");
        Sleep(5000); // Pause for 1 seconds
        system("cls");
        appointments(); // Return to appointments menu
    }
    else
    {
        printf("Error opening patients.txt for writing!\n");
        printf("Please ensure the file exists and is writable.\n");
        printf("--------------------------------------------------\n");
    }
    fclose(fptr);
}

void cancelappointment()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Cancel Appointment Section.\n");
    printf("--------------------------------------------------\n");
    Sleep(1000); // Pause for 1 seconds
    system("cls");
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
    struct p_atient tempPatient;
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
        printf("--------------------------------------------------\n");
        printf("Thank you for using our service!\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        appointments(); // Return to appointments menu
    }
    else
    {
        printf("No appointment found for patient ID %d.\n", id);
        remove("temp.txt"); // Clean up the temporary file
        printf("--------------------------------------------------\n");
        printf("Thank you for using our service!\n");
        Sleep(3000); // Pause for 1 seconds
        system("cls");
        appointments(); // Return to appointments menu
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
    struct p_atient tempPatient;
    char name[50];
    int id;
CHOICE:
    printf("--------------------------------------------------\n");
    printf("Search Appointments by:\n");
    printf("1. Patient Name\n");
    printf("2. Patient ID\n");
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
        scanf("%d", &id);
        break;
    default:
        printf("Invalid choice. Please try again.\n");
        goto CHOICE;
    }

    char buffer[256];
    int found = 0;
    switch (choice)
    {
    case 1:
        while (fgets(buffer, sizeof(buffer), fptr) != NULL)
        {
            sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
            if (strcmp(tempPatient.name, name) == 0)
            {
                printf("Appointment found: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
                found++;
            }
        }
        fclose(fptr);
        break;
    case 2:
        while (fgets(buffer, sizeof(buffer), fptr) != NULL)
        {
            sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
            if (tempPatient.id == id)
            {
                printf("Appointment found: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
                found++;
            }
        }
        fclose(fptr);
        break;
}
    if (found == 0)
    {
        printf("No appointment found for the given criteria.\n");
        printf("--------------------------------------------------\n");
        printf("Thank you for using our service!\n");
        Sleep(5000); // Pause for 1 seconds
        system("cls");
        appointments(); // Return to appointments menu
    }
    else
    {
        printf("--------------------------------------------------\n");
        printf("Thank you for using our service!\n");
        Sleep(5000); // Pause for 1 seconds
        system("cls");
        appointments(); // Return to appointments menu
    }

}   


void viewAppointments()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to View Appointments Section.\n");
    printf("--------------------------------------------------\n");
    Sleep(1000); // Pause for 1 seconds
    system("cls");
    printf("--------------------------------------------------\n");
    printf("List of all appointments:\n");
    printf("--------------------------------------------------\n");
    FILE *fptr = fopen("patients.txt", "r");
    if (fptr == NULL)
    {
        printf("No appointments found.\n");
        return;
    }
    struct p_atient tempPatient;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
        printf("Appointment: %s, Age: %d, ID: %d, Doctor: %s, Date: %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
    }
    fclose(fptr);
    printf("--------------------------------------------------\n");
    printf("Thank you for using our service!\n");
    printf("--------------------------------------------------\n");
    Sleep(5000); // Pause for 1 seconds
    printf("Press any key to return to the appointments menu...\n");
    fflush(stdin);
    getch(); // Wait for user input
    system("cls");  
    appointments(); // Return to appointments menu
}

void updateAppointment()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Update Appointment Section.\n");
    printf("--------------------------------------------------\n");
    Sleep(1000); // Pause for 1 seconds
    system("cls");
    int id;
    printf("Enter the patient ID to update the appointment: ");
    scanf("%d", &id);

    FILE *fptr = fopen("patients.txt", "r");
    FILE *tempFptr = fopen("temp.txt", "w");
    if (fptr == NULL || tempFptr == NULL)
    {
        printf("Error opening files!\n");
        return;
    }

    struct p_atient tempPatient;
    int found = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fptr) != NULL)
    {
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);

        if (tempPatient.id == id)
        {
            found = 1;
            printf("Current appointment details:\n");
            printf("Name: %s\n", tempPatient.name);
            printf("Age: %d\n", tempPatient.age);
            printf("ID: %d\n", tempPatient.id);
            printf("Doctor: %s\n", tempPatient.doctor);
            printf("Appointment Date: %s\n", tempPatient.appointmentDate);
            printf("--------------------------------------------------\n");
            printf("Enter new appointment details:\n");
            printf("Enter new patient name: ");
            fflush(stdin);
            scanf("%[^\n]s", tempPatient.name);
            printf("Enter new patient age: ");
            fflush(stdin);
            scanf("%d", &tempPatient.age);
            while (1)
            {
                printf("Enter new patient ID: ");
                scanf("%d", &tempPatient.id);
                if (tempPatient.id > 0)
                {
                    break;
                }
                else
                {
                    printf("Invalid ID. Please enter a positive integer.\n");
                }
            }
            fflush(stdin);
            printf("Enter new doctor's name: ");
            scanf(" %[^\n]s", tempPatient.doctor);
            fflush(stdin);
            printf("Enter new appointment date (DD/MM/YYYY): ");
            scanf(" %[^\n]s", tempPatient.appointmentDate);
            fprintf(tempFptr, "Name : %s, Age : %d, Id : %d, Doctor : %s, Date : %s\n", tempPatient.name, tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
        }
        else
        {
            fprintf(tempFptr, "%s", buffer);
        }
    }
    fclose(fptr);
    fclose(tempFptr);
    if (found)
    {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
        printf("Appointment for patient ID %d has been updated successfully.\n", id);
        printf("--------------------------------------------------\n");
        printf("Thank you for using our service!\n");
        Sleep(1000);
        system("cls");
        appointments();
    }
    else
    {
        printf("No appointment found for patient ID %d.\n", id);
        remove("temp.txt");
    }
}