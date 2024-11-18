#include "utils.h"

#include "config.h"

Vector2 randVec2ScreenPos() {
    return (Vector2) {(float) GetRandomValue(20, width - 20),
                      (float) GetRandomValue(20, height - 20)};
}
