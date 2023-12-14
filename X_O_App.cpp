// Class definition for XO_App class
// Author:  Mohammad El-Ramly
// Date:    10/10/2022
// Version: 1

#include <iostream>
#include"BoardGame_Classes.hpp"
#include "X_O_Pyramid_Board.h"


using namespace std;


int main() {
    int choice;
    Player* players[2];
    players[0] = new Player (1, 'x');

    cout << "Welcome to FCAI X-O Game. :)\n";
    cout<<"1-3x3 Tic Tac Toe \n";
    cout<<"2-Pyramid XO \n";
    cout<<"3-Connect Four \n";
    cout<<"4-5x5 Tic Tac Toe \n";
    cout<<"Enter name or number of game which you want: ";

    int choiceGame;
    cin>>choiceGame;

    cout << "Press 1 if you want to play with computer and 2 if multiplayer: ";
    cin >> choice;
    if(choiceGame == 1 ){
        if(choice == 1){
            players[1] = new RandomPlayer ('o', 3);
        }
        else{
            players[1] = new Player (2, 'o');
        }
        GameManager x_o_game (new X_O_Board(), players);
        x_o_game.run();
    }
    else if(choiceGame == 2){
        if(choice == 1){
            players[1] = new RandomPlayer ('o', 3);
        }
        else{
            players[1] = new Player (2, 'o');
        }
        GameManager x_o_game (new X_O_Pyramid_Board(), players);
        x_o_game.run();
    }
    else if (choiceGame == 3){
        if(choice == 1){
            players[1] = new RandomPlayer ('o', 3);
        }
        else{
            players[1] = new Player (2, 'o');
        }
//        GameManager x_o_game (new X_O_Pyramid_Board(), players);
//        x_o_game.run();
    }
    else if (choiceGame == 4){
        if(choice == 1){
            players[1] = new RandomPlayer ('o', 3);
        }
        else{
            players[1] = new Player (2, 'o');
        }
//        GameManager x_o_game (new X_O_Pyramid_Board(), players);
//        x_o_game.run();
    }

   /* if (choice != 1)
        players[1] = new Player (2, 'o');
    else
        //Player pointer points to child
        players[1] = new RandomPlayer ('o', 3);

    GameManager x_o_game (new X_O_Pyramid_Board(), players);
    x_o_game.run();*/
//   delete[]players[1];
//   delete[]players[1];

    system ("pause");
}
