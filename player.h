#ifndef __PLAYER__
#define __PLAYER__

#include "constants.h"

// Abstact class to define the player interface
class Player {
public:
bool update();

private:
bool move();
bool turn(Direction direction);
    
};

#endif
