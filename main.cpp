#include<iostream>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    int turn;

public:
    TicTacToe() {
        this->resetBoard();
        this->turn = 1;
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
};

int main() {
    TicTacToe games[1];  // Array of 1 TicTacToe object

    string temp_turn;

    cout << "Player-1 will play with 'X'\n";
    cout << "Player-2 will play with 'O'\n\n";
    
    while(true) {
        cout << "Which Player will turn first (1 or 2): ";
        getline(cin, temp_turn);

        if(temp_turn == "1") {
            games[0].setTurn(1);
            break;
        } else if(temp_turn == "2") {
            games[0].setTurn(0);
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
            } else if(games[0].isOccupied(row-1, col-1)) {
                cout << "Place Already Filled! Try Again\n";
            } else {
                break;
            }
        }
        
        games[0].makeMove(row-1, col-1);
        games[0].displayBoard();

        if(games[0].checkWin()) {
            cout << (games[0].getCurrentTurn() == 0 ? "Player-2 won the game!\n" : "Player-1 won the game!\n");
            break;
        }

        if(games[0].isFull()) {
            cout << "\n****It's a tie!!****\n";
            cout << "Board has been completely filled\n";
            break;
        }
    }
}
