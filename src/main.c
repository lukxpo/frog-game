#include <raylib.h>
#include "config.h"
#include "frog.h"
#include "platforms.h"


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "frog");

    InitAudioDevice();

    Vector2 spawn_position = {SCREEN_WIDTH / 2 - FROG_WIDTH / 2, 300};
    Frog frog = load_frog(spawn_position);

    Rectangle platforms[PLATFORMS_SIZE];
    load_initial_platforms(platforms);
    int current_platform = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        check_platforms_collision(&frog, platforms);
        check_walls_collision(&frog);

        update_frog(&frog, dt);
        update_aim(&frog, dt);

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        draw_platforms(platforms);
        draw_frog(&frog);
        draw_aim(&frog);
        draw_walls();

        EndDrawing();
    }

    UnloadTexture(frog.texture);
    UnloadSound(frog.jump_sound);
    UnloadSound(frog.wall_hit_sound);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}