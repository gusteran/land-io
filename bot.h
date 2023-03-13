#pragma once

#include "player.h"

class Bot : public Player {
  public:
    Bot(short id, std::string name);
    ~Bot();
    bool update();

  private:
    void pickMove();
    bool move();
};