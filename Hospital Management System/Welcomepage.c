#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "impfunc.h"
int menu();

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
void head(){
    system("cls");
    printf("***************************************\n");
    printf("*                                     *\n");
    printf("*       Hospital Management System     *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
}

void welcomePage()
{
    head();
    printf("Welcome to Hospital Management System \n");
    printf("***************************************\n");
    printf("This program is created by Team Elite \n");
    printf("***************************************\n");
    printf("Press Enter to continue...\n");
    int ch = getch();
    if (ch == 27) // ESC key
    {
        printf("\nESC pressed. Exiting the system. Goodbye!\n");
        exit(0);
    }
    else
    {
        system("cls");
        menuLogin(); // Call the login menu
    }
}

void appointments()
{
    head();
    printf("--------------------------------------------------\n");
    printf("Welcome to appointments Section.\n");
    printf("--------------------------------------------------\n");
    printf("1. Book Appointment\n");
    printf("2. Cancel Appointment\n");
    printf("3. Search Appointments\n");
    printf("4. View Appointments\n");
    printf("5. Update Appointment\n");
    printf("6. Exit to Main Menu\n");
    printf("0. Exit system\n");
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
        printf("Exiting the system back to Main Menu\n");
        Sleep(1000); // Pause for 1 seconds
        system("cls");
        menu(); // Return to main menu
        break;
        case 0:
        printf("Exiting the system. Goodbye!\n");
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
    printf("Press ESC to go back to previous field.\n\n");
    Sleep(1000);
    system("cls");
    struct p_atient newPatient;
    char buffer[100];

    // Name validation
    while (1) {
        if (getInputWithEsc("Enter patient name: ", newPatient.name, sizeof(newPatient.name))) {
            appointments(); return;
        }
        int valid = 1;
        for (int i = 0; newPatient.name[i] != '\0'; i++) {
            if (!isalpha(newPatient.name[i]) && !isspace(newPatient.name[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && strlen(newPatient.name) > 0) break;
        printf("Invalid name! Only letters and spaces allowed.\n");
    }

    // Age validation
    while (1) {
        if (getInputWithEsc("Enter patient age: ", buffer, sizeof(buffer))) { appointments(); return; }
        if (sscanf(buffer, "%d", &newPatient.age) == 1 && newPatient.age >= 0 && newPatient.age <= 100) break;
        printf("Invalid age! Please enter age between 0 and 100.\n");
    }

    // ID validation (minimum 4 digits, unique)
    while (1) {
        if (getInputWithEsc("Enter patient ID: ", buffer, sizeof(buffer))) { appointments(); return; }
        if (sscanf(buffer, "%d", &newPatient.id) == 1 && newPatient.id > 999) {
            // Check for unique ID
            int idExists = 0;
            FILE *checkFptr = fopen("patients.txt", "r");
            char tempBuffer[256];
            if (checkFptr != NULL) {
                while (fgets(tempBuffer, sizeof(tempBuffer), checkFptr) != NULL) {
                    struct p_atient tempPatient;
                    sscanf(tempBuffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, &tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
                    if (tempPatient.id == newPatient.id) { idExists = 1; break; }
                }
                fclose(checkFptr);
            }
            if (idExists) {
                printf("ID already exists. Please enter a unique ID.\n");
                continue;
            }
            break;
        }
        printf("Invalid ID! Must be at least 4 digits.\n");
    }

    // Doctor name validation
    while (1) {
        if (getInputWithEsc("Enter doctor's name: ", newPatient.doctor, sizeof(newPatient.doctor))) { appointments(); return; }
        int valid = 1;
        for (int i = 0; newPatient.doctor[i] != '\0'; i++) {
            if (!isalpha(newPatient.doctor[i]) && !isspace(newPatient.doctor[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && strlen(newPatient.doctor) > 0) break;
        printf("Invalid doctor name! Only letters and spaces allowed.\n");
    }

    // Date validation (format and not before today)
    while (1) {
        if (getInputWithEsc("Enter appointment date (DD/MM/YYYY): ", newPatient.appointmentDate, sizeof(newPatient.appointmentDate))) { appointments(); return; }
        int d, m, y;
        if (sscanf(newPatient.appointmentDate, "%d/%d/%d", &d, &m, &y) == 3 && d > 0 && m > 0 && y > 1900) {
            // Check not before today
            time_t t = time(NULL);
            struct tm *now = localtime(&t);
            int cy = now->tm_year + 1900, cm = now->tm_mon + 1, cd = now->tm_mday;
            if (y > cy || (y == cy && m > cm) || (y == cy && m == cm && d >= cd)) break;
        }
        printf("Invalid date! Enter a valid date (today or future, format DD/MM/YYYY).\n");
    }

    FILE *fptr = fopen("patients.txt", "a");
    if (fptr != NULL) {
        fprintf(fptr, "Name : %s, Age : %d, Id : %d, Doctor : %s, Date : %s\n", newPatient.name, newPatient.age, newPatient.id, newPatient.doctor, newPatient.appointmentDate);
        fclose(fptr);
        printf("--------------------------------------------------\n");
        printf("New appointment booked successfully!\n");
        Sleep(1000);
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
        Sleep(5000);
        system("cls");
        appointments();
    } else {
        printf("Error opening patients.txt for writing!\n");
        printf("Please ensure the file exists and is writable.\n");
        printf("--------------------------------------------------\n");
    }
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
        remove("temp.txt");
    }
}

void searchAppointments()
{
    printf("--------------------------------------------------\n");
    printf("Welcome to Search Appointments Section.\n");
    printf("--------------------------------------------------\n");
    Sleep(1000); // Pause for 1 seconds
    system("cls");
    char name[50]; // Add this at the top of your function if not already present
int id = 0;    // Add this at the top of your function if not already present

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
getchar(); // To consume the newline left by scanf

switch (choice)
{
case 1:
    while (1) {
        printf("Enter the name of the patient: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Remove trailing newline
        int valid = 1;
        for (int i = 0; name[i] != '\0'; i++) {
            if (!isalpha(name[i]) && !isspace(name[i])) {
                valid = 0;
                break;
            }
        }
        if (valid && strlen(name) > 0) break;
        printf("Invalid name! Only letters and spaces allowed.\n");
    }
    break;
case 2:
    printf("Enter the ID of the patient: ");
    scanf("%d", &id);
    break;
default:
    printf("Invalid choice. Please try again.\n");
    goto CHOICE;
}

    FILE *fptr = fopen("patients.txt", "r");
    if (fptr == NULL)
    {
        printf("No appointments found.\n");
        return;
    }
    struct p_atient tempPatient;
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
        sscanf(buffer, "Name : %[^,], Age : %d, Id : %d, Doctor : %[^,], Date : %[^\n]", tempPatient.name, &tempPatient.age, tempPatient.id, tempPatient.doctor, tempPatient.appointmentDate);
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