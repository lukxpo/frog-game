#include <raylib.h>
#include "config.h"
#include "frog.h"
#include "platforms.h"
#include "score.h"


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "frog");

    InitAudioDevice();

    Vector2 spawn_position = {SCREEN_WIDTH / 2 - FROG_WIDTH / 2, 500};
    Frog frog = load_frog(spawn_position);

    PlatformManager platform_manager = load_platform_manager();

    ScoreManager score_manager = load_score_manager();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        // play
        if (frog.current_lives > 0)
        {
            check_platforms_collision(&frog, platform_manager.platforms, &score_manager);
            check_walls_collision(&frog);

            update_frog(&frog, dt);
            update_aim(&frog, dt);
            update_platforms(&platform_manager);
            
            BeginDrawing();
            
            ClearBackground(RAYWHITE);

            draw_platforms(platform_manager.platforms);
            draw_frog(&frog);
            draw_aim(&frog);
            draw_walls();
            draw_score(score_manager.score);

            EndDrawing();
        }
        // gameover
        else
        {      
            BeginDrawing();
        
            ClearBackground(RAYWHITE);

            char *game_over_text = "GAME OVER";
            int text_width = MeasureText(game_over_text, 50);

            DrawText(
                TextFormat(game_over_text),
                SCREEN_WIDTH / 2 - text_width / 2,
                SCREEN_HEIGHT / 3,
                50,
                DARKGREEN
            );

            EndDrawing(); 
        }
    }

    UnloadTexture(frog.texture);
    UnloadSound(frog.jump_sound);
    UnloadSound(frog.wall_hit_sound);
    UnloadSound(score_manager.score_sound);
    CloseAudioDevice();

    CloseWindow();

    return 0;
}