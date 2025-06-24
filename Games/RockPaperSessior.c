#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int genrateRandomNumber(int n)
{
    srand(time(NULL));
    return rand() % n;
}
int greater(char char1, char char2)
{
    if (char1 == char2)
    {
        return -1;
    }

    if ((char1 == 'r') && (char2 == 's'))
    {
        return 1;
    }
    else if ((char2 == 'r') && (char1 == 's'))
    {
        return 0;
    }
    if ((char1 == 'r') && (char2 == 'p'))
    {
        return 1;
    }
    else if ((char2 == 'r') && (char1 == 'p'))
    {
        return 0;
    }
    if ((char1 == 's') && (char2 == 'r'))
    {
        return 1;
    }
    else if ((char1 == 's') && (char2 == 'r'))
    {
        return 0;
    }
}

int welcomerockpapersessior()
{
    int playerscore = 0, compscore = 0, temp;
    char playerchar, compchar;
    char dict[] = {'r', 'p', 's'};
    printf("Welcome to the game Rock,Paper and seissors \n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("player 1 's turn \n\n");
        printf("Choose 1 for rock and 2 for paper and 3 for seissors \n");
        scanf("%d", &temp);
        getchar();
        playerchar = dict[temp - 1];
        printf("You choose %c\n\n", playerchar);

        printf("Computer 's turn \n");
        temp = genrateRandomNumber(3) + 1;
        compchar = dict[temp - 1];
        printf("Computer choose %c\n", compchar);
        if (greater(compchar, playerchar) == 1)
        {
            compscore += 1;
            printf("computer win \n");
        }
        else if (greater(compchar, playerchar) == -1)
        {
            compscore += 1;
            playerscore += 1;
        }
        else
        {
            printf("you win \n");
            playerscore += 1;
        }
        printf("Score :\t you : %d computer : %d \n", playerscore, compscore);
    }
    if (playerscore > compscore)
    {
        printf("You won the Game \n");
    }
    else
    {
        printf("Computer won the game \n");
    }

    printf("The Random number genrated between 0 to 5 is : %d\n", genrateRandomNumber(2));

    return 0;
}
