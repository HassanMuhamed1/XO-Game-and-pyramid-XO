// Class definition for X_O_Board class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1
#include <iostream>
#include <random>
#include <iomanip>
#include <algorithm>
#include"BoardGame_Classes.hpp"

using namespace std;

// Set the board
X_O_Board::X_O_Board () {
    n_rows = 3;
    board = new char*[n_rows];
    board[0] = new char [1]{0};
    board[1] = new char [3]{0};
    board[2] = new char [5]{0};
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_Board::update_board (int x, int y, char mark){
    if(x==0&&y==0 && board[x][y]==0 || x==1&&(y==0||y==1||y==2) && board[x][y]==0
       || x==2&& (y==0||y==1||y==2 ||y==3 || y==4 )&&board[x][y]==0){
        board[x][y] = (char)toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
void X_O_Board::display_board() {
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

// Returns true if there is any winner
// either X or O
// Written in a complex way. DO NOT DO LIKE THIS.
bool X_O_Board::is_winner() {
    char row_win[3], col_win[1], diag_win[2];
    int j = 0,row = 2;
    for (int i:{1,2,3,4}) {
        if(i==1) {
            row_win[i] = (char) (board[i][j] & board[i][j+1] & board[i][j+2]); }
        else{
            row_win[row] = (char)(board[row][j] & board[row][j+1] & board[row][j+2]);
            ++j;
            if(row_win[row] == 'X' || col_win[row] == 'O'){
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

// Return true if 9 moves are done and no winner
bool X_O_Board::is_draw() {
    return (n_moves == 9 && !is_winner());
}

bool X_O_Board::game_is_over () {
    return n_moves >= 9;
}
