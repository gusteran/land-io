#include "tile.h"

Tile::Tile() { this->reset(); }

void Tile::reset() {
    this->value = 0;
    this->isStep = false;
}

bool Tile::stepOn(short id) {
    // TODO: Implement evaluation of whether a player can step on this tile
    if (this->isStep)
        return false;
    this->isStep = true;
    this->value = id;
    return true;
}

bool Tile::changeValue(short id) {
    // TODO: Implement evaluation of whether a player can step on this tile
    this->value = id;
    this->isStep = false;
    return true;
}

void Tile::printTile() { std::cout << this->value << (isStep ? "*" : " "); }
