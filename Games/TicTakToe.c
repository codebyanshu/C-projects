#include <stdio.h>
char board[3][3];
void createBoard()
{
    char num = '1';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = num++;
        }
    }
}
void showBoard()
{
    for (int i = 0; i < 3; i++)
    {
        printf("%c|%c|%c\n", board[i][0], board[i][1], board[i][2]);
    }
}
int winner()
{
    for (int i = 0; i < 3; i++)
    {
        // for row
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 1;
        // for column
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 1;
    }
    // for diagonal(left to right)
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 1;
    // for diagonaly (right to left)
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 1;

    return 0;
}

int welcometictactoe()
{
    int move, row, col;
    char player = 'x';
    createBoard();

    for (int i = 0; i < 9; i++)
    {
        showBoard();
        printf("player %c, enter (1-9):-", player);
        scanf("%d", &move);
        if (move < 1 || move > 9)
        {
            printf("Invalid move. Try again.\n");
            i--;
            continue;
        }

        row = (move - 1) / 3;
        col = (move - 1) % 3;

        if (board[row][col] == 'x' || board[row][col] == 'o')
        {
            printf("Already taken,Invalid\n");
            i--;
            continue;
        }
        board[row][col] = player;
        if (winner())
        {
            showBoard();
            printf("Player %c wins!\n", player);
            return 0;
        }

        player = (player == 'x') ? 'o' : 'x';
    }
    showBoard();
    printf("match Draw");
    return 0;
}