
#include "X_O_Pyramid_Board.h"


X_O_Pyramid_Board::X_O_Pyramid_Board() {
    n_rows = 3;
    board = new char*[n_rows];
    board[0] = new char [1]{0};
    board[1] = new char [3]{0};
    board[2] = new char [5]{0};
}

bool X_O_Pyramid_Board::update_board(int x, int y, char mark) {
    if(x==0&&y==0 && board[x][y]==0 || x==1&&(y>=0 && y<=2) && board[x][y]==0
       || x==2&& (y>=0 && y<=4)&&board[x][y]==0){
        board[x][y] = (char)toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

void X_O_Pyramid_Board::display_board() {
    for (int i: {0,1,2}) {
        cout<<"\n";
        cout <<setw(20) <<"| ";
        for (int j = 0; j < 1; ++j) {
            cout<<'('<<i<<','<<j<<')';
            cout << setw(2) << board [i][j] << " |";
        }i++;
        cout << "\n\t  -----------------------------";
        cout<<endl;
        cout<<setw(14)<<"|";
        for (int j = 0; j < 3; ++j) {
            cout<<'('<<i<<','<<j<<')';
            cout << setw(1) << board [i][j] << " |";
        }i++;
        cout << "\n\t  -------------------------------";
        cout<<endl;
        cout<<"| ";
        for (int j = 0; j < 5; ++j) {
            cout<<'('<<i<<','<<j<<')';
            cout << setw(2) << board [i][j] << " |";
        }i+=2;
        break;
    }
    cout << endl;
}

bool X_O_Pyramid_Board::is_winner() {
    char row_win[4], col_win[1], diag_win[2];
    int j = 0,row = 2;
    for (int i:{1,2,3,4}) {
        if(i==1) {
            row_win[i] = (char) (board[i][j] & board[i][j+1] & board[i][j+2]); }
        else{
            row_win[row] = (char)(board[row][j] & board[row][j+1] & board[row][j+2]);
            ++j;
            if(row_win[row] == 'X' ){
                break;
            }
        }
    }

    diag_win[0] = char(board[0][0] & board[1][0] & board[2][0]);
    diag_win[1] = char(board[0][0] & board[1][2] & board[2][4]);
    col_win[0] = char(board[0][0] & board[1][1] & board[2][2]);
    for(int i:{1,2,3,4}){
        if(i==1&&(row_win[i] && (row_win[i] == board[i][1]))||
           row_win[row]&&(row_win[row]==board[row][i])){
            return true;
        }
    }
    if((diag_win[0]==board[0][0])&&diag_win[0] || (diag_win[1]==board[0][0])&&diag_win[1]){
        return true;
    }
    if((col_win[0] ==board[0][0])&&col_win[0]){
        return true;
    }
    return false;
}

bool X_O_Pyramid_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Pyramid_Board::game_is_over() {
    return n_moves >= 9;
}

X_O_Pyramid_Board::~X_O_Pyramid_Board() {
    for (int i = 0; i < n_rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}
//X_O_Pyramid_Board::~X_O_Pyramid_Board() {
//    delete[]board;
//}
