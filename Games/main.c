#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include"CardMatching.c"
#include"mazegame.c"
#include"Snackgame.c"
#include"TicTakToe.c"
#include"RockPaperSessior.c"
#include"MiningGame.c"

void welcomeScreen()
{
    system("cls");

    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*     WELCOME TO THE ULTIMATE GAME ZONE!        *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*   Get ready for a thrilling gaming experience *\n");
    printf("*         Packed with challenges & fun!         *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("\n             Developed by Team ELITE\n");
    getch();
}

void gameMenu()
{
    int choice;
    system("cls");

    printf("=================================================\n");
    printf("           SELECT A GAME TO START\n");
    printf("=================================================\n");
    printf("  [1] Snake Game\n");
    printf("  [2] Maze Runner\n");
    printf("  [3] Tic Tac Toe\n");
    printf("  [4] Card Matching\n");
    printf("  [5] Rock Paper Sessior\n");
    printf("  [6] Mininig Game\n");
    printf("  [0] Exit\n");     
    printf("-------------------------------------------------\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Launching Snake Game...\n");
        welcomesnack();
        break;
    case 2:
        printf("Starting Maze Runner...\n");
        welcomemaze();
        break;
    case 3:
        printf("Loading Tic Tac Toe...\n");
        welcometictactoe();
        break;
    case 4:
        printf("Opening Card Matching Challenge...\n");
        welcomecard();
        break;
    case 5:
        printf("Opening Rock Paper Secciors Challenge...\n");
        welcomerockpapersessior();
        break;
    case 6:
        printf("Opening Mining Game Challenge...\n");
        MiningGame();
        break;
    case 0:
        printf("Thanks for playing! See you again.\n");
       exit(0);
    default:
        printf("Invalid selection. Please restart the program.\n");
    }
}

int main()
{
    welcomeScreen();
    gameMenu();
    return 0;
}