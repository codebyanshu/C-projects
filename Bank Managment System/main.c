#include <stdio.h>
#include <stdlib.h>
#include "encryption.h"
#include "openaccount.c"
#include "bankloansystem.c"
#include "banktransection.c"
#include "Accountsorting.c"
#include "login.c"

int main()
{
    login_page();

    int choice;

    while (1)
    {
        printf("\n\n********** Welcome to Elite Bank **********\n");
        printf("1. Open an Account\n");
        printf("2. Loan Services\n");
        printf("3. Deposit and withdraw\n");
        printf("4. Exit\n");
        printf("Select an option (1-4): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            account_menu();
            break;
        case 2:
            main2();
            break;
        case 3:
            menu();
            break;
        case 4:
            printf("Thank you for banking with us, Love!\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}