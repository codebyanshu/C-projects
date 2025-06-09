#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "impfunc.h"
#include <conio.h>
#include <time.h>

int menu();
void printmenu();
int patientmenu();
int addPatient();
int searchPatient();
int viewAllPatient();
int editPatient();
int deletePatient();

typedef struct Patient
{
    int id;
    char name[50];
    int age;
    char gen;
    char disease[100];
    char admitDate[20];
} patient;

void printmenu()
{

    head();
    printf("--------------------------- \n");
    printf("Patient Management System Menu \n");
    printf("--------------------------- \n");
    printf("1.Add Patient \n");
    printf("2.Search Patient \n");
    printf("3.View All Patient \n");
    printf("4.Edit Patient \n");
    printf("5.Delete Patient \n");
    printf("6.Back to main menu\n");
    printf("0.exit program\n");
    printf("--------------------------- \n");
}

int patientmenu()
{
    int choose;
    do
    {
        system("cls");
        printmenu();
        printf("Enter your choise \n");
        scanf("%d", &choose);
        system("cls");
        switch (choose)
        {
        case 1:
            system("cls");
            addPatient();
            break;
        case 2:
            system("cls");
            searchPatient();
            break;
        case 3:
            system("cls");
            viewAllPatient();
            break;
        case 4:
            system("cls");
            editPatient();
            break;
        case 5:
            system("cls");
            deletePatient();
            break;
        case 6:
            printf("Exitting to main menu.... \n");
            menu();
            break;
        case 0:
            printf("Exitting program.... \n");
            exit(0);
            break;

        default:
            printf("You entered invalid choose \n");
            patientmenu();
            break;
        }
    } while (choose);
}

// Helper: Name validation (only a-z, A-Z, spaces)
int isValidName(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return 0;
    }
    return strlen(name) > 0;
}

// Helper: ID validation (minimum 4 digits)
int isValidID(int id) {
    // return id >= 1000;
    if (id < 1000 || id > 9999) {
        printf("Invalid ID! Please enter a valid ID (minimum 4 digits).\n");
        return 0;
    }
}

// Helper: Date validation (DD/MM/YYYY, not before today)
int isValidDate(const char *dateStr) {
    int d, m, y;
    if (sscanf(dateStr, "%d/%d/%d", &d, &m, &y) != 3) return 0;
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) return 0;

    // Days in month check
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) daysInMonth[1] = 29;
    if (d > daysInMonth[m-1]) return 0;

    // Not before today
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    int cy = now->tm_year + 1900, cm = now->tm_mon + 1, cd = now->tm_mday;
    if (y < cy) return 0;
    if (y == cy && m < cm) return 0;
    if (y == cy && m == cm && d < cd) return 0;

    return 1;
}

int addPatient()
{
    patient p;
    FILE *fptr;
    int idExists = 0;
    char buffer[100];
    int step = 0;

    printf("-----Add New Patient---------- \n");
    printf("Press ESC to go back to previous field.\n\n");

    while (step < 6) {
        switch (step) {
            case 0: // Patient ID
                if (getInputWithEsc("Enter Patient ID: ", buffer, sizeof(buffer))) {
                    if (step == 0) return 0; // ESC on first field: exit
                    step--; continue;
                }
                if (sscanf(buffer, "%d", &p.id) == 1 && isValidID(p.id)) {
                    // Check if ID already exists
                    idExists = 0;
                    fptr = fopen("patient.txt", "r");
                    if (fptr != NULL) {
                        char line[200]; int id;
                        while (fgets(line, sizeof(line), fptr)) {
                            if (sscanf(line, "ID : %d", &id) == 1 && id == p.id) {
                                idExists = 1; break;
                            }
                        }
                        fclose(fptr);
                    }
                    if (idExists) {
                        printf("Patient with ID %d already exists! Please use a unique ID.\n", p.id);
                        printf("\nPress Enter to continue...");
                        getchar();
                        continue;
                    }
                    step++;
                } else {
                    printf("Invalid input! Please enter a valid ID (minimum 4 digits).\n");
                }
                break;
            case 1: // Name
                if (getInputWithEsc("Enter Name: ", p.name, sizeof(p.name))) { step--; continue; }
                if (!isValidName(p.name)) {
                    printf("Invalid Name! Only letters and spaces allowed.\n");
                    continue;
                }
                step++;
                break;
            case 2: // Admit Date
                if (getInputWithEsc("Enter Admit Date (DD/MM/YYYY): ", p.admitDate, sizeof(p.admitDate))) { step--; continue; }
                if (!isValidDate(p.admitDate)) {
                    printf("Invalid Date! Enter a valid date (today or future, format DD/MM/YYYY).\n");
                    continue;
                }
                step++;
                break;
            case 3: // Age
                if (getInputWithEsc("Enter Age: ", buffer, sizeof(buffer))) { step--; continue; }
                if (sscanf(buffer, "%d", &p.age) == 1 && p.age >= 0 && p.age <= 90) {
                    step++;
                } else {
                    printf("Invalid age! Please enter age between 0 and 90.\n");
                }
                break;
            case 4: // Gender
                if (getInputWithEsc("Enter Gender (M/F): ", buffer, sizeof(buffer))) { step--; continue; }
                if ((buffer[0] == 'M' || buffer[0] == 'F' || buffer[0] == 'm' || buffer[0] == 'f') && buffer[1] == '\0') {
                    p.gen = toupper(buffer[0]);
                    step++;
                } else {
                    printf("Invalid gender! Please enter 'M' or 'F'.\n");
                }
                break;
            case 5: // Disease
                if (getInputWithEsc("Enter Disease: ", p.disease, sizeof(p.disease))) { step--; continue; }
                step++;
                break;
        }
    }

    fptr = fopen("patient.txt", "a");
    if (fptr == NULL) {
        printf("Error occuring in file open \n");
        return 0;
    }
    fprintf(fptr, "ID : %d\n", p.id);
    fprintf(fptr, "Name : %s\n", p.name);
    fprintf(fptr, "Admit Date : %s\n", p.admitDate);
    fprintf(fptr, "Age : %d\n", p.age);
    fprintf(fptr, "Gender : %c\n", p.gen);
    fprintf(fptr, "Disease : %s\n", p.disease);
    fclose(fptr);
    printf("Patient added successfully!\n");
    printf("\nPress Enter to continue...");
    getchar();
    return 1;
}

int searchPatient()
{
    FILE *fptr;
    fptr = fopen("patient.txt", "r");
    if (fptr == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    if (size == 0)
    {
        printf("File is empty! No patient records found.\n");
        fclose(fptr);
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        return 0;
    }
    rewind(fptr);

    int searchId, id, found = 0;
    printf("Enter id to search : ");
    scanf("%d", &searchId);

    char str[10000], *line;
    int j = 0;
    char c;
    while ((c = fgetc(fptr)) != EOF)
        str[j++] = c;
    str[j] = '\0';

    line = strtok(str, "\n");
    while (line != NULL)
    {
        if (sscanf(line, "ID : %d", &id) == 1)
        {
            if (id == searchId)
            {
                found = 1;
                printf("FOUND !\nPatient's Details:\n");
                printf("%s\n", line); // ID line
                for (int i = 0; i < 4; i++)
                {
                    line = strtok(NULL, "\n");
                    if (line != NULL)
                        printf("%s\n", line);
                }
                break;
            }
        }
        line = strtok(NULL, "\n");
    }
    if (!found)
        printf("Patient with ID %d not found.\n", searchId);

    fclose(fptr);

    printf("\nPress Enter to continue...");
    getchar();
    getchar(); // Wait for user to see output
}

int viewAllPatient()
{
    FILE *fptr;
    fptr = fopen("patient.txt", "r");
    if (fptr == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    if (size == 0)
    {
        printf("File is empty! No patient records found.\n");
        fclose(fptr);
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        return 0;
    }
    rewind(fptr);

    char str[10000];
    int j = 0;
    char c;
    while ((c = fgetc(fptr)) != EOF)
        str[j++] = c;
    str[j] = '\0';

    printf("All Patient's Details:\n%s\n", str);

    fclose(fptr);

    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

int editPatient()
{
    FILE *fptr, *temp;
    patient p;
    // Open the original file for reading and a temporary file for writing
    // Check if the files opened successfully
    fptr = fopen("patient.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    if (size == 0)
    {
        printf("File is empty! No patient records found.\n");
        fclose(fptr);
        fclose(temp);
        printf("\nPress Enter to continue...");
        getchar();
        getchar();
        return 0;
    }
    rewind(fptr);

    int searchId, id, found = 0;
    printf("Enter id to edit : ");
    scanf("%d", &searchId);
    getchar(); // clear buffer

    char str[10000], *line;
    int j = 0;
    char c;
    while ((c = fgetc(fptr)) != EOF)
        str[j++] = c;
    str[j] = '\0';

    line = strtok(str, "\n");
    while (line != NULL)
    {
        if (sscanf(line, "ID : %d", &id) == 1)
        {
            if (id == searchId)
            {
                found = 1;
                p.id = id;

                // Read next 5 lines for details
                line = strtok(NULL, "\n");
                sscanf(line, "Name : %[^\n]", p.name);
                line = strtok(NULL, "\n");
                sscanf(line, "Admit Date : %[^\n]", p.admitDate);
                line = strtok(NULL, "\n");
                sscanf(line, "Age : %d", &p.age);
                line = strtok(NULL, "\n");
                sscanf(line, "Gender : %c", &p.gen);
                line = strtok(NULL, "\n");
                sscanf(line, "Disease : %[^\n]", p.disease);

                // Show previous details
                printf("Previous Details:\n");
                printf("Name: %s\n", p.name);
                printf("Admit Date: %s\n", p.admitDate);
                printf("Age: %d\n", p.age);
                printf("Gender: %c\n", p.gen);
                printf("Disease: %s\n", p.disease);

                // Enter new details
                printf("Enter new Name: ");
                fgets(p.name, sizeof(p.name), stdin);
                p.name[strcspn(p.name, "\n")] = 0;

                printf("Enter new Admit Date (DD/MM/YYYY): ");
                fgets(p.admitDate, sizeof(p.admitDate), stdin);
                p.admitDate[strcspn(p.admitDate, "\n")] = 0;

                printf("Enter new Age: ");
                while (1)
                {
                    scanf("%d", &p.age);
                    getchar();
                    if (p.age >= 0 && p.age <= 90)
                        break;
                    printf("Invalid age! Please enter age between 0 and 90: ");
                }

                printf("Enter new Gender: ");
                while (1)
                {
                    scanf(" %c", &p.gen);
                    getchar();
                    if (p.gen == 'M' || p.gen == 'F' || p.gen == 'm' || p.gen == 'f')
                    {
                        p.gen = toupper(p.gen);
                        break;
                    }
                    printf("Invalid gender! Please enter 'M' or 'F': ");
                }

                printf("Enter new Disease: ");
                fgets(p.disease, sizeof(p.disease), stdin);
                p.disease[strcspn(p.disease, "\n")] = 0;

                // Write updated details to temp file
                fprintf(temp, "ID : %d\nName : %s\nAdmit Date : %s\nAge : %d\nGender : %c\nDisease : %s\n",
                        p.id, p.name, p.admitDate, p.age, p.gen, p.disease);
            }
            else
            {
                // Write this patient as is
                fprintf(temp, "%s\n", line);
                for (int i = 0; i < 4; i++)
                {
                    line = strtok(NULL, "\n");
                    if (line != NULL)
                        fprintf(temp, "%s\n", line);
                }
            }
        }
        line = strtok(NULL, "\n");
    }

    fclose(fptr);
    fclose(temp);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");

    if (found)
    {
        printf("---------------------------------------------------\n");
        printf("Patient with ID %d updated successfully!\n", searchId);
        printf("Updated Details:\n");
        printf("Name: %s\n", p.name);
        printf("Admit Date: %s\n", p.admitDate);
        printf("Age: %d\n", p.age);
        printf("Gender: %c\n", p.gen);
        printf("Disease: %s\n", p.disease);
    }
    else
    {
        printf("Patient with ID %d not found.\n", searchId);
    }
    // Wait for user to see output
    printf("\nPress Enter to continue...");
    getchar();
}

int deletePatient()
{
    FILE *fptr, *temp;
    patient p;
    fptr = fopen("patient.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }
    int searchId, id, found = 0;
    printf("Enter id to delete : ");
    scanf("%d", &searchId);

    char str[10000], *line;
    int j = 0;
    char c;
    // Read whole file into str
    while ((c = fgetc(fptr)) != EOF)
        str[j++] = c;
    str[j] = '\0';

    line = strtok(str, "\n");
    while (line != NULL)
    {
        if (sscanf(line, "ID : %d", &id) == 1)
        {
            if (id == searchId)
            {
                found = 1;
                p.id = id;
                // Read and store next 5 lines for details
                line = strtok(NULL, "\n");
                sscanf(line, "Name : %[^\n]", p.name);
                line = strtok(NULL, "\n");
                sscanf(line, "Admit Date : %[^\n]", p.admitDate);
                line = strtok(NULL, "\n");
                sscanf(line, "Age : %d", &p.age);
                line = strtok(NULL, "\n");
                sscanf(line, "Gender : %c", &p.gen);
                line = strtok(NULL, "\n");
                sscanf(line, "Disease : %[^\n]", p.disease);
            }
            else
            {
                // Write this patient as is
                fprintf(temp, "%s\n", line);
                for (int i = 0; i < 4; i++)
                {
                    line = strtok(NULL, "\n");
                    fprintf(temp, "%s\n", line);
                }
            }
        }
        line = strtok(NULL, "\n");
    }

    fclose(fptr);
    fclose(temp);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");

    if (found)
    {
        // Show previous details before deleting
        printf("---------------------------------------------------\n");
        printf("Previous Details (to be deleted):\n");
        printf("Name: %s\n", p.name);
        printf("Admit Date: %s\n", p.admitDate);
        printf("Age: %d\n", p.age);
        printf("Gender: %c\n", p.gen);
        printf("Disease: %s\n", p.disease);
        printf("---------------------------------------------------\n");
        printf("Patient with ID %d deleted successfully!\n", searchId);
        printf("---------------------------------------------------\n");
    }
    else
    {
        printf("Patient with ID %d not found.\n", searchId);
    }
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
