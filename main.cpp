#include<iostream>
#include<string>
using namespace std;

class TicTacToe {
private:
    char board[3][3];    // Private: Hides the internal representation of the board
    int turn;            // Private: Hides the internal state of whose turn it is
    static int gameCount;  // Static variable to track the number of games
    static int totalMoves; // Static variable to track total moves made across all games

public:
    // 1. Default Constructor
    TicTacToe() {
        this->resetBoard();  // Public: Allows the board to be reset
        this->turn = 1;      // Sets the initial turn to Player-1 ('X')
        gameCount++;          // Increment game count when a new game starts
        cout << "Default Constructor called. New game initialized.\n";
    }

    // 2. Parameterized Constructor
    TicTacToe(char initialBoard[3][3], int initialTurn) {
        for(int i = 0; i < 3; i++) {          // Initialize board with provided values
            for(int j = 0; j < 3; j++) {
                this->board[i][j] = initialBoard[i][j];
            }
        }
        this->turn = initialTurn;             // Set the initial turn
        gameCount++;                           // Increment game count when a new game starts
        cout << "Parameterized Constructor called. Custom game initialized.\n";
    }

    // 3. Destructor
    ~TicTacToe() {
        cout << "Destructor called. Game ended.\n";
    }

    void resetBoard() {  // Public: Allows access to reset the board
        // Abstraction hides how the board is reset
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                this->board[i][j] = '-';
            }
        }
    }

    void displayBoard() {  // Public: Allows the user to see the board
        // Abstracts the board's internal structure and presents it in a user-friendly format
        cout << "\n";
        cout << this->board[0][0] << " | " << this->board[0][1] << " | " << this->board[0][2] << endl;
        cout << "---------\n";
        cout << this->board[1][0] << " | " << this->board[1][1] << " | " << this->board[1][2] << endl;
        cout << "---------\n";
        cout << this->board[2][0] << " | " << this->board[2][1] << " | " << this->board[2][2] << endl;
    }

    bool checkRow() {  // Private: Used internally to check rows for a win
        for(int i = 0; i < 3; i++) {
            if(this->board[i][0] != '-' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2]) {
                return true;
            }
        }
        return false;
    }
    
    bool checkCol() {  // Private: Used internally to check columns for a win
        for(int i = 0; i < 3; i++) {
            if(this->board[0][i] != '-' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i]) {
                return true;
            }
        }
        return false;
    }

    bool checkDiag1() {  // Private: Checks first diagonal for a win
        return (this->board[0][0] != '-' && this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2]);
    }

    bool checkDiag2() {  // Private: Checks second diagonal for a win
        return (this->board[0][2] != '-' && this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]);
    }

    bool isFull() {  // Public: Check if the board is full (game draw)
        // Abstraction hides how the board is checked for a full state
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(this->board[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    void makeMove(int row, int col) {  // Public: Allows a player to make a move
        // Abstraction hides how the board is updated based on the turn
        if(this->turn == 1) {
            this->board[row][col] = 'X';
        } else {
            this->board[row][col] = 'O';
        }
        this->turn = (this->turn + 1) % 2;  // Switch turn after the move
        totalMoves++;  // Increment total move count whenever a move is made
    }

    bool isOccupied(int row, int col) {  // Public: Check if a cell is occupied
        return (this->board[row][col] == 'X' || this->board[row][col] == 'O');
    }

    bool checkWin() {  // Public: Check if any player has won
        // Abstracts the win condition logic
        return this->checkRow() || this->checkCol() || this->checkDiag1() || this->checkDiag2();
    }

    // Getter method to access the current player's turn
    int getCurrentTurn() {  // Public: Allows access to check current turn
        return this->turn;
    }

    // Setter method to set the current player's turn
    void setTurn(int player) {  // Public: Allows access to set the current turn
        this->turn = player;
    }

    // Static member function for game count
    static int getGameCount() {  // Public: Allows access to the game count
        return gameCount;
    }

    // Static member function for total number of moves
    static int getTotalMoves() {  // Public: Allows access to the total move count
        return totalMoves;
    }
};

// Initializing static variables
int TicTacToe::gameCount = 0;
int TicTacToe::totalMoves = 0;

int main() {
    // Using Default Constructor
    TicTacToe* game1 = new TicTacToe();  // Dynamic memory allocation

    // Using Parameterized Constructor
    char initialBoard[3][3] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'-', '-', '-'}
    };
    TicTacToe* game2 = new TicTacToe(initialBoard, 0);  // Player-2 starts

    string temp_turn;

    cout << "Player-1 will play with 'X'\n";
    cout << "Player-2 will play with 'O'\n\n";
    
    while(true) {
        cout << "Which Player will turn first (1 or 2): ";
        getline(cin, temp_turn);

        if(temp_turn == "1") {
            game1->setTurn(1);
            break;
        } else if(temp_turn == "2") {
            game1->setTurn(0);
            break;
        } else {
            cout << "Wrong Input! Try Again\n\n";
        }
    }

    int row, col;
    while(true) {
        while(true) {
            cout << "\nEnter a row number (1 or 2 or 3): ";
            cin >> row;
            cout << "Enter a column number (1 or 2 or 3): ";
            cin >> col;

            if(row <= 0 || row >= 4 || col <= 0 || col >= 4) {
                cout << "Invalid Input! Try Again\n";
            } else if(game1->isOccupied(row-1, col-1)) {
                cout << "Place Already Filled! Try Again\n";
            } else {
                break;
            }
        }
        
        game1->makeMove(row-1, col-1);
        game1->displayBoard();

        if(game1->checkWin()) {
            cout << (game1->getCurrentTurn() == 0 ? "Player-2 won the game!\n" : "Player-1 won the game!\n");
            break;
        }

        if(game1->isFull()) {
            cout << "\n****It's a tie!!****\n";
            cout << "Board has been completely filled\n";
            break;
        }
    }

    // Displaying game statistics
    cout << "Total number of games played: " << TicTacToe::getGameCount() << endl;
    cout << "Total number of moves made: " << TicTacToe::getTotalMoves() << endl;

    // Deleting dynamically allocated memory to call destructors
    delete game1;  // Destructor called for game1
    delete game2;  // Destructor called for game2

    return 0;
}
