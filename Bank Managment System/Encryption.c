#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// List of allowed characters: A-Z, a-z, 0-9
char allowed[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
int allowedLen = 62;


int getIndex(char ch)
{
    for (int i = 0; i < allowedLen; i++)
    {
        if (allowed[i] == ch)
            return i;
    }
    return -1;
}

int main()
{
    char input[MAX], encrypted[MAX], decrypted[MAX];
    int shift[MAX];

    srand(time(NULL));

    
    printf("Enter text to encrypt: ");
    gets(input);
    // Remove newline
    input[strcspn(input, "\n")] = '\0'; 

    int len = strlen(input);

    // Encrypt
    for (int i = 0; i < len; i++)
    {
        if (input[i] == ' ')
        {
            // space is not encrypted
            encrypted[i] = ' ';
            shift[i] = -1; 
        }
        else
        {
            int idx = getIndex(input[i]);
            if (idx == -1)
            {
                // unsupported character
                encrypted[i] = '?';
                shift[i] = -2;
            }
            else
            {
                // random shift
                int s = rand() % allowedLen; 
                shift[i] = s;
                int newIndex = (idx + s) % allowedLen;
                encrypted[i] = allowed[newIndex];
            }
        }
    }
    encrypted[len] = '\0';

    // Decrypt
    for (int i = 0; i < len; i++)
    {
        if (shift[i] == -1)
        {
            decrypted[i] = ' ';
        }
        else if (shift[i] == -2)
        {
            decrypted[i] = '?';
        }
        else
        {
            int idx = getIndex(encrypted[i]);
            int originalIndex = (idx - shift[i] + allowedLen) % allowedLen;
            decrypted[i] = allowed[originalIndex];
        }
    }
    decrypted[len] = '\0';

    // result
    printf("\nEncrypted text: %s\n", encrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
