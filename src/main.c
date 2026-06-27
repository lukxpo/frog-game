#include <raylib.h>
#include "config.h"
#include "frog.h"
#include "platforms.h"
#include "walls.h"
#include "score.h"

void reset_game(Frog *frog, PlatformManager *platform_manager, ScoreManager *score_manager);
void draw_game_over(const int score);


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "frog");

    InitAudioDevice();

    Frog frog = load_frog();
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
            update_score(&score_manager, frog.position, dt);
            
            BeginDrawing();
            
            ClearBackground(RAYWHITE);

            draw_platforms(platform_manager.platforms);
            draw_frog(&frog);
            draw_aim(&frog);
            draw_walls();
            draw_score(&score_manager);
            draw_lives(frog.current_lives);

            EndDrawing();
        }
        // gameover
        else
        {   
            if (IsKeyPressed(KEY_SPACE))
            {
                reset_game(&frog, &platform_manager, &score_manager);
            }

            BeginDrawing();
        
            ClearBackground(RAYWHITE);

            draw_game_over(score_manager.score);

            EndDrawing(); 
        }
    }

    unload_frog(&frog);
    unload_score_manager(&score_manager);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}


void reset_game(Frog *frog, PlatformManager *platform_manager, ScoreManager *score_manager)
{
    unload_frog(frog);
    *frog = load_frog();

    *platform_manager = load_platform_manager();

    unload_score_manager(score_manager);
    *score_manager = load_score_manager();
}

void draw_game_over(const int score)
{
    char *game_over_text = "GAME OVER";
    int text_width = MeasureText(game_over_text, GAME_OVER_TEXT_SIZE);

    DrawText(
        TextFormat(game_over_text),
        SCREEN_WIDTH / 2 - text_width / 2,
        SCREEN_HEIGHT / 3,
        GAME_OVER_TEXT_SIZE,
        DARKGREEN
    );

    const char *ascended_text = TextFormat("Frog Ascended %dm", score);
    text_width = MeasureText(ascended_text, PLAY_AGAIN_TEXT_SIZE);
    DrawText(
        TextFormat(ascended_text),
        SCREEN_WIDTH / 2 - text_width / 2,
        SCREEN_HEIGHT / 2.3,
        PLAY_AGAIN_TEXT_SIZE,
        ORANGE
    );
    
    const char *play_again_text = "PRESS SPACE";
    text_width = MeasureText(play_again_text, PLAY_AGAIN_TEXT_SIZE);
    DrawText(
        TextFormat(play_again_text),
        SCREEN_WIDTH / 2 - text_width / 2,
        SCREEN_HEIGHT / 2,
        PLAY_AGAIN_TEXT_SIZE,
        DARKGRAY
    );
}