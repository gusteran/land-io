#include "board.h"

Board::Board() { generateSpawnLocation(); }

void Board::generateSpawnLocation() {
    const int NUM_SPAWN_LOCATIONS = MAX_PLAYERS * 2;

    int playersPerWall = (NUM_SPAWN_LOCATIONS + 3) / 4;
    int rowInc = ROWS / playersPerWall;
    int colInc = COLS / playersPerWall;
    int row = -rowInc / 2;
    int col = -colInc / 2;

    for (int i = 0; i < NUM_SPAWN_LOCATIONS; i += 2) {
        if (i < NUM_SPAWN_LOCATIONS / 2) {
            row += rowInc;
            spawnLocations.push_back(std::make_pair(row, 1));
            spawnLocations.push_back(std::make_pair(row, COLS - 2));
        } else {
            col += colInc;
            spawnLocations.push_back(std::make_pair(1, col));
            spawnLocations.push_back(std::make_pair(ROWS - 2, col));
        }
    }
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(spawnLocations), std::end(spawnLocations), rng);
}

bool Board::update() {
    for (Player *p : players) {
        MoveResult res = p->update(field);
        if (res == MoveResult::DEATH) {
            killPlayer(p);
        } else if (res == MoveResult::COMPLETE) {
            completeTerritory(p);
        }
    }
    return true;
}

bool Board::spawnPlayer(Player *p) {
    if (players.size() >= MAX_PLAYERS)
        return false;

    players.push_back(p);

    std::pair<int, int> location = spawnLocations[currentSpawnLocation++];
    currentSpawnLocation %= spawnLocations.size();

    for (int i = location.first - 1; i < location.first + 2; i++) {
        for (int j = location.second - 1; j < location.second + 2; j++) {
            field[i][j].changeValue(p->getID());
        }
    }

    p->setLocation(location);
    return true;
}

bool Board::killPlayer(Player *player) {
    // TODO
    return true;
}

// True if territory is gained, false otherwise
bool Board::completeTerritory(Player *player) {
    // TODO
    if (player->trail.empty())
        return false;

    bool startConnected = false;
    bool endConnected = false;
    std::pair<int, int> fillLocation;

    for (std::pair<int, int> neighbor : getNeighbors(player->trail.front())) {
        startConnected = checkConcavity(player, neighbor);
        if (startConnected) {
            fillTerritory(player, neighbor);
            break;
        }
    }

    for (std::pair<int, int> trailTile : player->trail) {
        field[trailTile.first][trailTile.second].clearTrail();
    }

    player->trail.clear();
    return true;
}

// maybe return the area we searched if the capture territory is slow?
bool Board::fillTerritory(Player *player, std::pair<int, int> location) {
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(ROWS,
                                           std::vector<bool>(COLS, false));
    q.push(location);
    visited[location.first][location.second] = true;

    while (!q.empty()) {
        std::pair<int, int> curr = q.front();
        q.pop();
        visited[curr.first][curr.second] = true;

        // Passes if the tile is owned by this player
        if (field[curr.first][curr.second].getValue() == player->getID())
            continue;
        field[curr.first][curr.second].changeValue(player->getID());

        for (std::pair<int, int> neighbor : getNeighbors(curr)) {
            if (!visited[neighbor.first][neighbor.second])
                ;
        }
    }
    return true;
}

// Checks if the tile is a new piece of territory surrounded by
// this players tiles
bool Board::checkConcavity(Player *player, std::pair<int, int> location) {
    if (field[location.first][location.second].getValue() == player->getID())
        return false;

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(ROWS,
                                           std::vector<bool>(COLS, false));
    q.push(location);
    visited[location.first][location.second] = true;

    while (!q.empty()) {
        std::pair<int, int> curr = q.front();
        q.pop();
        visited[curr.first][curr.second] = true;

        // The territory cannot be concanve if the flood fill reaches a wall
        if (againstWall(curr))
            return false;

        // Passes if the tile is owned by this player
        if (field[curr.first][curr.second].getValue() == player->getID())
            continue;

        for (std::pair<int, int> neighbor : getNeighbors(curr)) {
            if (!visited[neighbor.first][neighbor.second])
                ;
        }
    }
    return true;
}

std::vector<std::pair<int, int>>
Board::getNeighbors(std::pair<int, int> location) {
    std::vector<std::pair<int, int>> validNeighbors;
    // up down
    std::pair<int, int> up =
        std::make_pair(location.first + 1, location.second);
    std::pair<int, int> down =
        std::make_pair(location.first - 1, location.second);

    // left right
    std::pair<int, int> left =
        std::make_pair(location.first, location.second - 1);
    std::pair<int, int> right =
        std::make_pair(location.first, location.second + 1);

    if (isInBounds(up))
        validNeighbors.push_back(up);
    if (isInBounds(down))
        validNeighbors.push_back(down);
    if (isInBounds(left))
        validNeighbors.push_back(left);
    if (isInBounds(right))
        validNeighbors.push_back(right);

    return validNeighbors;
}

bool Board::isInBounds(std::pair<int, int> location) {
    return location.first <= ROWS && location.first >= 0 &&
           location.second <= COLS && location.second >= 0;
}

bool Board::againstWall(std::pair<int, int> location) {
    return location.first == ROWS - 1 || location.first == 0 ||
           location.second == COLS - 1 || location.second == 0;
}

void Board::printBoard() {
    std::cout << "spawn locations: ";
    for (int i = 0; i < spawnLocations.size(); i++) {
        std::cout << "(" << spawnLocations[i].first << ", "
                  << spawnLocations[i].second << "), ";
    }
    std::cout << std::endl;
    std::cout << "player locations: ";
    for (int i = 0; i < players.size(); i++) {
        std::cout << "(" << players[i]->getLocation().first << ", "
                  << players[i]->getLocation().second << "), ";
    }
    std::cout << std::endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            field[i][j].printTile();
        }
        std::cout << std::endl;
    }
}
