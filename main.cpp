#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to draw the Tic-Tac-Toe board
void drawBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "-------------" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "| ";
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
        std::cout << "-------------" << std::endl;
    }
}

// Function to check if a player has won
bool checkWin(const std::vector<std::vector<char>>& board, char player) {
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
bool checkFull(const std::vector<std::vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function for the CPU to make a random move
void makeCPUMove(std::vector<std::vector<char>>& board) {
    std::vector<int> availableMoves;

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
    std::vector<std::vector<char>> board(3, std::vector<char>(3, ' '));
    char currentPlayer = 'X';

    while (true) {
        // Draw the board
        drawBoard(board);

        // Player's move
        if (currentPlayer == 'X') {
            int row, col;
            std::cout << "Player " << currentPlayer << ", enter your move (row [1-3] and column [1-3]): ";
            std::cin >> row >> col;
            --row; // Adjust for zero-based indexing
            --col;

            // Check if the move is valid
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
                std::cout << "Invalid move. Try again." << std::endl;
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
            std::cout << "Player " << currentPlayer << " wins!" << std::endl;
            break;
        }

        // Check if the board is full
        if (checkFull(board)) {
            // Draw the final board
            drawBoard(board);
            std::cout << "It's a tie!" << std::endl;
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