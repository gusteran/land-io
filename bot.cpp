#include "bot.h"

Bot::Bot(short id, std::string name) {
    this->id = id;
    this->name = name;
    this->direction = STOPPED;
}

MoveResult Bot::update(Tile (&field)[ROWS][COLS]) {
    pickMove(field);
    MoveResult res = move(field);
    if (res == MoveResult::STEP)
        trail.push_back(location);
    return res;
}

// Returns true if legal move, returns false if they die
MoveResult Bot::move(Tile (&field)[ROWS][COLS]) {
    if (facingWall()) {
        std::cout << "bot " << id << " is facing a wall" << std::endl;
        return MoveResult::IDLE;
    }
    switch (direction) {
    case NORTH:
        location.first++;
        break;
    case SOUTH:
        location.first--;
        break;
    case EAST:
        location.second++;
        break;
    case WEST:
        location.second--;
        break;
    case STOPPED:
        return MoveResult::IDLE;
    };
    return field[location.first][location.second].stepOn(id);
}

void Bot::pickMove(Tile (&field)[ROWS][COLS]) {
    if (!directions.empty()) {
        direction = directions.back();
        directions.pop_back();
    } else {
        direction = Direction(rand() % DIRECTIONS);
        std::cout << "bot " << id << " picking move " << direction << std::endl;
        if (facingWall() || facingTrail(field))
            pickMove(field);
    }
}

bool Bot::facingTrail(Tile (&field)[ROWS][COLS]) {
    std::pair<int, int> nextPos = location;
    switch (direction) {
    case NORTH:
        nextPos.first++;
        break;
    case SOUTH:
        nextPos.first--;
        break;
    case EAST:
        nextPos.second++;
        break;
    case WEST:
        nextPos.second--;
        break;
    case STOPPED:
        return false;
    };
    return field[nextPos.first][nextPos.second].isTrail();
}

Bot::~Bot() {}
