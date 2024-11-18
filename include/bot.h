#ifndef SNAKE_BOT_H
#define SNAKE_BOT_H

#include <raylib.h>

double getAngleRelSDF(Vector2 s, Vector2 d, Vector2 f);
void botmove(double a, Vector2 *d);

#endif //SNAKE_BOT_H
