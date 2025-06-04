#include "welcomepage02.c"

#include <stdio.h>
int main()
{
    welcomePage();
    getch();
    system("cls");
    int x = menu();
    subparts(x);
    return 0;
}