#include "platforms.h"

void load_initial_platforms(Rectangle platforms[])
{
    platforms[0] = (Rectangle){
        SCREEN_WIDTH / 2 - PLATFORM_WIDTH / 2,
        500,
        PLATFORM_WIDTH,
        PLATFORM_HEIGHT
    };

    platforms[1] = (Rectangle){
        SCREEN_WIDTH / 2 - PLATFORM_WIDTH / 2,
        200,
        PLATFORM_WIDTH,
        PLATFORM_HEIGHT
    }; 
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
        }
    }
}