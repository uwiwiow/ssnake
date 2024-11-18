#include "bot.h"

#include <raymath.h>

double getAngleRelSDF(Vector2 s, Vector2 d, Vector2 f) {
    Vector2 v = Vector2Subtract(f, s);

    double magnitude_v = Vector2Length(v);
    if (magnitude_v == 0) {
        return 0;
    }

    double angle = acos(Vector2DotProduct(d, v) / magnitude_v);

    if ((d.x * v.y - d.y * v.x) < 0) {
        angle = -angle;
    }

    return angle * RAD2DEG;
}

void botmove(double a, Vector2 *d) {
    if (a < -1.0f)
        *d = Vector2Rotate(*d, -5 * GetFrameTime());
    if (a > 1.0f)
        *d = Vector2Rotate(*d, 5 * GetFrameTime());
}