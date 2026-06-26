#include "platforms.h"
#include "stdio.h"

PlatformManager load_platform_manager(void)
{
    PlatformManager platform_manager;

    int x_pos = 0;
    int y_pos = 0;

    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        if (i == 0)
        {
            x_pos = SCREEN_WIDTH / 2 - PLATFORM_WIDTH / 2;
            y_pos = SCREEN_HEIGHT - 50;
        }
        else
        {
            x_pos = GetRandomValue(PLATFORM_MIN_X, PLATFORM_MAX_X);
            y_pos -= GetRandomValue(PLATFORM_MIN_Y_INCREMENT, PLATFORM_MAX_Y_INCREMENT);
        }

        platform_manager.platforms[i] = (Rectangle){
            x_pos,
            y_pos,
            PLATFORM_WIDTH,
            PLATFORM_HEIGHT
        };
    }

    platform_manager.last_platform = PLATFORMS_SIZE - 1;

    return platform_manager;
}

void draw_platforms(const Rectangle platforms[])
{
    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        DrawRectangleRec(platforms[i], DARKGRAY);
    }
}

void check_platforms_collision(Frog *frog, Rectangle platforms[], ScoreManager *score_manager)
{
    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        if (CheckCollisionRecs(frog->feet, platforms[i]) && frog->velocity.y > 0)
        {
            frog->is_jumping = false;
            frog->velocity.y = 0;
            frog->feet.y = platforms[i].y - FEET_HEIGHT;
            frog->position.y = frog->feet.y - FEET_OFFSET_Y;
            frog->current_frame = IDLE;
            if (i != frog->current_platform)
            {   
                score_manager->scored = true;
                score_manager->score += pow(2, frog->wall_hits);
                PlaySound(score_manager->score_sound);

                int delta_y = platforms[i].y - platforms[frog->current_platform].y;
                frog->current_platform = i;
                frog->position.y -= delta_y;
                for (int j = 0; j < PLATFORMS_SIZE; j++)
                {
                    platforms[j].y -= delta_y;
                }

                return true;
            }

            frog->wall_hits = 0;
        }
    }

    return false;
}

void update_platforms(PlatformManager *platform_manager)
{
    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        if (platform_manager->platforms[i].y >= SCREEN_HEIGHT)
        {   
            platform_manager->platforms[i] = (Rectangle){
                GetRandomValue(PLATFORM_MIN_X, PLATFORM_MAX_X),
                platform_manager->platforms[platform_manager->last_platform].y - GetRandomValue(PLATFORM_MIN_Y_INCREMENT, PLATFORM_MAX_Y_INCREMENT),
                PLATFORM_WIDTH,
                PLATFORM_HEIGHT
            };
            platform_manager->last_platform = i;
        }
    }
}
