#include <iostream>
#include <string>
using namespace std;

// Base class for games, providing common functionalities for all games
// Adheres to SRP by focusing only on responsibilities common to all games
// Supports OCP by allowing new game types to extend this class without modifying it
class Game {
protected:
    static int gameCount;  // Static variable to track the total number of games created

public:
    // Constructor increments the game count whenever a new game instance is created
    Game() {
        gameCount++;
    }

    // Pure virtual function for resetting the game board
    // Enforces OCP by defining a contract that derived classes must implement
    virtual void resetBoard() = 0;

    // Static function to get the total number of games created
    // Demonstrates SRP by handling the specific responsibility of tracking game instances
    static int getGameCount() {
        return gameCount;
    }
};

// Initializing the static variable for tracking game count
int Game::gameCount = 0;

// Derived class for Tic-Tac-Toe game, inheriting from Game (Single Inheritance)
// Adheres to SRP by handling all responsibilities specific to Tic-Tac-Toe
class TicTacToe : public Game {
protected:
    char board[3][3];  // 2D array to represent the Tic-Tac-Toe board
    int turn;          // Variable to track the current player's turn (1 or 2)
    static int totalMoves;  // Static variable to track total moves across all Tic-Tac-Toe games

public:
    // Constructor initializes the board and sets the first turn
    // Utilizes OCP by extending the Game class and implementing game-specific logic
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
    // Demonstrates OCP by customizing the behavior for Tic-Tac-Toe
    void resetBoard() override {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->board[i][j] = '-';  // Set all positions on the board to '-'
            }
        }
    }

    // Function to display the current state of the board
    // Part of SRP, focusing on displaying the board for Tic-Tac-Toe
    void displayBoard() {
        cout << "\n";
        cout << this->board[0][0] << " | " << this->board[0][1] << " | " << this->board[0][2] << endl;
        cout << "---------\n";
        cout << this->board[1][0] << " | " << this->board[1][1] << " | " << this->board[1][2] << endl;
        cout << "---------\n";
        cout << this->board[2][0] << " | " << this->board[2][1] << " | " << this->board[2][2] << endl;
    }

    // Function to check if a player has won
    // Encapsulates win-checking logic, adhering to SRP by focusing on game-specific rules
    bool checkWin() {
        // Check all possible winning conditions
        return (checkRow() || checkCol() || checkDiag1() || checkDiag2());
    }

    // Function Overloading: makeMove with row and column as integers
    // Demonstrates SRP by encapsulating move logic specific to Tic-Tac-Toe
    void makeMove(int row, int col) {
        // Assign 'X' or 'O' based on the current turn
        if (this->turn == 1) {
            this->board[row][col] = 'X';
        } else {
            this->board[row][col] = 'O';
        }
        this->turn = (this->turn + 1) % 2;  // Switch turns between players
        totalMoves++;  // Increment the total moves made across all games
    }

    // Function Overloading: makeMove with input as a string (e.g., "1 2")
    // Further demonstrates SRP by providing an alternate way to make a move
    void makeMove(const string& input) {
        // Parse row and column from the input string
        int row = input[0] - '0';
        int col = input[2] - '0';

        // Validate the move and call the appropriate makeMove function
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && !isOccupied(row, col)) {
            makeMove(row, col);
        } else {
            cout << "Invalid move. Try again.\n";  // Notify the user about invalid moves
        }
    }

    // Check if a specific cell on the board is already occupied
    // Demonstrates SRP by focusing on checking the state of a cell
    bool isOccupied(int row, int col) {
        return (this->board[row][col] == 'X' || this->board[row][col] == 'O');
    }

    // Check if the board is full (no empty cells)
    bool isFull() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->board[i][j] == '-') {
                    return false;  // If any cell is empty, the board is not full
                }
            }
        }
        return true;  // All cells are occupied
    }

    // Static function to get the total moves made across all TicTacToe games
    // Adheres to SRP by providing statistics specific to this game
    static int getTotalMoves() {
        return totalMoves;
    }

    // Getter for the current player's turn
    // Demonstrates encapsulation by providing controlled access to `turn`
    int getTurn() const {
        return turn;
    }

private:
    // Check if there is a winning condition in any row
    bool checkRow() {
        for (int i = 0; i < 3; i++) {
            if (this->board[i][0] != '-' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) {
                return true;  // Winning row found
            }
        }
        return false;
    }

    // Check if there is a winning condition in any column
    bool checkCol() {
        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] != '-' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]) {
                return true;  // Winning column found
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
    // Create a TicTacToe game instance using dynamic memory allocation
    // Demonstrates dynamic memory allocation and SRP by separating game management logic
    TicTacToe* game = new TicTacToe();
    game->displayBoard();  // Display the initial state of the board

    string input;  // Variable to hold user input for moves
    while (true) {
        // Prompt the current player to make a move
        cout << "Player " << (game->getTurn() == 1 ? "1 (X)" : "2 (O)") << ", enter your move (row and column separated by space or as 'row col'): ";
        getline(cin, input);  // Get the entire line of input

        // Validate input format and process the move
        if (input.size() == 3 && isdigit(input[0]) && input[1] == ' ' && isdigit(input[2])) {
            game->makeMove(input);
        } else {
            cout << "Invalid move format. Enter two digits separated by space.\n";
            continue;  // Skip to the next iteration
        }

        game->displayBoard();  // Display the board after the move

        // Check if the current player has won
        if (game->checkWin()) {
            cout << "Player " << (game->getTurn() == 0 ? "1 (X)" : "2 (O)") << " wins!\n";
            break;  // Exit the loop
        }

        // Check if the game is a draw (board is full)
        if (game->isFull()) {
            cout << "It's a draw!\n";
            break;  // Exit the loop
        }
    }

    delete game;  // Free the dynamically allocated memory
    return 0;
}
