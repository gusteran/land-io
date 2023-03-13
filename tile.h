#pragma once

#include "constants.h"
#include <iostream>

class Tile {
  public:
    Tile();
    MoveResult stepOn(short id);
    bool changeValue(short id);
    short getValue() { return value; }
    void reset();
    void printTile();
    bool isTrail() { return isStep; }
    void clearTrail() { isStep = false; }

  private:
    short value;
    bool isStep;
};
