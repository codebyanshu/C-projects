#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define width 45
#define height 15

// Globel variable
int snakeX, snakeY;
int fruitX, fruitY;
int score;
char direction;
int gameOver;
int tailX[100], tailY[100];
int nTail = 0;

void menu();
void start();
void border();
void input();
void logic();

void setup()
{
    snakeX = width / 2;
    snakeY = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    score = 0;
    direction = 'R';
    gameOver = 0;
}

void border()
{
    system("cls");
    printf("\t~ Welcome!!, To The Snake-Game ~\n\n");
    int i, j;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // top or bottam border
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("#");
            }
            else if (i == snakeY && j == snakeX)
                printf("O"); // snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // fruite

            // inside the area

            else
            {
                int k;
                int printed = 0;
                for (k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o"); // tail body
                        printed = 1;
                        break;
                    }
                }
                if (!printed)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf(" Score :- %d\n", score);
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 72:
            direction = 'U';
            break;
        case 80:
            direction = 'D';
            break;
        case 75:
            direction = 'L';
            break;
        case 77:
            direction = 'R';
            break;
        }
    }
}

void logic()
{
    // Move tail positions
    int i;
    for (i = nTail - 1; i > 0; i--)
    {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = snakeX;
    tailY[0] = snakeY;

    // Move head
    switch (direction)
    {
    case 'U':
        snakeY--;
        break;
    case 'D':
        snakeY++;
        break;
    case 'L':
        snakeX--;
        break;
    case 'R':
        snakeX++;
        break;
    }

    // Check for fruit collision
    if (snakeX == fruitX && snakeY == fruitY)
    {
        score += 10;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        nTail++;
    }

    // Game over if snake hits wall
    if (snakeX <= 0 || snakeX >= width - 1 || snakeY <= 0 || snakeY >= height - 1)
        gameOver = 1;
}

// Function 1: Main Menu
void menu()
{

    system("cls"); // Clears screen (Windows only)
    int choice;
    printf("\t\t\t~ Welcome!!, To The Snake-Game ~\n\n");
    printf("~ Options :-\n\n");
    printf("1. Start\n");
    printf("2. help?\n");
    printf("3. Exit\n");
    printf("\n~ Please select an option: \t");
    scanf("%d", &choice);
    getchar();     // clear input buffer
    system("cls"); // Clears screen (Windows only)

    switch (choice)
    {
    case 1:
        printf("\t\t\t~ Welcome!!, To The Snake-Game ~\n\n");
        break;
    case 2:
        printf("KEYS TO PLAY THE GAME :-\n");
        printf("\n1. 'W' key is used to move snake in UPPER direction.\n");
        printf("2. 'S' key is used to move snake in DOWN direction. \n");
        printf("3. 'D' key is used to move snake in LEFT direction. \n");
        printf("4. 'A key is used to move snake in RIGHT direction. \n");
        printf("\nNOW! PREES THE ENTER KEY TO SEE THE OPTIONS :-\n");
        getchar();     // clear input buffer
        system("cls"); // Clears screen (Windows only)
        menu();

    case 3:
        printf("Exiting the system. Goodbye!\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        menu();
        break;
    }
}

int welcomesnack()
{
    srand(time(NULL));
    setup();
    menu();

    while (!gameOver)
    {
        border();
        input();
        logic();
        Sleep(200); // Slow down the loop
    }

    printf("Game Over! Final Score: %d\n", score);
    printf("\n PREES THE ENTER KEY CONTINUE :-\n");
    getchar(); // clear input buffer
    welcomesnack();
    return 0;
}
