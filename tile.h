#ifndef __TILE__
#define __TILE__

#include "constants.h"

class Tile {
  public:
    Tile();
    bool stepOn(int id);
    bool changeValue(int id);
    void reset();

  private:
    short value;
    bool isStep;
};

#endif
