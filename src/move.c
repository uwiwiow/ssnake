#include "move.h"

#include <raymath.h>
#include "globals.h"

void move(Vector2 *snake, Vector2 d) {
    snake->x = snake->x + (d.x * (100 + body) * GetFrameTime());
    snake->y = snake->y + (d.y * (100 + body) * GetFrameTime());
}

void procmove(Vector2 *curr, Vector2 prev, float dist) {

    Vector2 direction = Vector2Subtract(*curr, prev);
    if (Vector2Length(direction) != 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, dist);
    }
    *curr = Vector2Add(prev, direction);

}