#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
void gameloop();
void setupBoards();
void placeMines();
void printBoard();
void reveal(int r, int c);
int checkwin();

#define SIZE 9
#define MINES 10

char displayBoard[SIZE][SIZE];
int mineBoard[SIZE][SIZE];
int revealed[SIZE][SIZE];
int boxRow = 0, boxCol = 0;
int score = 0;

int MiningGame()
{
    srand(time(NULL));
    setupBoards();
    placeMines();
    gameloop();
    return 0;
}

void setupBoards()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            displayBoard[i][j] = '*';
            mineBoard[i][j] = 0;
            revealed[i][j] = 0;
        }
    }
}

void placeMines()
{
    int count = 0;
    while (count < MINES)
    {
        int r = rand() % SIZE;
        int c = rand() % SIZE;

        if (mineBoard[r][c] == 0)
        {

            mineBoard[r][c] = -1;
            count++;
        }
    }

    // add mine counts to non mine cells
    int i, j, dr, dc;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (mineBoard[i][j] == -1)
            {
                continue;
            }
            int mines = 0;
            for (dr = -1; dr <= 1; dr++)
            {
                for (dc = -1; dc <= 1; dc++)
                {
                    int ni = i + dr, nj = j + dc;
                    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && mineBoard[ni][nj] == -1)
                    {
                        mines++;
                    }
                }
            }
            mineBoard[i][j] = mines;
        }
    }
}

void printBoard()
{
    int i, j;
    system("cls");
    printf("Use arrow keys to move, ENTER to open cell, ESC to exit, R to restart.\n");
    printf("Goal: Avoid mines!\n");
    printf("Score: %d\n\n", score);

    // Print column numbers
    printf("   ");
    for (j = 0; j < SIZE; j++)
        printf("   "); // Remove numbers, just spacing
    printf("\n");

    for (i = 0; i < SIZE; i++)
    {
        printf("   "); // Remove row numbers, just spacing
        for (j = 0; j < SIZE; j++)
        {
            if (i == boxRow && j == boxCol)
            {
                printf("[%c] ", displayBoard[i][j]);
            }
            else
            {
                printf(" %c  ", displayBoard[i][j]);
            }
        }
        printf("\n");
    }
}

void reveal(int r, int c)
{
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || revealed[r][c])
    {
        return;
        revealed[r][c] = 1;
    }
    score++;

    if (mineBoard[r][c] == -1)
    {
        displayBoard[r][c] = 'X'; // This will be handled by gameloop if it's a mine
    }
    else if (mineBoard[r][c] == 0)
    {
        score--;
        displayBoard[r][c] = '0';
    }
    else
    {
        displayBoard[r][c] = '0' + mineBoard[r][c];
    }
}

int checkwin()
{
    int i, j;
    int safecells = SIZE * SIZE - MINES;
    int count = 0;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (revealed[i][j] && mineBoard[i][j] != -1)
            {
                count++;
            }
        }
    }
    return count == safecells;
}

void resetGame()
{
    score = 0;
    boxRow = 0;
    boxCol = 0;
    setupBoards();
    placeMines();
}

void gameloop()
{
    int gameover = 0;

    while (!gameover)
    {
        printBoard();

        int key = getch();
        if (key == 0 || key == 224)
        {
            key = getch();
        }
        if (key == 27) // ESC key
        {
            printf("\nGame exited by user.\n");
            exit(0);
        }
        else if (key == 'r' || key == 'R') // Restart game
        {
            resetGame();
            continue;
        }
        else if (key == 72 && boxRow > 0)
        {
            boxRow--; // Up
        }
        else if (key == 80 && boxRow < SIZE - 1)
        {
            boxRow++; // Down
        }
        else if (key == 75 && boxCol > 0)
        {
            boxCol--; // Left
        }
        else if (key == 77 && boxCol < SIZE - 1)
        {
            boxCol++; // right
        }
        else if (key == 13) // ENTER key
        {
            if (revealed[boxRow][boxCol])
            {
                continue;
            }
            if (mineBoard[boxRow][boxCol] == -1)
            {
                displayBoard[boxRow][boxCol] = 'X';
                for (int i = 0; i < SIZE; i++)
                {
                    for (int j = 0; j < SIZE; j++)
                    {
                        if (mineBoard[i][j] == -1)
                        {
                            displayBoard[i][j] = 'X';
                        }
                    }
                }
                printBoard();
                printf("\n Ohh no! GAME OVER! You hit a mine...");
                printf("\nYour score: %d", score);
                printf("\nPress R to restart or ESC to exit.");
                // Wait for R or ESC
                while (1)
                {
                    int ch = getch();
                    if (ch == 'r' || ch == 'R')
                    {
                        resetGame();
                        gameover = 0;
                        break;
                    }
                    else if (ch == 27)
                    {
                        exit(0);
                    }
                }
                continue;
            }
            else
            {
                reveal(boxRow, boxCol);
                if (checkwin())
                {
                    printBoard();
                    printf("\n GREAT! Congratulations! You cleared the minefield! \n");
                    printf("Your final score: %d\n", score);
                    printf("Press R to restart or ESC to exit.");
                    // Wait for R or ESC
                    while (1)
                    {
                        int ch = getch();
                        if (ch == 'r' || ch == 'R')
                        {
                            resetGame();
                            gameover = 0;
                            break;
                        }
                        else if (ch == 27)
                        {
                            exit(0);
                        }
                    }
                    continue;
                }
            }
        }
    }
}