#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"

void input(Vector2 *d);
void move(Vector2 *snake, Vector2 d);
Vector2 randVec2ScreenPos();
void procmove(Vector2 *curr, Vector2 prev, float dist);
double getAngleRelSDF(Vector2 s, Vector2 d, Vector2 f);
void botmove(double a, Vector2 *d);

const int width = 640;
const int height = 480;
float body = 10.0f;
bool botmode = false;

int main () {

    InitWindow(width, height, "SNAKE");

    cvector_vector_type(Vector2) snakes = NULL;

    cvector_push_back(snakes, ((Vector2) {320.0f, 240.0f}));
    Vector2 d = {1.0f, 0.0f};

    Vector2 food = randVec2ScreenPos();

    while(!WindowShouldClose()) {

        input(&d);

        if (botmode) {
            botmove(getAngleRelSDF(snakes[0], d, food), &d);
        }

        move(&snakes[0], d);

        if (CheckCollisionCircles(snakes[0], body, food, body/2)) {
            body += 0.5f;
            food = randVec2ScreenPos();
            cvector_push_back(snakes, *(cvector_back(snakes)));
        }

        for (size_t i = 1; i < cvector_size(snakes); ++i) {
            procmove(&snakes[i], snakes[i-1], body);
        }

        BeginDrawing();

            ClearBackground(BLACK);

            for (int i = cvector_size(snakes) - 1; i >= 0; i--) {
                DrawCircleV(snakes[i], body, GREEN);
            }

            DrawCircleV(food, body/2, RED);

            if (botmode) {
                DrawLineV(snakes[0], Vector2Add(snakes[0], Vector2Scale(d, 600.0f)), BLUE);
                DrawText(TextFormat("%.2lf", getAngleRelSDF(snakes[0], d, food)), 150, 10, 20, WHITE);
            }

            DrawText(TextFormat("Controls:\nA - S: move\nB: botmode"), 10, 10, 20, WHITE);
            DrawFPS(10, height - 30);

        EndDrawing();
    }

    cvector_free(snakes);

    return 0;
}

void input(Vector2 *d) {
    if (IsKeyDown(KEY_A))
        *d = Vector2Rotate(*d, -5 * GetFrameTime());

    if (IsKeyDown(KEY_D))
        *d = Vector2Rotate(*d, 5 * GetFrameTime());

    if (IsKeyPressed(KEY_B))
        botmode = !botmode;
}

void move(Vector2 *snake, Vector2 d) {
    snake->x = snake->x + (d.x * (100 + body) * GetFrameTime());
    snake->y = snake->y + (d.y * (100 + body) * GetFrameTime());
}

Vector2 randVec2ScreenPos() {
    return (Vector2) {(float) GetRandomValue(20, width - 20),
                      (float) GetRandomValue(20, height - 20)};
}

void procmove(Vector2 *curr, Vector2 prev, float dist) {

    Vector2 direction = Vector2Subtract(*curr, prev);
    if (Vector2Length(direction) != 0) {
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, dist);
    }
    *curr = Vector2Add(prev, direction);

}

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