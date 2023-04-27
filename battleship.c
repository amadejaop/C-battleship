#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SPACES 7
#define NUMSHIP 10
#define GRIDS 3
#define TURNS 49

void printBoard (char arr[][SPACES]);
void createBoard (char arr[][SPACES]);
void placeShips(char arr[][SPACES]);
void randomizeShips(char arr[][SPACES]);
void playerGuess (char visible[][SPACES], char hidden[][SPACES]);
void PCGuess(char arr[][SPACES]);
bool winner(char arr[][SPACES]);
int shipsRemaining(char arr[][SPACES]);

int main(void)
{
    // print game instructions?

    // create playing boards
    char userBoard[SPACES][SPACES], PCBoardVisible[SPACES][SPACES], PCBoardHidden[SPACES][SPACES];

    createBoard(userBoard);
    createBoard(PCBoardVisible);
    createBoard(PCBoardHidden);
    printBoard(userBoard);

    // place ships on the board
    placeShips(userBoard);
    srand(time(NULL));
    randomizeShips(PCBoardHidden);

    // START THE GAME
    for (int i = 0; i < TURNS; i++)
    {
        printf("It's your turn.\n");

        playerGuess(PCBoardVisible, PCBoardHidden);
        printf("Computer has %i ships remaining!\n\n", shipsRemaining(PCBoardHidden));

        if (winner(PCBoardHidden))
        {
            printf("Congratulations, you won the game!\n");
            return 0;
        }

        printf("Computer attacked!\n");
        PCGuess(userBoard);
        printf("You have %i ships remaining!\n\n", shipsRemaining(userBoard));

        if (winner(userBoard))
        {
            printf("Computer won this time!\n");
            return 0;
        }
    }
}

void createBoard (char arr[][SPACES])
{
    for (int i = 0; i < SPACES; i++)
    {
        for (int j = 0; j < SPACES; j++)
        {
            arr[i][j] = '_';
        }
    }
}

void printBoard (char arr[][SPACES])
{
    printf("  A B C D E F G\n");
    for (int i = 0; i < SPACES; i++)
    {
        printf("%i ", i + 1);
        for (int j = 0; j < SPACES; j++)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}
void randomizeShips(char arr[][SPACES])
{
    int x, y;

    for (int i = 0; i < NUMSHIP; i++)
    {
        do
        {
            x = rand() % 7;
            y = rand() % 7;
        }
        while (arr[x][y] != '_');
        arr[x][y] = 'O';
    }
}

void placeShips(char arr[][SPACES])
{
    char c;
    int x, y;

    for (int i = 0; i < NUMSHIP; i++)
    {
        do
        {
            do
            {
                printf("Choose a letter: ");
                scanf(" %c", &c);
            }
            while (toupper(c) > 71 || toupper(c) < 65);
            y = (int)toupper(c) - 65;

            do
            {
                printf("Choose a number: ");
                scanf(" %i", &x);
            }
            while (x > 7 || x < 1);
            x--;
        }
        while (arr[x][y] != '_');

        arr[x][y] = 'O';

        printBoard(arr);
        printf("Ships left to place: %i / 10.\n\n", 9 - i);
    }
}

void playerGuess (char visible[][SPACES], char hidden[][SPACES])
{
    char c;
    int x, y;

    printf("Pick coordinates to attack.\n");

    do
    {
        do
        {
            printf("Choose a letter: ");
            scanf(" %c", &c);
        }
        while (toupper(c) > 71 || toupper(c) < 65);
        y = (int)toupper(c) - 65;

        do
        {
            printf("Choose a number: ");
            scanf(" %i", &x);
        }
        while (x > 7 || x < 1);
        x--;
    }
    while(visible[x][y] != '_');

    if (hidden[x][y] == 'O')
    {
        visible[x][y] = 'X';
        hidden[x][y] = 'X';
        printBoard(visible);
        printf("You've hit a ship!\n");
    }
    else
    {
        visible[x][y] = '~';
        printBoard(visible);
        printf("Oh no! You've missed!\n");
    }
}

void PCGuess(char arr[][SPACES])
{
    int x, y;

    do
    {
        x = rand() % 7;
        y = rand() % 7;
    }
    while(arr[x][y] == 'X');

    if (arr[x][y] == 'O')
    {
        printf("Computer hit your ship!\n");
    }
    else
    {
        printf("Computer missed your ship!\n");
    }

    arr[x][y] = 'X';
    printBoard(arr);
}

bool winner(char arr[][SPACES])
{
    bool winner = true;

    for (int i = 0; i < SPACES; i++)
    {
        for (int j = 0; j < SPACES; j++)
        {
            if (arr[i][j] == 'O')
            {
                winner = false;
            }
        }
    }

    return winner;
}

int shipsRemaining(char arr[][SPACES])
{
    int counter = 0;

    for (int i = 0; i < SPACES; i++)
    {
        for (int j = 0; j < SPACES; j++)
        {
            if (arr[i][j] == 'O')
            {
                counter++;
            }
        }
    }

    return counter;
}
