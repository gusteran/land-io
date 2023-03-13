#include "bot.h"

Bot::Bot(short id, std::string name) {
    this->id = id;
    this->name = name;
    this->direction = STOPPED;
}

MoveResult Bot::update(Tile (&field)[ROWS][COLS]) {
    pickMove(field);
    return move(field);
}

// Returns true if legal move, returns false if they die
MoveResult Bot::move(Tile (&field)[ROWS][COLS]) {
    if (facingWall()) {
        std::cout << "bot " << id << " is facing a wall" << std::endl;
        return MoveResult::IDLE;
    }
    switch (direction) {
    case NORTH:
        location.second++;
        break;
    case SOUTH:
        location.second--;
        break;
    case EAST:
        location.first++;
        break;
    case WEST:
        location.first--;
        break;
    case STOPPED:
        return MoveResult::IDLE;
    };
    return field[location.first][location.second].stepOn(id);
}

void Bot::pickMove(Tile (&field)[ROWS][COLS]) {
    direction = Direction(rand() % DIRECTIONS);
    std::cout << "bot " << id << " picking move " << direction << std::endl;
    if (facingWall() || facingTrail(field))
        pickMove(field);
}

bool Bot::facingTrail(Tile (&field)[ROWS][COLS]) {
    std::pair<int, int> nextPos = location;
    switch (direction) {
    case NORTH:
        nextPos.second++;
        break;
    case SOUTH:
        nextPos.second--;
        break;
    case EAST:
        nextPos.first++;
        break;
    case WEST:
        nextPos.first--;
        break;
    case STOPPED:
        return false;
    };
    return field[nextPos.first][nextPos.second].isTrail();
}

Bot::~Bot() {}
