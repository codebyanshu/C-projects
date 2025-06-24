#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

struct Score
{
    char name[50];
    int moves;
};

void shuffle(char symbols[], char result[]);
void display(char board[4][4], int revealed[4][4], int r1, int c1, int r2, int c2);
void hideboard(char board[4][4], int revealed[4][4], int boxrow, int boxcol);
void loadingAnimation();
void playgame(struct Score *best);

int welcomecard()
{
    struct Score best = {"None", 0};
    while (1)
    {
        playgame(&best);
    }
    return 0;
}

void playgame(struct Score *best)
{
    int r1 = -1, r2 = -1, c1 = -1, c2 = -1;
    char board[4][4];
    int revealed[4][4] = {0};
    char symbols[] = "AABBCCDDEEFFGGHH";
    char shuffled[17];
    int pair = 0, move = 0;
    int boxrow = 0, boxcol = 0, selecte = 0;
    int key;

    shuffle(symbols, shuffled);

    int k = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            board[i][j] = shuffled[k++];
        }
    }

    while (pair < 8)
    {
        selecte = 0;
        r1 = r2 = c1 = c2 = -1;

        // SELECT LOOP
        while (1)
        {
            system("cls");
            printf("Best Score: %s - %d moves\n", best->name, best->moves);
            hideboard(board, revealed, boxrow, boxcol);
            printf("\nENTER to select, \nESC to exit...\n");

            key = getch();
            if (key == 224)
            {
                key = getch();
                if (key == 72 && boxrow > 0)
                    boxrow--;
                if (key == 80 && boxrow < 3)
                    boxrow++;
                if (key == 75 && boxcol > 0)
                    boxcol--;
                if (key == 77 && boxcol < 3)
                    boxcol++;
            }
            else if (key == 13)
            {
                if (revealed[boxrow][boxcol] == 1)
                    continue;

                if (selecte == 0)
                {
                    r1 = boxrow;
                    c1 = boxcol;
                    selecte = 1;
                }
                else if (selecte == 1 && !(r1 == boxrow && c1 == boxcol))
                {
                    r2 = boxrow;
                    c2 = boxcol;
                    break;
                }
            }
            else if (key == 27)
            {
                exit(0);
            }
        }

        system("cls");
        display(board, revealed, r1, c1, r2, c2);
        Sleep(2000);
        move++;

        if (board[r1][c1] == board[r2][c2])
        {
            loadingAnimation();
            revealed[r1][c1] = 1;
            revealed[r2][c2] = 1;
            pair++;
            printf("Match!\n");
        }
        else
        {
            printf("Not a match!\n");
        }

        Sleep(1000);
    }

    system("cls");
    hideboard(board, revealed, boxrow, boxcol);
    printf("\nCongratulations You won in %d moves!\n", move);

    if (move < best->moves)
    {
        printf("New Best Score!\nEnter your name: ");
        scanf("%s", best->name);
        best->moves = move;
    }

    printf("\nPress Enter to play again or ESC to quit...\n");
    key = getch();
    if (key == 13)
    {
        welcomecard();
    }
    else if (key == 27)
    {
        exit(0);
    }
}

// SHUFFLE
void shuffle(char symbols[], char result[])
{
    srand(time(NULL));
    for (int i = 0; i < 16; i++)
        result[i] = symbols[i];
    result[16] = '\0';

    for (int i = 15; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

// DISPLAY
void display(char board[4][4], int revealed[4][4], int r1, int c1, int r2, int c2)
{
    printf("Current Board:\n\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (revealed[i][j] == 1 || (i == r1 && j == c1) || (i == r2 && j == c2))
                printf(" %c\t", board[i][j]);
            else
                printf(" *\t");
        }
        printf("\n");
    }
}

// HIDEBOARD
void hideboard(char board[4][4], int revealed[4][4], int boxrow, int boxcol)
{
    printf("Use arrow keys up,down,right and left to move. \nPress ENTER to select.\n\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == boxrow && j == boxcol)
            {
                printf("[*]\t");
                // printf(" [%c]\t", board[i][j]);
            }
            else if (revealed[i][j] == 1)
            {
                printf(" %c\t", board[i][j]);
            }
            else
            {
                printf(" *\t");
            }
        }
        printf("\n");
    }
}

// LOADING ANIMATION
void loadingAnimation()
{
    char dots[] = ". . .";
    for (int i = 0; i < 3; i++)
    {
        printf("\rChecking%s", dots + i);
        Sleep(300);
    }
    printf("\n");
}
