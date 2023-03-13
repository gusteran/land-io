#include "board.h"

Board::Board(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            this->field[i][j] = 0;
        }
    }
}

bool Board::update(){
    return true;
}