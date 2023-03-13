#pragma once

#include "constants.h"
#include <iostream>

class Tile {
  public:
    Tile();
    MoveResult stepOn(short id);
    bool changeValue(short id);
    void reset();
    void printTile();
    bool isTrail(){return isStep;}

  private:
    short value;
    bool isStep;
};
