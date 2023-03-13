#include "bot.h"

Bot::Bot(short id, std::string name) {
    this->id = id;
    this->name = name;
}

bool Bot::update() {
    pickMove();
    move();
    return true;
}

bool Bot::move() { return false; }

void Bot::pickMove() {}

Bot::~Bot() {}
