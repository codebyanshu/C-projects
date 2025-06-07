#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


int main(int argc, char const *argv[])
{
    printf("--------------------------------------------------\n");
    printf("Welcome to the Patient Management System.\n");
    FILE *fptr = fopen("patients.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening patients.txt for reading!\n");
        return 1;
    }


    char buffer[256]; // Buffer to read lines
    fgets(buffer, 256,fptr);
    if (fptr == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    printf("%s", buffer);
    

    return 0;
}
