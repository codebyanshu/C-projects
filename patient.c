#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void printmenu();
int patientmenu();
int addPatient();
int searchPatient();
int viewAllPatient();
typedef struct patient
{
    int id;
    char name[50];
    int age;
    char gen;
    char disease[100];
} patient;
int main()
{
    patientmenu();
    return 0;
}
void printmenu()
{
    printf("-----PATIENT MANAGMENT ------ \n");
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
        printmenu();
        printf("Enter your choise \n");
        scanf("%d", &choose);
        system("cls");
        switch (choose)
        {
        case 1:
            addPatient();
            break;
        case 2:
            searchPatient();
            break;
        case 3:
            viewAllPatient();
            break;
        case 0:
            printf("Exitting program.... \n");
            break;

        default:
            printf("You entered invalid choose \n");
            break;
        }
    } while (choose);
}
int addPatient()
{
    patient p;
    FILE *fptr;
    fptr = fopen("patient.txt", "a");
    if (fptr == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }

    printf("-----Add New Patient---------- \n");
    printf("Enter Patient ID :- \n");
    scanf("%d", &p.id);
    getchar();
    printf("Enter Name :- \n");
    gets(p.name);
    printf("Enter Age :- \n");
    scanf("%d", &p.age);
    getchar();
    printf("Enter Gender :- \n");
    printf("'M' for male and 'F' for female\n");
    scanf("%c", &p.gen);
    printf("Enter Disease :- \n");
    scanf("%s", &p.disease);

    // fprintf(fptr,"ID : %d\nName : %s\nAge : %d\nGender : %c\nDisease :  %s\n",p.id,p.name,p.age,p.gen,p.disease);
    fprintf(fptr, "ID : %d\n", p.id);
    fprintf(fptr, "Name : %s\n", p.name);
    fprintf(fptr, "Age : %d\n", p.age);
    fprintf(fptr, "Gender : %c\n", p.gen);
    fprintf(fptr, "Disease : %s\n", p.disease);
    fclose(fptr);
    printf("Patient added successfully!\n");
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
    int searchId;
    char str[200];
    int id;
    printf("Enter id to search : ");
    scanf("%d", &searchId);
    char c;
    int j;
    int printing = 0;
    char *line;
    for (int i = 0; (c = fgetc(fptr)) != EOF; i++)
    {
        str[i] = c;
        j = i;
    }
    str[j] = '\0';
    line = strtok(str, "\n");

    while (line != NULL)
    {
        if (strncmp(line, "ID", 2) == 0)
        {

            if (sscanf(line, "ID : %d", &id))
            {

                if (id == searchId)
                {
                    printing = 1;
                    printf("FOUND ! \n");
                    printf("Patient's Details : \n");
                    printf(" %s\n", line);
                }
                else if (printing)
                {
                    break;
                }
            }
        }
        else if (printing)
        {
            printf(" %s\n", line);
        }
        line = strtok(NULL, "\n");
    }

    fclose(fptr);
}
int viewAllPatient()
{
    FILE *fptr;
    fptr = fopen("patient.txt", "r");
    char str[200];
    if (fptr == NULL)
    {
        printf("Error occuring in file open \n");
        return 0;
    }
    char c;
    int j;
    int printing = 0;
    for (int i = 0; (c = fgetc(fptr)) != EOF; i++)
    {
        str[i] = c;
        j = i;
    }
    str[j] = '\0';
    printf("All Patient's Details : \n%s\n", str);
    fclose(fptr);
}