#pragma once

#define ROWS 16
#define COLS 16
#define MAX_PLAYERS 3
#define SLEEP_TIME 500     // ms
#define GAME_DURATION 5000 // ms

#define DIRECTIONS 5
enum Direction { NORTH, EAST, SOUTH, WEST, STOPPED };

#define MOVE_RESULT 4
enum MoveResult { IDLE, DEATH, STEP, COMPLETE};
