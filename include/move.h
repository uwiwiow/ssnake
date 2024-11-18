#ifndef SNAKE_MOVE_H
#define SNAKE_MOVE_H

#include <raylib.h>

void move(Vector2 *snake, Vector2 d);
void procmove(Vector2 *curr, Vector2 prev, float dist);

#endif //SNAKE_MOVE_H
