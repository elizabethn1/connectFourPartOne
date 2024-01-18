/**************************************************************************
 * This program replicates Connect 4.
 * Two players take turns placing their piece into the board until
 * one of them is able to get their pieces to be four in a row
 * (horiztonally, vertically, or diagonally), a player quits the game,
 * or the board is full and no one wins.
 * Class: CS 141, Fall 2023
 * System: Zybooks Lab
 * @author Elizabeth Ng
 * @version November 16, 2023
 **************************************************************************/
#include <iostream>

using namespace std;

/*
 * Description: Displays the Connect 4 board.
 * Input: myBoard (a 2D char array, which is the board)
 * Output: This function is of type void, so it doesn't return anything. However, it prints the 2D array, which is the board.
 */
void displayBoard(char myBoard[6][7]) {
    cout << "    0 1 2 3 4 5 6" << endl;

    for (int m = 0; m < 6; ++m) {
        cout << "    ";
        for (int n = 0; n < 7; ++n) {
            cout << myBoard[m][n] << " ";
        }
        cout << endl;
    }
}

/*
 * Description: Updates the board to reflect a player's move.
 * Input: myBoard (a 2D char array, which is the board), columnChoice (the column that a player chose for their move), currentPlayer (the player that is making a move)
 * Output: This function is of type void, so it doesn't return anything. However, this function updates the board to reflect a particular move that a player makes.
 */
void makeMove(char myBoard[6][7], int columnChoice, char currentPlayer) {
    for (int row = 5; row >= 0; --row) { // Starts checking from the bottom of the column
        if (myBoard[row][columnChoice] == '-') {
            myBoard[row][columnChoice] = currentPlayer;
            break; // Exit out of the loop once the player's move has been made
        }
    }
}

/*
 * Description: Checks if the board's column is full.
 * Input: myBoard (a 2D char array, which is the board), columnChoice (the column to check)
 * Output: isFull (If the column is full, return true. If not, return false)
 */
bool columnFull(char myBoard[6][7], int columnChoice) {
    bool isFull = false;
    int counter = 0;

    for (int row = 5; row >= 0; --row) {
        if (myBoard[row][columnChoice] != '-') {
            counter += 1; // Increments the counter by 1 because myBoard[row][columnChoice] contains an 'X' or 'O'
        }
    }

    if (counter == 6) {
        isFull = true; // Change the value of isFull from false to true because the column is full
    }

    return isFull;
}

/*
 * Description: Checks for a win that is diagonal and pointing downwards
 * Inputs: myBoard (a 2D char array, which is the board), currentPlayer (the player that just made a move)
 * Output: foundWin (If the current player achieves a diagonal four in a row, return true. If not, return false)
 */
bool diagonalDownCheck (char myBoard[6][7], char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == myBoard[row][col]) {
                if (myBoard[row][col] == myBoard[row + 1][col + 1]) {
                    if (myBoard[row + 1][col + 1] == myBoard[row + 2][col + 2]) {
                        if (myBoard[row + 2][col + 2] == myBoard[row + 3][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that is diagonal and pointing upwards
 * Inputs: myBoard (a 2D char array, which is the board), currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a diagonal four in a row, return true. If not, return false)
 */
bool diagonalUpCheck (char myBoard[6][7], char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 3; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == myBoard[row][col]) {
                if (myBoard[row][col] == myBoard[row - 1][col + 1]) {
                    if (myBoard[row - 1][col + 1] == myBoard[row - 2][col + 2]) {
                        if (myBoard[row - 2][col + 2] == myBoard[row - 3][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that's in a horizontal row
 * Inputs: myBoard (a 2D char array, which is the board), currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a horizontal four in a row, return true. If not, return false)
 */
bool horizontalCheck (char myBoard[6][7], char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (currentPlayer == myBoard[row][col]) {
                if (myBoard[row][col] == myBoard[row][col + 1]) {
                    if (myBoard[row][col + 1] == myBoard[row][col + 2]) {
                        if (myBoard[row][col + 2] == myBoard[row][col + 3]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks for a win that's in a vertical row
 * Inputs: myBoard (a 2D char array, which is the board), currentPlayer (the player that just made a move)
 * Output: foundWin (If the player achieves a vertical four in a row, return true. If not, return false)
 */
bool verticalCheck(char myBoard[6][7], char currentPlayer) {
    bool foundWin = false;
    bool canBreak = false; // This variable helps with breaking out of the outer loop once a four in a row has been found

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 7; ++col) {
            if (currentPlayer == myBoard[row][col]) {
                if (myBoard[row][col] == myBoard[row + 1][col]) {
                    if (myBoard[row + 1][col] == myBoard[row + 2][col]) {
                        if (myBoard[row + 2][col] == myBoard[row + 3][col]) {
                            foundWin = true;
                            canBreak = true;
                            break; // There is a four in a row, so break out of the inner loop
                        }
                    }
                }
            }
        }

        if (canBreak) { // Break out of the outer loop
            break;
        }
    }

    return foundWin;
}

/*
 * Description: Checks if the board is full
 * Inputs: myBoard (a 2D char array, which is the board)
 * Output: fullBoard (Returns true if the board is full. Returns false if the board isn't full.)
 */
bool boardFull(char myBoard[6][7]) {
    bool fullBoard = false;
    int counter = 0;

    // Only checks row 0 because if row 0 is full, the entire board must be full
    for (int a = 0; a < 7; ++a) {
        if (myBoard[0][a] != '-') {
            counter += 1;
        }
    }

    if (counter == 7) {
        fullBoard = true;
    }

    return fullBoard;
}

int main()
{
    // Directions for the game
    cout << "This is the Game Connect 4." << endl;
    cout << "Each player should place an X or an O in the space" << endl;
    cout << "by entering the column you want to place the piece." << endl;
    cout << "The piece will fall until it reaches the bottom or" << endl;
    cout << "the current pieces in the board. When X or O gets 4 in" << endl;
    cout << "a row (either horizontally, vertically, or diagonally," << endl;
    cout << "then that person wins. The user can enter Q (or q) to" << endl;
    cout << "end the game early." << endl;
    cout << "Let's get started!!!" << endl;

    char board[6][7];

    // Initialize board
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 7; ++j) {
            board[i][j] = '-';
        }
    }

    displayBoard(board); // Display the board, which is currently empty

    int playerCounter = 0; // Initialized to 0 so that player X will make the first move
    char playerInput;
    char player;

    do {
        // Allows the players to take turns while they play the game. If playerCounter is an even integer, X plays. If playerCounter is an odd integer, O plays.
        if ((playerCounter % 2) == 0) {
            player = 'X';
            cout << "It is X's turn." << endl;
        } else if ((playerCounter % 2) == 1) {
            player = 'O';
            cout << "It is O's turn." << endl;
        }

        cout << "Enter a column to place your piece. ";
        cin >> playerInput;

        if ((playerInput == 'Q') || (playerInput == 'q')) { // The game will quit if the player entered 'Q' or 'q' earlier
            cout << "Ending Game" << endl;
            break;
        }
        else if ((int(playerInput) >= 48) && (int(playerInput) <= 54)) { // If this is true, this means that the user's input is a valid column.
            int columnSelection = int(playerInput - '0'); // Stores the column as an int

            if (columnFull(board, columnSelection) == false) { // If the column is not full, the player can make their move. If it's full, they have to enter another input.
                makeMove(board, columnSelection, player); // Player makes a move
                displayBoard(board); // Display board

                // Checks for a win. Four different checks are made on the board.
                if (player == 'X') {
                    if (diagonalDownCheck(board, 'X') || diagonalUpCheck(board, 'X') || horizontalCheck(board, 'X') || verticalCheck(board, 'X')) {
                        cout << "Game is Over, Player X got 4 in a row!!!!" << endl;
                        break;
                    }
                }
                else if (player == 'O') {
                    if (diagonalDownCheck(board, 'O') || diagonalUpCheck(board, 'O') || horizontalCheck(board, 'O') || verticalCheck(board, 'O')) {
                        cout << "Game is Over, Player O got 4 in a row!!!!" << endl;
                        break;
                    }
                }

                playerCounter += 1; // Increment playerCounter by 1 at the end of the turn so that it can be the next player's turn.
            }
            else {
                cout << "column chosen is already full" << endl;
            }
        }
        else {
            cout << "Please enter a valid column" << endl;
        }
    } while (boardFull(board) != true); // The players will be prompted to play the game as long as the board isn't full and no one has won

    if (boardFull(board)) { // Checks if the board is full
        cout << "Board is Full, It's a Draw!!!" << endl;
    }

    return 0;
}

