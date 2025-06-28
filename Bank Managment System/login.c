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
        scanf("%d", &ch);

        if (ch == 1)
        {
            char username[50], password[50];
            printf("Enter Username: ");
            scanf("%s", username);
            printf("Enter Password: ");
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
    printf("Choose a Username: ");
    scanf("%s", username);
    printf("Choose a Password: ");
    scanf("%s", password);

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