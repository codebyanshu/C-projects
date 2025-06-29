#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void signup_page();
int check_credentials(const char *username, const char *password);

void login_page()
{
    int ch;
    while (1)
    {
        printf("\n====== Elite Bank Login System ======\n");
        printf("1. Login\n");
        printf("2. Signup\n");
        printf("3. Exit\n");
        printf("Select option: ");
        fflush(stdin);
        scanf("%d", &ch);

        if (ch == 1)
        {
            char username[50], password[50];
            printf("Enter Username: ");
            fflush(stdin);
            scanf("%s", username);
            printf("Enter Password: ");
            fflush(stdin);
            scanf("%s", password);

            if (check_credentials(username, password))
            {
                printf("Login successful! Welcome, %s\n", username);
                break;
            }
            else
            {
                printf("Invalid username or password. Try again.\n");
            }
        }
        else if (ch == 2)
        {
            signup_page();
        }
        else if (ch == 3)
        {
            printf("Exiting...\n");
            exit(0);
        }
        else
        {
            printf("Invalid option. Try again.\n");
        }
    }
}

void signup_page()
{
    char username[50], password[50];
    printf("\n====== Signup Page ======\n");
    int valid, i;

    do
    {
        printf("Choose a Username : ");
        scanf("%99s", username);

        valid = 1;

        for (i = 0; username[i] != '\0'; i++)
        {
            if (!isalpha((unsigned char)username[i]))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Invalid input. Please use letters only.\n");
        }

    } while (!valid);

    // printf("Username accepted: %s\n", username);
    int hasLower, hasUpper, hasDigit, hasSpecial;

    do
    {
        printf("Choose a Password : ");
        scanf("%99s", password);

        hasLower = hasUpper = hasDigit = hasSpecial = 0;
        valid = 1;

        for (i = 0; password[i] != '\0'; i++)
        {
            if (islower((unsigned char)password[i]))
                hasLower = 1;
            else if (isupper((unsigned char)password[i]))
                hasUpper = 1;
            else if (isdigit((unsigned char)password[i]))
                hasDigit = 1;
            else
                hasSpecial = 1;
        }

        if (!(hasLower && hasUpper && hasDigit && hasSpecial))
        {
            printf("Invalid input. Make sure your password includes all character types.\n");
            valid = 0;
        }
        if (strlen(password) < 0)
        {
            printf("Invalid input. The Length should be larger than 5.\n");
            valid = 0;
        }
    } while (!valid);

    FILE *f = fopen("users.txt", "a");
    if (!f)
    {
        printf("Error opening users.txt\n");
        return;
    }
    fprintf(f, "%s %s\n", username, password);
    fclose(f);
    printf("Signup successful! Please login now.\n");
}

int check_credentials(const char *username, const char *password)
{
    char u[50], p[50];
    FILE *f = fopen("users.txt", "r");
    if (!f)
        return 0;
    while (fscanf(f, "%s %s", u, p) == 2)
    {
        if (strcmp(u, username) == 0 && strcmp(p, password) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
