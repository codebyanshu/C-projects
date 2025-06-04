#include <stdio.h>
#include <string.h>
#include <windows.h>

void welcomepage();
void printBorder(int width);
void printSpaces(int count);
void margin(int x , int width );

int main() {
    welcomepage();
    return 0;
}

void welcomepage() {
    // Get console width instead of screen width
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.dwSize.X; // Console width in characters

    printBorder(width);

    char message[100] = "Welcome To Hospital Management System";
    int msgLen = strlen(message);
    margin(3 , width);
    printf("|");
    printSpaces((width - msgLen - 2) / 2); 
    
    printf("%s", message);
    
    printSpaces((width - msgLen - 2) / 2); 
    printf("|");
    printf("\n");
    margin(3 ,width);   
    // printBorder(width);
    margin(1,width);
   strcpy(message,"Developed By Team Elite");
    msgLen = strlen(message);
    printf("|");
    printSpaces((width - msgLen - 4)); 
    printf("%s", message);
     printSpaces(2); 
  printf("|");
//   margin(1,width);
  printBorder(width);

}

void printBorder(int width) {
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("\n");
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void margin(int x , int width)
{
    for (int i = 0; i < x; i++)
    {
        printf("|"); printSpaces((width -2 )); printf("|\n");
    }
    
}