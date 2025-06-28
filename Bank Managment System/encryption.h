
#ifndef LOGIN_H
#define LOGIN_H

void login_page();

#endif

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string.h>
#include <stdlib.h>
#include <time.h>

void decrypt_caesar(const char *src, char *dest, int shift);

static char allowed[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static int allowedLen = 62;

// Encrypts src into dest, returns shift array (must be freed by caller)
static void encrypt(const char *src, char *dest, int *shift) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        if (src[i] == ' ') {
            dest[i] = ' ';
            shift[i] = -1;
        } else {
            int idx = -1;
            for (int j = 0; j < allowedLen; j++)
                if (allowed[j] == src[i]) { idx = j; break; }
            if (idx == -1) {
                dest[i] = '?';
                shift[i] = -2;
            } else {
                int s = rand() % allowedLen;
                shift[i] = s;
                int newIndex = (idx + s) % allowedLen;
                dest[i] = allowed[newIndex];
            }
        }
    }
    dest[len] = '\0';
}

static void decrypt(const char *src, char *dest, int *shift) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        if (shift[i] == -1) {
            dest[i] = ' ';
        } else if (shift[i] == -2) {
            dest[i] = '?';
        } else {
            int idx = -1;
            for (int j = 0; j < allowedLen; j++)
                if (allowed[j] == src[i]) { idx = j; break; }
            int originalIndex = (idx - shift[i] + allowedLen) % allowedLen;
            dest[i] = allowed[originalIndex];
        }
    }
    dest[len] = '\0';
}

void simple_decrypt(const char *src, char *dest, int shift) {
    int len = strlen(src);
    for (int i = 0; i < len; i++) {
        if (src[i] >= 'A' && src[i] <= 'Z')
            dest[i] = ((src[i] - 'A' - shift + 26) % 26) + 'A';
        else if (src[i] >= 'a' && src[i] <= 'z')
            dest[i] = ((src[i] - 'a' - shift + 26) % 26) + 'a';
        else if (src[i] >= '0' && src[i] <= '9')
            dest[i] = ((src[i] - '0' - shift + 10) % 10) + '0';
        else
            dest[i] = src[i];
    }
    dest[len] = '\0';
}

void decrypt_caesar(const char *src, char *dest, int shift) {
    int i;
    for (i = 0; src[i]; i++) {
        if (src[i] >= 'A' && src[i] <= 'Z')
            dest[i] = ((src[i] - 'A' - shift + 26) % 26) + 'A';
        else if (src[i] >= 'a' && src[i] <= 'z')
            dest[i] = ((src[i] - 'a' - shift + 26) % 26) + 'a';
        else if (src[i] >= '0' && src[i] <= '9')
            dest[i] = ((src[i] - '0' - shift + 10) % 10) + '0';
        else
            dest[i] = src[i];
    }
    dest[i] = '\0';
}

#endif
