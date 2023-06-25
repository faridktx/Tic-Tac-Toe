#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to draw the Tic-Tac-Toe board
void drawBoard(const vector<vector<char>>& board) {
    cout << "-------------" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << "| ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << " | ";
        }
        cout << endl;
        cout << "-------------" << endl;
    }
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

// Function to check if the board is full
bool checkFull(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function for the CPU to make a random move
void makeCPUMove(vector<vector<char>>& board) {
    vector<int> availableMoves;

    // Find all available moves
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                availableMoves.push_back(i * 3 + j);
        }
    }

    // Choose a random available move
    int randomIndex = rand() % availableMoves.size();
    int row = availableMoves[randomIndex] / 3;
    int col = availableMoves[randomIndex] % 3;

    // Make the move
    board[row][col] = 'O';
}

// Function to play the game against the CPU
void playGame() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';

    while (true) {
        // Draw the board
        drawBoard(board);

        // Player's move
        if (currentPlayer == 'X') {
            int row, col;
            cout << "Player " << currentPlayer << ", enter your move (row [1-3] and column [1-3]): ";
            cin >> row >> col;
            --row; // Adjust for zero-based indexing
            --col;

            // Check if the move is valid
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            // Make the move
            board[row][col] = currentPlayer;
        }
        // CPU's move
        else {
            makeCPUMove(board);
        }

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            // Draw the final board
            drawBoard(board);
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }

        // Check if the board is full
        if (checkFull(board)) {
            // Draw the final board
            drawBoard(board);
            cout << "It's a tie!" << endl;
            break;
        }

        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    playGame();

    return 0;
}
