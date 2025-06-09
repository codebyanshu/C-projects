#ifndef LOGIN_PAGE_3_H
#define LOGIN_PAGE_3_H

struct signinformation;
void menuLogin();
void login();
void signUp();
void checkInfo();
int checkPasswordStrength(const char password[]);

#endif

#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include <stdio.h>
#include <conio.h>

int getInputWithEsc(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    int idx = 0, ch;
    while (1) {
        ch = getch();
        if (ch == 27) { // ESC key
            buffer[0] = '\0';
            printf("\n");
            return 1;
        }
        if (ch == '\r' || ch == '\n') {
            buffer[idx] = '\0';
            printf("\n");
            break;
        }
        if (ch == 8) {
            if (idx > 0) {
                idx--;
                printf("\b \b");
            }
        } else if (idx < size - 1 && ch >= 32 && ch <= 126) {
            buffer[idx++] = ch;
            printf("%c", ch);
        }
    }
    return 0;
}

#endif