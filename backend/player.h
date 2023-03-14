#pragma once

#include "constants.h"
#include "tile.h"
#include <string>
#include <vector>

// Abstact class to define the player interface
class Player {
  public:
    virtual MoveResult update(Tile (&field)[ROWS][COLS]) = 0;
    virtual ~Player() {}
    short getID() { return id; }
    std::string getName() { return name; }
    std::pair<int, int> getLocation() { return location; }

    virtual void setLocation(std::pair<int, int> location) {
        this->location = location;
    };
    std::vector<std::pair<int, int>> trail;

  protected:
    short id;
    std::string name;
    Direction direction;
    std::pair<int, int> location;
    virtual MoveResult move(Tile (&field)[ROWS][COLS]) = 0;
    bool facingWall() {
        switch (direction) {
        case NORTH:
            return location.first == ROWS - 1;
        case SOUTH:
            return location.first == 0;
        case EAST:
            return location.second == COLS - 1;
        case WEST:
            return location.second == 0;
        case STOPPED:
            return false;
        };
    }
};
