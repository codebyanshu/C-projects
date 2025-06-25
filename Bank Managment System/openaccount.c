#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct accountcreate
{
    char name[50];
    char father_name[50];
    char mobile_no[15];
    char email[50];
    char date_of_birth[50];
    char user_id[10];
};
void account();
void view();
void modify();
void delete();
// function no 1, create account.
void account()
{
    struct accountcreate user;
    printf("~~~Welcome To Account Managment Page~~~ \n");
    printf("Enter your Name:-");
    scanf("%s", user.name);
    while (strlen(user.name) < 4)
    {
        printf("Name must be at least 4 characters long.\n ");
        scanf("%s", user.name);
    }

    printf("Enter your Father Name:-");
    scanf("%s", user.father_name);
    while (strlen(user.father_name) < 4)
    {
        printf("Father Name must be at least 4 characters long.\n ");
        scanf("%s", user.father_name);
    }

    printf("Enter your Mobile Number:-");
    scanf("%s", user.mobile_no);
    while (strlen(user.mobile_no) < 10)
    {
        printf("Mobile No. must be at least 10 characters long.\n ");
        scanf("%s", user.mobile_no);
    }

    printf("Enter your Email:-");
    scanf("%s", user.email);
    while (strstr(user.email, "@gmail.com") == NULL)
    {
        printf("Invalid email! Email must contain '@gmail.com'.\n ");
        scanf("%s", user.email);
    }

    printf("Enter your Date Of Birth:-");
    scanf("%s", user.date_of_birth);
    printf("Enter your id:-");
    scanf("%s", user.user_id);
    while (strlen(user.user_id) < 12)
    {
        printf("Id must be at least 10 characters long.\n ");
        scanf("%s", user.user_id);
    }

    FILE *fptr = fopen("accountInfo.txt", "a");

    if (fptr == NULL)
    {
        printf("error in file opening \n");
        return;
    }
    fprintf(fptr, "Full Name :- %s\n", user.name);
    fprintf(fptr, "Father Name :- %s\n", user.father_name);
    fprintf(fptr, "Mobile No :- %s\n", user.mobile_no);
    fprintf(fptr, "Email :- %s\n", user.email);
    fprintf(fptr, "Date Of Birth :- %s\n", user.date_of_birth);
    fprintf(fptr, "Id :- %s\n", user.user_id);
    fclose(fptr);
    printf("Your Account Is Successfully Created");
}
void account_menu()
{
    int Number;
    printf("~~~Welcome To Account Managment Page~~~  \n\n");
    printf("Options:- \n");
    printf("1.Create Account \n");
    printf("2.view \n");
    printf("3.Modify \n");
    printf("4.Delete\n");
    printf("5.Exit\n");
    printf("Please Select Any Option:-");
    scanf("%d", &Number);
    switch (Number)
    {
    case 1:
        account();
        break;
    case 2:
        view();
        break;
    case 3:
        modify();
        break;
    case 4:
        delete();
        break;
    case 5:
        exit(0);
        break;
    default:
        printf("invalid input");

        break;
    }
}
// int main()
// {
    // account_menu();
//     return 0;
// }
// // Function no. 2 , view details.
void view()
{
    struct accountcreate user;
    FILE *fptr = fopen("login1.txt", "r");

    if (fptr == NULL)
    {
        printf("error in file opening \n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fptr))
    {
        printf("%s", line);
    }
}
// Function No.3 , modify account detail:
void modify()
{
    struct accountcreate user;
    char search_id[10];
    int found = 0;
    FILE *fptr = fopen("login1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }

    printf("Enter your ID to modify: ");
    scanf("%s", search_id);
    while (fscanf(fptr, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nId :- %s\n",
                  user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.user_id) != EOF)
    {

        if (strcmp(user.user_id, search_id) == 0)
        {
            found = 1;
            printf("Account found! Enter new details:\n");
            printf("Enter Name: ");
            scanf("%s", user.name);
            printf("Enter Father Name: ");
            scanf("%s", user.father_name);
            printf("Enter Mobile Number: ");
            scanf("%s", user.mobile_no);
            printf("Enter Email: ");
            scanf("%s", user.email);
            printf("Enter Date Of Birth: ");
            scanf("%s", user.date_of_birth);
        }

        fprintf(temp, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nId :- %s\n",
                user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.user_id);
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("login1.txt");
        rename("temp.txt", "login1.txt");
        printf("Account modified successfully!\n");
    }
    else
    {
        printf("ID not found.\n");
    }
}
// function no. 4, delete an account:
void delete()
{
    struct accountcreate user;
    char search_id[10];
    int found = 0;
    FILE *fptr = fopen("login1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fptr == NULL || temp == NULL)
    {
        printf("Error in file opening.\n");
        return;
    }

    printf("Enter your ID for delete an account: ");
    scanf("%s", search_id);
    while (fscanf(fptr, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nId :- %s\n",
                  user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.user_id) != EOF)
    {
        if (strcmp(user.user_id, search_id) == 0)
        {
            found = 1;
            printf("Account has been found and delete.\n");
        }

        fprintf(temp, "Full Name :- %s\nFather Name :- %s\nEmail :- %s\nMobile No :- %s\nDate Of Birth :- %s\nId :- %s\n",
                user.name, user.father_name, user.email, user.mobile_no, user.date_of_birth, user.user_id);
    }

    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("login1.txt");
        rename("temp.txt", "login1.txt");
        printf("Account Has Been Deleted Successesfully");
    }
    else
    {
        printf("ID not found.\n");
    }
}
