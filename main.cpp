#include<iostream>
#include<string>
using namespace std;

// Base class for games
class Game {
protected:
    static int gameCount;  // Static variable to track the number of games created
public:
    // Constructor increments the game count whenever a new game is created
    Game() {
        gameCount++;  
    }
    
    // Pure virtual function for resetting the game board, must be overridden by derived classes
    virtual void resetBoard() = 0;  

    // Static function to get the total number of games created
    static int getGameCount() {  
        return gameCount;
    }
};

// Initializing static variable
int Game::gameCount = 0;

// Derived class inheriting from Game (Single Inheritance)
class TicTacToe : public Game {
protected:
    char board[3][3];  // 2D array to represent the Tic-Tac-Toe board
    int turn;          // Variable to track whose turn it is (1 or 2)
    static int totalMoves; // Static variable to track total moves made across all Tic-Tac-Toe games

public:
    // Constructor initializes the game board and sets the initial turn
    TicTacToe() {
        this->resetBoard();  // Call to reset the board
        this->turn = 1;      // Player 1 starts first
        cout << "TicTacToe game initialized.\n";
    }

    // Destructor announces when the game ends
    ~TicTacToe() {
        cout << "TicTacToe game ended.\n";
    }

    // Override of the pure virtual function from Game to reset the board
    void resetBoard() override {  
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                this->board[i][j] = '-';  // Set all positions on the board to '-'
            }
        }
    }

    // Function to display the current state of the board
    void displayBoard() {
        cout << "\n";
        cout << this->board[0][0] << " | " << this->board[0][1] << " | " << this->board[0][2] << endl;
        cout << "---------\n";
        cout << this->board[1][0] << " | " << this->board[1][1] << " | " << this->board[1][2] << endl;
        cout << "---------\n";
        cout << this->board[2][0] << " | " << this->board[2][1] << " | " << this->board[2][2] << endl;
    }

    // Function to check if a player has won the game
    bool checkWin() {
        return (checkRow() || checkCol() || checkDiag1() || checkDiag2());
    }

    // Function Overloading: makeMove with row and column as integers
    void makeMove(int row, int col) {
        // Assign 'X' or 'O' based on the current turn
        if(this->turn == 1) {
            this->board[row][col] = 'X';
        } else {
            this->board[row][col] = 'O';
        }
        this->turn = (this->turn + 1) % 2;  // Switch turns between players
        totalMoves++;  // Increment the total moves made in the game
    }

    // Function Overloading: makeMove with row and column as a single string input (e.g., "1 2")
    void makeMove(const string& input) {
        // Parse row and column from the input string
        int row = input[0] - '0';
        int col = input[2] - '0';
        // Check if the move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && !isOccupied(row, col)) {
            makeMove(row, col);  // Call the other makeMove function with integer arguments
        } else {
            cout << "Invalid move. Try again.\n";  // Inform the user of an invalid move
        }
    }

    // Check if a cell on the board is already occupied
    bool isOccupied(int row, int col) {
        return (this->board[row][col] == 'X' || this->board[row][col] == 'O');
    }

    // Check if the board is full
    bool isFull() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(this->board[i][j] == '-') {
                    return false;  // If any position is still empty, the board is not full
                }
            }
        }
        return true;  // All positions are filled
    }

    // Static function to get the total moves made across all TicTacToe games
    static int getTotalMoves() {  
        return totalMoves;
    }

    // Getter for the current player's turn
    int getTurn() const {  
        return turn;
    }

private:
    // Check for winning conditions in rows
    bool checkRow() {
        for(int i = 0; i < 3; i++) {
            if(this->board[i][0] != '-' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) {
                return true;  // Return true if a winning row is found
            }
        }
        return false;  // No winning row found
    }

    // Check for winning conditions in columns
    bool checkCol() {
        for(int i = 0; i < 3; i++) {
            if(this->board[0][i] != '-' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]) {
                return true;  // Return true if a winning column is found
            }
        }
        return false;  // No winning column found
    }

    // Check for winning condition in the main diagonal
    bool checkDiag1() {
        return (this->board[0][0] != '-' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]);
    }

    // Check for winning condition in the anti-diagonal
    bool checkDiag2() {
        return (this->board[0][2] != '-' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]);
    }
};

// Initializing static variable
int TicTacToe::totalMoves = 0;

int main() {
    // Creating an instance of TicTacToe using dynamic memory allocation
    TicTacToe* game = new TicTacToe();  
    game->displayBoard();  // Display the initial game board

    string input;  // Variable to hold user input for moves
    while(true) {
        // Prompt the current player for their move
        cout << "Player " << (game->getTurn() == 1 ? "1 (X)" : "2 (O)") << ", enter your move (row and column separated by space or as 'row col'): ";
        getline(cin, input);  // Get the entire line of input

        // Validate the input format
        if (input.size() == 3 && isdigit(input[0]) && input[1] == ' ' && isdigit(input[2])) {
            game->makeMove(input);  // Call overloaded makeMove function with string input
        } else {
            cout << "Invalid move format. Enter two digits separated by space.\n";  // Inform the user of invalid input
            continue;  // Go to the next iteration of the loop
        }

        game->displayBoard();  // Display the board after the move

        // Check if the current player has won
        if (game->checkWin()) {
            cout << "Player " << (game->getTurn() == 0 ? "1 (X)" : "2 (O)") << " wins!\n";
            break;  // Exit the loop if there's a winner
        }

        // Check if the game is a draw
        if (game->isFull()) {
            cout << "It's a draw!\n";
            break;  // Exit the loop if the board is full
        }
    }

    // Display the total games played and total moves made
    cout << "Total games played: " << Game::getGameCount() << endl;
    cout << "Total moves made: " << TicTacToe::getTotalMoves() << endl;

    delete game;  // Free the dynamically allocated memory for the game instance

    return 0;  // End of the program
}
