#pragma once

#define ROWS 16
#define COLS 16
#define MAX_PLAYERS 3
#define SLEEP_TIME 500     // ms
#define GAME_DURATION 1000 // ms

#define DIRECTIONS 5
enum Direction { NORTH, EAST, SOUTH, WEST, STOPPED };

/**
 * IDLE = not moving
 * DEATH - dead
 * STEP = movement outside territory
 * COMPLETE = movement inside territory
 */
#define MOVE_RESULT 4
enum MoveResult { IDLE, DEATH, STEP, COMPLETE };
