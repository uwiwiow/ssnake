#include "input.h"

#include <raymath.h>
#include "globals.h"

void input(Vector2 *d) {
    if (IsKeyDown(KEY_A))
        *d = Vector2Rotate(*d, -5 * GetFrameTime());

    if (IsKeyDown(KEY_D))
        *d = Vector2Rotate(*d, 5 * GetFrameTime());

    if (IsKeyPressed(KEY_B))
        botmode = !botmode;
}