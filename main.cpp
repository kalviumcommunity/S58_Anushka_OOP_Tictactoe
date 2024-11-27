#include <iostream>
#include <string>
using namespace std;

// Base class for games, providing common functionalities for all games
// Adheres to SRP by focusing only on responsibilities common to all games
// Supports LSP by ensuring derived classes can substitute the base class without altering behavior
class Game {
protected:
    static int gameCount;  // Static variable to track the total number of games created

public:
    // Constructor increments the game count whenever a new game instance is created
    Game() {
        gameCount++;
    }

    virtual ~Game() {}  // Virtual destructor to ensure proper cleanup of derived classes

    // Pure virtual function for resetting the game board
    // Enforces LSP by defining a contract that all derived classes must implement
    virtual void resetBoard() = 0;

    // Virtual function to display the game board
    // Adheres to LSP by allowing meaningful overrides in derived classes
    virtual void displayBoard() const = 0;

    // Static function to get the total number of games created
    static int getGameCount() {
        return gameCount;
    }
};

// Initializing the static variable for tracking game count
int Game::gameCount = 0;

// Derived class for Tic-Tac-Toe game, inheriting from Game (Single Inheritance)
// Adheres to SRP by handling all responsibilities specific to Tic-Tac-Toe
// Supports LSP by ensuring substitutability without altering base class behavior
class TicTacToe : public Game {
protected:
    char board[3][3];  // 2D array to represent the Tic-Tac-Toe board
    int turn;          // Variable to track the current player's turn (1 or 2)
    static int totalMoves;  // Static variable to track total moves across all Tic-Tac-Toe games

public:
    // Constructor initializes the board and sets the first turn
    TicTacToe() {
        this->resetBoard();  // Reset the board to its initial state
        this->turn = 1;      // Player 1 starts first
        cout << "TicTacToe game initialized.\n";
    }

    // Destructor announces when the game ends
    ~TicTacToe() {
        cout << "TicTacToe game ended.\n";
    }

    // Override the pure virtual function from Game to reset the board
    void resetBoard() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->board[i][j] = '-';  // Set all positions on the board to '-'
            }
        }
    }

    // Override the virtual function to display the current state of the board
    void displayBoard() const override {
        cout << "\n";
        cout << this->board[0][0] << " | " << this->board[0][1] << " | " << this->board[0][2] << endl;
        cout << "---------\n";
        cout << this->board[1][0] << " | " << this->board[1][1] << " | " << this->board[1][2] << endl;
        cout << "---------\n";
        cout << this->board[2][0] << " | " << this->board[2][1] << " | " << this->board[2][2] << endl;
    }

    // Function to check if a player has won
    bool checkWin() {
        // Check all possible winning conditions
        return (checkRow() || checkCol() || checkDiag1() || checkDiag2());
    }

    // Make a move with row and column as integers
    void makeMove(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || isOccupied(row, col)) {
            cout << "Invalid move.\n";
            return;
        }

        this->board[row][col] = (this->turn == 1) ? 'X' : 'O';
        this->turn = 3 - this->turn;  // Toggle turn between 1 and 2
        totalMoves++;
    }

    // Static function to get the total moves made across all TicTacToe games
    static int getTotalMoves() {
        return totalMoves;
    }

private:
    // Check if a specific cell is occupied
    bool isOccupied(int row, int col) {
        return (this->board[row][col] != '-');
    }

    // Check if there is a winning condition in any row
    bool checkRow() {
        for (int i = 0; i < 3; i++) {
            if (this->board[i][0] != '-' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) {
                return true;
            }
        }
        return false;
    }

    // Check if there is a winning condition in any column
    bool checkCol() {
        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] != '-' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]) {
                return true;
            }
        }
        return false;
    }

    // Check if there is a winning condition in the main diagonal
    bool checkDiag1() {
        return (this->board[0][0] != '-' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]);
    }

    // Check if there is a winning condition in the anti-diagonal
    bool checkDiag2() {
        return (this->board[0][2] != '-' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]);
    }
};

// Initializing the static variable for tracking total moves
int TicTacToe::totalMoves = 0;

int main() {
    Game* game = new TicTacToe();  // Substituting the base class with a derived class
    game->displayBoard();         // Display the board using the base class pointer

    delete game;  // Free the dynamically allocated memory
    return 0;
}
