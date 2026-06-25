#include "platforms.h"

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
            y_pos -= GetRandomValue(160, 320);
        }

        platform_manager.platforms[i] = (Rectangle){
            x_pos,
            y_pos,
            PLATFORM_WIDTH,
            PLATFORM_HEIGHT
        };
    }

    platform_manager.last_platform_y = y_pos;

    return platform_manager;
}

void draw_platforms(Rectangle platforms[])
{
    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        DrawRectangleRec(platforms[i], DARKGRAY);
    }
}

void check_platforms_collision(Frog *frog, Rectangle platforms[])
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
                printf("land\n");
            }
        }
    }
}

void update_platforms(PlatformManager *platform_manager)
{
    for (int i = 0; i < PLATFORMS_SIZE; i++)
    {
        if (platform_manager->platforms[i].y >= SCREEN_HEIGHT)
        {
            platform_manager->last_platform_y += GetRandomValue(160, 320);
            platform_manager->platforms[i] = (Rectangle){
                GetRandomValue(PLATFORM_MIN_X, PLATFORM_MAX_X),
                platform_manager->last_platform_y,
                PLATFORM_WIDTH,
                PLATFORM_HEIGHT
            };
        }
    }
}
