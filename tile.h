#pragma once

#include "constants.h"
#include <iostream>

class Tile {
  public:
    Tile();
    bool stepOn(short id);
    bool changeValue(short id);
    void reset();
    void printTile();

  private:
    short value;
    bool isStep;
};
