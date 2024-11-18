#include <raylib.h>
#include <raymath.h>


#include "config.h"
#include "globals.h"
#include "input.h"
#include "move.h"
#include "utils.h"
#include "bot.h"


#define CVECTOR_LOGARITHMIC_GROWTH
#include "cvector.h"


int main () {

    InitWindow(width, height, "SNAKE");


    Vector2 center = {(float) width / 2, (float) height / 2};
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;
    camera.offset = center;


    cvector_vector_type(Vector2) snakes = NULL;
    cvector_push_back(snakes, ((Vector2) {320.0f, 240.0f}));
    Vector2 d = {1.0f, 0.0f};
    Vector2 food = randVec2ScreenPos();


    while(!WindowShouldClose()) {

        input(&d);

        if (botmode)
            botmove(getAngleRelSDF(snakes[0], d, food), &d);

        move(&snakes[0], d);


        camera.target = snakes[0];
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
            camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 64.0f);
        }


        if (CheckCollisionCircles(snakes[0], body, food, body/2)) {
            body += 0.5f;
            food = randVec2ScreenPos();
            cvector_push_back(snakes, *(cvector_back(snakes)));
        }


        for (size_t i = 1; i < cvector_size(snakes); ++i) {
            procmove(&snakes[i], snakes[i-1], body);
        }


        BeginDrawing();

            ClearBackground(DARKGRAY);


            BeginMode2D(camera);

                for (int i = cvector_size(snakes) - 1; i >= 0; i--) {
                    DrawCircleV(snakes[i], body, GREEN);
                }

                DrawCircleV(food, body/2, RED);

                if (botmode)
                    DrawLineV(snakes[0], Vector2Add(snakes[0], Vector2Scale(d, 600.0f)), BLUE);
                

            EndMode2D();


            if (botmode)
                DrawText(TextFormat("%.2lf", getAngleRelSDF(snakes[0], d, food)), 150, 10, 20, WHITE);


            DrawText(TextFormat("Controls:\nA - S: move\nB: botmode"), 10, 10, 20, WHITE);
            DrawFPS(10, height - 30);

        EndDrawing();
    }

    cvector_free(snakes);

    return 0;
}

