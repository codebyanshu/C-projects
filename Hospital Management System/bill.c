#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "createbill.c"

int menu();

typedef struct
{
    int billId;
    int patientId;
    char patientName[50];
    float totalAmount;
    // ... aur bhi fields add kar sakte hain ...
} BillSummary;

void searchBill();
void viewAllBills();
void editBill();
void deleteBill();
void printBill();

void billMenu()
{
    int choice;
    do
    {
        system("cls");
        head(); // <-- Add this line
        printf("--------------------------------------------------\n");
        printf("Welcome to Billing Section.\n");
        printf("--------------------------------------------------\n");
        printf("1. Create New Bill\n");
        printf("2. Search Bill\n");
        printf("3. View All Bills\n");
        printf("4. Edit Bill\n");
        printf("5. Delete Bill\n");
        printf("6. Print Bill\n");
        printf("7. Back to Main\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            createbill(NULL, 0); // New bill, so patient ID user se lo
            break;
        case 2:
            searchBill();
            break;
        case 3:
            viewAllBills();
            break;
        case 4:
            editBill();
            break;
        case 5:
            deleteBill();
            break;
        case 6:
            printBill();
            break;
        case 7:
            printf("Exiting Bill Management...\n");
            // Sleep(1000); // Optional: Pause for 1 second
            system("cls");
            menu(); // Return to main menu
            break;
        case 0:
            printf("Exiting the system. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

// Function Definitions
void searchBill()
{
    int searchId, found = 0;
    char line[500];
    printf("Enter Bill ID or Patient ID to search: ");
    scanf("%d", &searchId);
    FILE *fptr = fopen("bill.txt", "r");
    if (!fptr)
    {
        printf("No bills found!\n");
        return;
    }
    while (fgets(line, sizeof(line), fptr))
    {
        if (strstr(line, "Patient ID:"))
        {
            int pid;
            sscanf(line, "Patient ID: %d", &pid);
            if (pid == searchId)
            {
                found = 1;
                printf("\n--- Bill Found ---\n");
                printf("%s", line);
                // Print rest of bill
                for (int i = 0; i < 30 && fgets(line, sizeof(line), fptr); i++)
                {
                    printf("%s", line);
                    if (strstr(line, "Thank you"))
                        break;
                }
                break;
            }
        }
    }
    fclose(fptr);
    if (!found)
        printf("Bill not found!\n");
}

void viewAllBills()
{
    char line[500];
    FILE *fptr = fopen("bill.txt", "r");
    if (!fptr)
    {
        printf("No bills found!\n");
        return;
    }
    printf("\n--- All Bills ---\n");
    while (fgets(line, sizeof(line), fptr))
    {
        printf("%s", line);
    }
    fclose(fptr);
}

void editBill()
{
    int editId, found = 0;
    char line[500];
    printf("Enter Patient ID of bill to edit: ");
    scanf("%d", &editId);

    FILE *fptr = fopen("bill.txt", "r");
    FILE *temp = fopen("tempbill.txt", "w");
    if (!fptr || !temp)
    {
        printf("File error!\n");
        if (fptr)
            fclose(fptr);
        if (temp)
            fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), fptr))
    {
        // Bill block ki shuruaat header se hoti hai
        if (strstr(line, "================== HOSPITAL BILL =================="))
        {
            // Next line me Patient ID check karo
            char nextLine[500];
            if (fgets(nextLine, sizeof(nextLine), fptr))
            {
                int pid;
                if (sscanf(nextLine, "Patient ID: %d", &pid) == 1 && pid == editId)
                {
                    found = 1;
                    // Print old bill for reference
                    printf("\n--- Old Bill ---\n");
                    printf("%s", line);     // header
                    printf("%s", nextLine); // patient id
                    // Print rest of bill to screen
                    for (int i = 0; i < 40 && fgets(line, sizeof(line), fptr); i++)
                    {
                        printf("%s", line);
                        if (strstr(line, "Thank you"))
                            break;
                    }
                    printf("\nEnter new bill details:\n");
                    // Write new bill to temp file, pass editId
                    createbill(temp, editId);
                    // Skip lines till end of this bill (footer tak)
                    while (fgets(line, sizeof(line), fptr))
                    {
                        if (strstr(line, "Thank you"))
                        {
                            // Footer ki last line bhi skip karo
                            fgets(line, sizeof(line), fptr);
                            break;
                        }
                    }
                    continue;
                }
                else
                {
                    // Agar yeh editId nahi hai, to header + patient id line copy karo
                    fputs(line, temp);
                    fputs(nextLine, temp);
                    continue;
                }
            }
        }
        // Copy line to temp file
        fputs(line, temp);
    }
    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("bill.txt");
        rename("tempbill.txt", "bill.txt");
        printf("Bill updated successfully!\n");
    }
    else
    {
        remove("tempbill.txt");
        printf("Bill not found!\n");
    }
}

void deleteBill()
{
    int delId, found = 0;
    char line[500];
    printf("Enter Patient ID of bill to delete: ");
    scanf("%d", &delId);

    FILE *fptr = fopen("bill.txt", "r");
    FILE *temp = fopen("tempbill.txt", "w");
    if (!fptr || !temp)
    {
        printf("File error!\n");
        if (fptr)
            fclose(fptr);
        if (temp)
            fclose(temp);
        return;
    }

    while (fgets(line, sizeof(line), fptr))
    {
        // Bill block ki shuruaat header se hoti hai
        if (strstr(line, "================== HOSPITAL BILL =================="))
        {
            // Next line me Patient ID check karo
            char nextLine[500];
            if (fgets(nextLine, sizeof(nextLine), fptr))
            {
                int pid;
                if (sscanf(nextLine, "Patient ID: %d", &pid) == 1 && pid == delId)
                {
                    found = 1;
                    // Print deleted bill for reference
                    printf("\n--- Bill Deleted ---\n");
                    printf("%s", line);     // header
                    printf("%s", nextLine); // patient id
                    // Print rest of bill to screen
                    for (int i = 0; i < 40 && fgets(line, sizeof(line), fptr); i++)
                    {
                        printf("%s", line);
                        if (strstr(line, "Thank you"))
                            break;
                    }
                    // Skip lines till end of this bill (footer tak)
                    while (fgets(line, sizeof(line), fptr))
                    {
                        if (strstr(line, "Thank you"))
                        {
                            // Footer ki last line bhi skip karo
                            fgets(line, sizeof(line), fptr);
                            break;
                        }
                    }
                    continue;
                }
                else
                {
                    // Agar yeh delId nahi hai, to header + patient id line copy karo
                    fputs(line, temp);
                    fputs(nextLine, temp);
                    continue;
                }
            }
        }
        // Copy line to temp file
        fputs(line, temp);
    }
    fclose(fptr);
    fclose(temp);

    if (found)
    {
        remove("bill.txt");
        rename("tempbill.txt", "bill.txt");
        printf("Bill deleted successfully!\n");
    }
    else
    {
        remove("tempbill.txt");
        printf("Bill not found!\n");
    }
}
void printBill()
{
    int pid, found = 0;
    char line[500];
    printf("Enter Patient ID to print bill: ");
    scanf("%d", &pid);

    FILE *fptr = fopen("bill.txt", "r");
    FILE *out = fopen("printbill.txt", "w");
    if (!fptr || !out)
    {
        printf("File error!\n");
        if (fptr)
            fclose(fptr);
        if (out)
            fclose(out);
        return;
    }

    // Header sirf ek baar print karein
    fprintf(out, "================== HOSPITAL BILL ==================\n");

    while (fgets(line, sizeof(line), fptr))
    {
        if (strstr(line, "Patient ID:"))
        {
            int tempId;
            sscanf(line, "Patient ID: %d", &tempId);
            if (tempId == pid)
            {
                found = 1;
                fputs(line, out);
                // Copy rest of bill (including full footer)
                while (fgets(line, sizeof(line), fptr))
                {
                    fputs(line, out);
                    // Footer ki last line ke baad break
                    if (strstr(line, "Thank you for choosing our hospital!"))
                    {
                        // Copy the next line (footer ka last line)
                        if (fgets(line, sizeof(line), fptr))
                            fputs(line, out);
                        break;
                    }
                }
                break;
            }
        }
    }

    // Footer sirf ek baar print hoga
    if (found)
    {
        printf("Bill printed to printbill.txt successfully!\n");
    }
    else
    {
        printf("Bill not found!\n");
        remove("printbill.txt");
    }

    fclose(fptr);
    fclose(out);
}