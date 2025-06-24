#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void printStart(char mapping[][100], int *, int *, int);
void printchange(char map[][100], int);
int movement(char mapping[][100], int *rowp, int *colp, int, int *);
int working();
void gameoverposition(char mapping[][100], int, int);

void displayMenu()
{
    printf("==== MAZE GAME MENU ====\n");
    printf("1. Start Game\n");
    printf("2. Instructions\n");
    printf("3. Exit\n");
    printf("========================\n");
    printf("Enter your choice: ");
}

void showWelcomePage()
{
    system("cls");
    printf("====================================\n");
    printf("         WELCOME TO THE MAZE GAME   \n");
    printf("====================================\n");
    printf("    \"Not all who wander are lost —\n");
    printf("     some are just solving a maze.\"\n");
    printf("\n");
    printf("   Navigate from 'S' to 'E' using:\n");
    printf("      W - Up | A - Left\n");
    printf("      S - Down | D - Right\n");
    printf("\n");
    printf("        Dare to find your path?\n");
    printf("      Press any key to begin...\n");
    printf("====================================\n");
    getch();
    system("cls");
}

void showInstructions()
{
    printf("========== INSTRUCTIONS ==========\n");
    printf("Welcome to the Maze Game!\n\n");
    printf("Use the following keys to navigate:\n");
    printf("  W - Move Up\n");
    printf("  A - Move Left\n");
    printf("  S - Move Down\n");
    printf("  D - Move Right\n\n");
    printf("Objective:\n");
    printf("  Navigate through the maze from 'P' (Start) to 'G' (End).\n");
    printf("  Avoid hitting walls marked with '#'.\n");
    printf("  Use logic and memory to find your way through!\n");
    printf("==================================\n");
    getch();
    system("cls");
}

int main()
{
    showWelcomePage();

    int choice;

    while (1)
    {
        displayMenu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Starting new game...\n");
            Sleep(100);
            system("cls");
            working();
            printf("Press any key to Continue...\n");
            getch();
            Sleep(300);
            system("cls");

            break;
        case 2:
            printf("Instructions:\nUse arrow keys to navigate through the maze.\nAvoid traps and reach the exit!\n");
            Sleep(100);
            system("cls");
            showInstructions();
            break;
        case 3:
            printf("Exiting the game. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}

int working()
{
    char mapping[100][100];
    int rowp, colp, i = 0;

    // FILE *file = fopen("Map.txt", "r");
    // char buf[100];

    // strcpy(mapping[0], "##########");
    // strcpy(mapping[1], "#        #");
    // strcpy(mapping[2], "#  #  #  #");
    // strcpy(mapping[3], "#       G#");
    // strcpy(mapping[4], "##########");

    // while (fgets(buf, sizeof(buf), file) != NULL && i < 50)
    // {
    //     buf[strcspn(buf, "\n")] = '\0';
    //     strcpy(mapping[i], buf);
    //     i++;
    // }

    
    strcpy(mapping[0],  "####################");
    strcpy(mapping[1],  "# #     #       #  #");
    strcpy(mapping[2],  "# # ### # ##### # ##");
    strcpy(mapping[3],  "#     #   #   # #  #");
    strcpy(mapping[4],  "### # ##### # # ####");
    strcpy(mapping[5],  "#   #     # # #    #");
    strcpy(mapping[6],  "# ##### # # # #### #");
    strcpy(mapping[7],  "#     # # # #    # #");
    strcpy(mapping[8],  "##### # # # #### # #");
    strcpy(mapping[9],  "#     #   #      # #");
    strcpy(mapping[10], "####################");





    int rowCount = 11;
    int colcount = strlen(mapping[0]);
    printStart(mapping, &rowp, &colp, rowCount);
    gameoverposition(mapping, colcount, rowCount);
    int movess = 0;
    int x = movement(mapping, &rowp, &colp, rowCount, &movess);

    if (x == 1)
    {
        Sleep(100);
        system("cls");
        printchange(mapping, rowCount);
        printf("\nThe Game is over\n");
        printf("Total Moves: %d\n", movess);
        printf("Score: %d\n", movess * 10);
    }

    return 0;
}

void gameoverposition(char mapping[][100], int colcount, int rowcounnt)
{
    int xdir = 0, ydir = 0;
    srand(time(NULL));
    while (1)
    {
        ydir = rand() % rowcounnt;
        xdir = rand() % colcount;
        printf("%d %d \n", xdir, ydir);

        if (xdir < rowcounnt && ydir < colcount && xdir > 0 && ydir > 0)
        {
            if (mapping[ydir][xdir] == ' ')
            {
                mapping[ydir][xdir] = 'G';
                break;
            }
        }
    }
}

int movement(char mapping[][100], int *rowp, int *colp, int row, int *movement)
{

    while (1)
    {
        // Sleep(100);
        system("cls");
        printchange(mapping, row);
        char move;
        fflush(stdin);
        move = getch();

        switch (move)
        {
        case 'd':
        case 'D':
            if (mapping[*rowp][*colp + 1] == ' ')
            {
                mapping[*rowp][*colp + 1] = 'P';
                mapping[*rowp][*colp] = ' ';
                *colp = *colp + 1;
                *movement = *movement + 1;
            }
            else if (mapping[*rowp][*colp + 1] == 'G')
            {
                mapping[*rowp][*colp + 1] = 'P';
                mapping[*rowp][*colp] = ' ';
                *colp = *colp + 1;
                *movement = *movement + 1;
                return 1;
            }
            break;
        case 'a':
        case 'A':
            if (mapping[*rowp][*colp - 1] == ' ')
            {
                mapping[*rowp][*colp - 1] = 'P';
                mapping[*rowp][*colp] = ' ';
                *colp = *colp - 1;
                *movement = *movement + 1;
            }
            else if (mapping[*rowp][*colp - 1] == 'G')
            {

                mapping[*rowp][*colp - 1] = 'P';
                mapping[*rowp][*colp] = ' ';
                *colp = *colp - 1;
                *movement = *movement + 1;
                return 1;
            }
            break;
        case 's':
        case 'S':
            if (mapping[*rowp + 1][*colp] == ' ')
            {
                mapping[*rowp + 1][*colp] = 'P';
                mapping[*rowp][*colp] = ' ';
                *rowp = *rowp + 1;
                *movement = *movement + 1;
            }
            else if (mapping[*rowp + 1][*colp] == 'G')
            {
                mapping[*rowp + 1][*colp] = 'P';
                mapping[*rowp][*colp] = ' ';
                *rowp = *rowp + 1;
                *movement = *movement + 1;

                return 1;
            }
            break;
        case 'w':
        case 'W':
            if (mapping[*rowp - 1][*colp] == ' ')
            {
                mapping[*rowp - 1][*colp] = 'P';
                mapping[*rowp][*colp] = ' ';
                *rowp = *rowp - 1;
                *movement = *movement + 1;
            }
            else if (mapping[*rowp - 1][*colp] == 'G')
            {
                mapping[*rowp - 1][*colp] = 'P';
                mapping[*rowp][*colp] = ' ';
                *rowp = *rowp - 1;
                *movement = *movement + 1;

                return 1;
            }

            break;
        default:
            break;
        }
    }
}

void printStart(char mapping[][100], int *rowp, int *colp, int row)
{

    int i, j, found = 0, lenRow = strlen(mapping[0]);

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < lenRow; j++)
        {
            if (mapping[i][j] == ' ')
            {
                mapping[i][j] = 'P';
                *rowp = i;
                *colp = j;
                found = 1;
                break;
            }
        }
        if (found == 1)
        {
            break;
        }
    }
    system("cls");
    for (int i = 0; i < lenRow; i++)
    {
        printf("%s\n", mapping[i]);
    }
}

void printchange(char map[][100], int row)
{
    system("cls");
    for (int i = 0; i < row; i++)
    {
        printf("%s\n", map[i]);
    }
}