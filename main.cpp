#include<iostream>
#include<string>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    int turn;
    static int gameCount;  // Static variable to track the number of games
    static int totalMoves; // Static variable to track total moves made across all games

public:
    TicTacToe() {
        this->resetBoard();
        this->turn = 1;
        gameCount++;  // Increment game count when a new game starts
    }
    
    void resetBoard() {
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

    void makeMove(int row, int col) {
        if(this->turn == 1) {
            this->board[row][col] = 'X';
        } else {
            this->board[row][col] = 'O';
        }
        this->turn = (this->turn + 1) % 2;
        totalMoves++;  // Increment total move count whenever a move is made
    }

    bool isOccupied(int row, int col) {
        return (this->board[row][col] == 'X' || this->board[row][col] == 'O');
    }

    bool checkWin() {
        return this->checkRow() || this->checkCol() || this->checkDiag1() || this->checkDiag2();
    }

    int getCurrentTurn() {
        return this->turn;
    }

    void setTurn(int player) {
        this->turn = player;
    }

    static int getGameCount() {  // Getter for static gameCount
        return gameCount;
    }

    static int getTotalMoves() {  // Getter for static totalMoves
        return totalMoves;
    }
};

// Initializing static variables
int TicTacToe::gameCount = 0;
int TicTacToe::totalMoves = 0;

int main() {
    TicTacToe* game = new TicTacToe();  // Dynamic memory allocation

    string temp_turn;

    cout << "Player-1 will play with 'X'\n";
    cout << "Player-2 will play with 'O'\n\n";
    
    while(true) {
        cout << "Which Player will turn first (1 or 2): ";
        getline(cin, temp_turn);

        if(temp_turn == "1") {
            game->setTurn(1);
            break;
        } else if(temp_turn == "2") {
            game->setTurn(0);
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
            } else if(game->isOccupied(row-1, col-1)) {
                cout << "Place Already Filled! Try Again\n";
            } else {
                break;
            }
        }
        
        game->makeMove(row-1, col-1);
        game->displayBoard();

        if(game->checkWin()) {
            cout << (game->getCurrentTurn() == 0 ? "Player-2 won the game!\n" : "Player-1 won the game!\n");
            break;
        }

        if(game->isFull()) {
            cout << "\n****It's a tie!!****\n";
            cout << "Board has been completely filled\n";
            break;
        }
    }

    // Displaying static variables
    cout << "Total number of games played: " << TicTacToe::getGameCount() << endl;
    cout << "Total number of moves made: " << TicTacToe::getTotalMoves() << endl;

    delete game;  // Free the dynamically allocated memory
    return 0;
}
