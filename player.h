#pragma once

#include "constants.h"
#include <string>

// Abstact class to define the player interface
class Player {
  public:
    virtual bool update() = 0;
    virtual ~Player() {}
    short getID() {return id;}
    std::pair<int, int> getLocation() {return location;}
    virtual void setLocation(std::pair<int, int> location) {this->location = location;};

  protected:
    short id;
    std::string name;
    Direction direction;
    std::pair<int, int> location;
    virtual bool move() = 0;
};
