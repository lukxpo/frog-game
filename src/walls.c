#include "walls.h"

void check_walls_collision(Frog *frog)
{
    if (frog->feet.x < LEFT_WALL_X + WALL_WIDTH) 
    {
        frog->feet.x = LEFT_WALL_X + WALL_WIDTH;
        frog->velocity.x *= -1;
    };

    if (frog->feet.x + frog->feet.width > RIGHT_WALL_X)
    {
        frog->feet.x = RIGHT_WALL_X - frog->feet.width;
        frog->velocity.x *= -1;
    };
}

void draw_walls(void)
{
    DrawRectangle(
        LEFT_WALL_X,
        0,
        WALL_WIDTH,
        SCREEN_HEIGHT,
        GRAY
    );

    DrawRectangle(
        RIGHT_WALL_X,
        0,
        WALL_WIDTH,
        SCREEN_HEIGHT,
        GRAY
    );
}