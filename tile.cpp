#include "tile.h"

Tile::Tile() { this->reset(); }

void Tile::reset() {
    this->value = 0;
    this->isStep = 0;
}

bool Tile::stepOn(int id) {
    // TODO: Implement evaluation of whether a player can step on this tile
    if (this->isStep)
        return false;
    this->isStep = true;
    return this->changeValue(id);
}

bool Tile::changeValue(int id) {
    // TODO: Implement evaluation of whether a player can step on this tile
    this->value = id;
    return true;
}