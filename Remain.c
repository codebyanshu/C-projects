#include "welcomepage02.c"
#include "login.c" 
#include <stdio.h>
int main()
{
    menu1();
    getch();
    system("cls");
    fflush(stdin); // Clear input buffer
    fflush(stdout); // Ensure all output is flushed to the console
    welcomePage();
    getch();
    system("cls");
    int x = menu();
    subparts(x);
    return 0;
}