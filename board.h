#ifndef __BOARD__
#define __BOARD__

#include "constants.h"

class Board {
public:
  Board();
  bool update();

private:
  short * field[ROWS][COLS];
};


#endif
