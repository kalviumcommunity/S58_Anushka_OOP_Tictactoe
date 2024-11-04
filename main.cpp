#include<iostream>
#include<string>
using namespace std;

// Base class for games
class Game {
protected:
    static int gameCount;  // Static variable to track the number of games
public:
    Game() {
        gameCount++;  // Increment game count whenever a new game is created
    }
    
    virtual void resetBoard() = 0;  // Pure virtual function for resetting the board

    static int getGameCount() {  // Getter for game count
        return gameCount;
    }
};

// Initializing static variable
int Game::gameCount = 0;

// Derived class inheriting from Game (Single Inheritance)
class TicTacToe : public Game {
protected:
    char board[3][3];
    int turn;
    static int totalMoves; // Static variable to track total moves made across all games

public:
    TicTacToe() {
        this->resetBoard();
        this->turn = 1;
        cout << "TicTacToe game initialized.\n";
    }

    ~TicTacToe() {
        cout << "TicTacToe game ended.\n";
    }

    void resetBoard() override {  // Overriding the pure virtual function from Game
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                this->board[i][j] = '-';
            }
        }
    }

    void displayBoard() {
        cout << "\n";
        cout << this->board[0][0] << " | " << this->board[0][1] << " | " << this->board[0][2] << endl;
        cout << "---------\n";
        cout << this->board[1][0] << " | " << this->board[1][1] << " | " << this->board[1][2] << endl;
        cout << "---------\n";
        cout << this->board[2][0] << " | " << this->board[2][1] << " | " << this->board[2][2] << endl;
    }

    bool checkWin() {
        return (checkRow() || checkCol() || checkDiag1() || checkDiag2());
    }

    // Function Overloading: makeMove with row and column as integers
    void makeMove(int row, int col) {
        if(this->turn == 1) {
            this->board[row][col] = 'X';
        } else {
            this->board[row][col] = 'O';
        }
        this->turn = (this->turn + 1) % 2;
        totalMoves++;  // Increment total moves
    }

    // Function Overloading: makeMove with row and column as a single string input (e.g., "1 2")
    void makeMove(const string& input) {
        int row = input[0] - '0';
        int col = input[2] - '0';
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && !isOccupied(row, col)) {
            makeMove(row, col);  // Call the other makeMove function with integer arguments
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }

    bool isOccupied(int row, int col) {
        return (this->board[row][col] == 'X' || this->board[row][col] == 'O');
    }

    bool isFull() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(this->board[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    static int getTotalMoves() {  // Getter for total moves
        return totalMoves;
    }

    int getTurn() const {  // Getter for the current player's turn
        return turn;
    }

private:
    bool checkRow() {
        for(int i = 0; i < 3; i++) {
            if(this->board[i][0] != '-' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) {
                return true;
            }
        }
        return false;
    }

    bool checkCol() {
        for(int i = 0; i < 3; i++) {
            if(this->board[0][i] != '-' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]) {
                return true;
            }
        }
        return false;
    }

    bool checkDiag1() {
        return (this->board[0][0] != '-' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]);
    }

    bool checkDiag2() {
        return (this->board[0][2] != '-' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]);
    }
};

// Initializing static variable
int TicTacToe::totalMoves = 0;

int main() {
    // Single Inheritance: Using TicTacToe that inherits from Game
    TicTacToe* game = new TicTacToe();
    game->displayBoard();

    string input;
    while(true) {
        // Player's move
        cout << "Player " << (game->getTurn() == 1 ? "1 (X)" : "2 (O)") << ", enter your move (row and column separated by space or as 'row col'): ";
        getline(cin, input);

        if (input.size() == 3 && isdigit(input[0]) && input[1] == ' ' && isdigit(input[2])) {
            game->makeMove(input);  // Call overloaded makeMove function with string input
        } else {
            cout << "Invalid move format. Enter two digits separated by space.\n";
            continue;
        }

        game->displayBoard();

        // Check if current player won
        if (game->checkWin()) {
            cout << "Player " << (game->getTurn() == 0 ? "1 (X)" : "2 (O)") << " wins!\n";
            break;
        }

        // Check if it's a draw
        if (game->isFull()) {
            cout << "It's a draw!\n";
            break;
        }
    }

    cout << "Total games played: " << Game::getGameCount() << endl;
    cout << "Total moves made: " << TicTacToe::getTotalMoves() << endl;

    delete game;

    return 0;
}
