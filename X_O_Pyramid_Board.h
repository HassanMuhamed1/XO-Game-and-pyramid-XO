//
// Created by hassa on 12/11/2023.
//

#ifndef XO_X_O_PYRAMID_BOARD_H
#define XO_X_O_PYRAMID_BOARD_H
#include <bits/stdc++.h>
#include"BoardGame_Classes.hpp"

class X_O_Pyramid_Board :public X_O_Board {
public:
    X_O_Pyramid_Board ();
    bool update_board (int x, int y, char mark);
    void display_board();
    bool is_winner();
    bool is_draw();
    bool game_is_over();
};


#endif //XO_X_O_PYRAMID_BOARD_H
