#include <stdio.h>
#define SIZE 3
int i, j;
void initializeBoard(char board[SIZE][SIZE])
{
	//Board intialization
    for (i = 0; i < SIZE; ++i)
	{
        for (j = 0; j < SIZE; ++j) 
            board[i][j] = ' ';
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    printf("   0 1 2\n");
    printf("  -------\n");
    for (i = 0; i < SIZE; ++i) 
	{
        printf("%d| ", i);
        for (j = 0; j < SIZE; ++j)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

char checkWin(char board[SIZE][SIZE]) {
    char winner = ' ';

    // Check rows and columns
    for (i = 0; i < SIZE; ++i) 
	{
        if ((board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])) 
		{
            winner = board[0][i];
            break;
        }
    }
    // Check diagonals
    if (board[1][1] != ' ' &&
        ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
         (board[0][2] == board[1][1] && board[1][1] == board[2][0]))) 
	{
        winner = board[1][1];
    }
    return winner;
}

int main() {
    char board[SIZE][SIZE];
    char currentPlayer = 'X';
    int row, col;
    char winner = ' ';
    int pieceCount=0;
    initializeBoard(board);

    printf("Welcome to Buddhi-Chal!\n");

    // Each player places their three pieces one by one
    while (pieceCount<6) 
	{
        printBoard(board);
        printf("Player %c's turn. Enter row and column to place your piece (e.g., 0 0): ", currentPlayer);
        scanf("%d %d", &row, &col);
		
		//Checks if the entered space is in the board and empty or not
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') 
		{
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = currentPlayer;
        pieceCount++;
        
		winner = checkWin(board);

        // Switch to the other player after each piece placement
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    // Main game loop for moving pieces
    while (winner == ' ' && currentPlayer != ' ') 
	{
        printBoard(board);
        printf("Player %c's turn. Enter current row and column of your piece (e.g., 0 0): ", currentPlayer);
        scanf("%d %d", &row, &col);

        //Check if the entered space is in the board and contains current player's piece or not
		if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != currentPlayer)
		{
            printf("Invalid move. Try again.\n");
            continue;
        }

        printf("Enter new row and column to move your piece (e.g., 0 1): ");
        int newRow, newCol;
        scanf("%d %d", &newRow, &newCol);

        //Checks if the new row and column is ajacent to the present row and column and also empty or not
		if (newRow < 0 || newRow >= SIZE || newCol < 0 || newCol >= SIZE ||
            (newRow != row - 1 && newRow != row + 1 && newRow != row) ||
            (newCol != col - 1 && newCol != col + 1 && newCol != col) ||
            board[newRow][newCol] != ' ') 
		{
            printf("Invalid move. Try again.\n");
            continue;
        }
		
		//Empties the previous space and moves the selected piece tot he new space
        board[row][col] = ' ';
        board[newRow][newCol] = currentPlayer;

        winner = checkWin(board);
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    printBoard(board);
	
	//Print winner
    if (winner == 'X' || winner == 'O')
        printf("Player %c wins!\n", winner);

    return 0;
}
