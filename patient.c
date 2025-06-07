#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void header()
{
    printf("***************************************\n");
    printf("*                                     *\n");
    printf("*       Patient Management System     *\n");
    printf("*                                     *\n");
    printf("***************************************\n");
    printf("Welcome to Patient Management System \n");
    printf("***************************************\n");
    printf("This program is created by Team Elite \n");
    printf("***************************************\n");
}

void printmenu();
int patientmenu();
int addPatient();
int searchPatient();
int viewAllPatient();
int editPatient();
int deletePatient();

typedef struct patient2
{
    int id;
    char name[50];
    int age;
    char gen;
    char disease[100];
    char admitDate[20];
} patient;

int main()
{
    // header();
    // printf("Welcome to Patient Management System \n");
    // printf("This program is created by Team Elite \n");
    patientmenu();
    return 0;
}

void printmenu()
{

    header();
    printf("--------------------------- \n");
    printf("Patient Management System Menu \n");
    printf("--------------------------- \n");
    printf("1.Add Patient \n");
    printf("2.Search Patient \n");
    printf("3.View All Patient \n");
    printf("4.Edit Patient \n");
    printf("5.Delete Patient \n");
    printf("0.Back to main menu\n");
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
        case 0:
            printf("Exitting program.... \n");
            // menu();
            break;

        default:
            printf("You entered invalid choose \n");
            patientmenu();
            break;
        }
    } while (choose);
}

int addPatient()
{
    patient p;
    FILE *fptr;
    int idExists = 0;
    printf("-----Add New Patient---------- \n");
    printf("Enter Patient ID :- \n");
    scanf("%d", &p.id);
    getchar();

    // Check if ID already exists
    fptr = fopen("patient.txt", "r");
    if (fptr != NULL)
    {
        char line[200];
        int id;
        while (fgets(line, sizeof(line), fptr))
        {
            if (sscanf(line, "ID : %d", &id) == 1)
            {
                if (id == p.id)
                {
                    idExists = 1;
                    break;
                }
            }
        }
        fclose(fptr);
    }
    if (idExists)
    {
        printf("Patient with ID %d already exists! Please use a unique ID.\n", p.id);
        printf("\nPress Enter to continue...");
        getchar();
        return 0;
    }

    fptr = fopen("patient.txt", "a");
    if (fptr == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }

    printf("Enter Name :- \n");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Enter Admit Date (DD/MM/YYYY):\n");
    fgets(p.admitDate, sizeof(p.admitDate), stdin);
    p.admitDate[strcspn(p.admitDate, "\n")] = 0;

    printf("Enter Age :- \n");
    while (1)
    {
        scanf("%d", &p.age);
        getchar();
        if (p.age >= 0 && p.age <= 90)
            break;
        printf("Invalid age! Please enter age between 0 and 90: ");
    }

    printf("Enter Gender :- \n");
    printf("'M' for male and 'F' for female\n");
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
    printf("Enter Disease :- \n");
    fgets(p.disease, sizeof(p.disease), stdin);
    p.disease[strcspn(p.disease, "\n")] = 0;

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
