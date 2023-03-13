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
        if(res == MoveResult::DEATH){
            //TODO: kill player
        } else if(res == MoveResult::COMPLETE){
            //TODO: complete their territory
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
