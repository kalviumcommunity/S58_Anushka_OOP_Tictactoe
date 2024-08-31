#include<iostream>
using namespace std;

#include<iostream>
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    int turn;

public:
    TicTacToe() {
        resetBoard();
        turn = 1;  // Default starting turn
    }
    
    void resetBoard() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
    }
    
    void displayBoard() {
        cout << "\n";
        cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
        cout << "---------\n";
        cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
        cout << "---------\n";
        cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    }

    bool checkRow() {
        for(int i = 0; i < 3; i++) {
            if(board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true;
            }
        }
        return false;
    }
    
    bool checkCol() {
        for(int i = 0; i < 3; i++) {
            if(board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return true;
            }
        }
        return false;
    }

    bool checkDiag1() {
        return (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]);
    }

    bool checkDiag2() {
        return (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]);
    }

    bool isFull() {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(board[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    void makeMove(int row, int col) {
        if(turn == 1) {
            board[row][col] = 'X';
        } else {
            board[row][col] = 'O';
        }
        turn = (turn + 1) % 2; // Switch turns
    }

    bool isOccupied(int row, int col) {
        return (board[row][col] == 'X' || board[row][col] == 'O');
    }

    bool checkWin() {
        return checkRow() || checkCol() || checkDiag1() || checkDiag2();
    }

    int getCurrentTurn() {
        return turn;
    }

    void setTurn(int player) {
        turn = player;
    }
};

int main() {
    TicTacToe game;
    string temp_turn;

    cout << "Player-1 will play with 'X'\n";
    cout << "Player-2 will play with 'O'\n\n";
    
    while(true) {
        cout << "Which Player will turn first (1 or 2): ";
        getline(cin, temp_turn);

        if(temp_turn == "1") {
            game.setTurn(1);
            break;
        } else if(temp_turn == "2") {
            game.setTurn(0);
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
            } else if(game.isOccupied(row-1, col-1)) {
                cout << "Place Already Filled! Try Again\n";
            } else {
                break;
            }
        }
        
        game.makeMove(row-1, col-1);
        game.displayBoard();

        if(game.checkWin()) {
            cout << (game.getCurrentTurn() == 0 ? "Player-2 won the game!\n" : "Player-1 won the game!\n");
            break;
        }

        if(game.isFull()) {
            cout << "\n****It's a tie!!****\n";
            cout << "Board has been completely filled\n";
            break;
        }
    }
}
