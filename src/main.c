#include <raylib.h>
#include "frog.h"

#define SCREEN_WIDTH  720
#define SCREEN_HEIGHT 720

#define WALL_WIDTH   10
#define LEFT_WALL_X  SCREEN_WIDTH / 5
#define RIGHT_WALL_X SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH

#define PLATFORM_WIDTH  50
#define PLATFORM_HEIGHT 5

#define AIM_THICKNESS 1
#define AIM_SIZE      20
#define AIM_ANGLE_CAP 90.0f

void draw_walls(void);
void update_aim(Frog *frog, float dt);
void draw_aim(Frog *frog);


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "frog");

    Vector2 spawn_position = {SCREEN_WIDTH / 2 - FROG_WIDTH / 2, 300};
    Frog frog = create_frog(spawn_position);

    int platforms_size = 2;
    Rectangle platforms[platforms_size];

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

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        for (int i = 0; i < platforms_size; i++)
        {
            if (CheckCollisionRecs(frog.feet, platforms[i]) && frog.velocity.y > 0)
            {
                frog.is_jumping = false;
                frog.velocity.y = 0;
                frog.feet.y = platforms[i].y - FEET_HEIGHT;
                frog.position.y = frog.feet.y - FEET_OFFSET_Y;
            }
        }

        if (frog.feet.x < LEFT_WALL_X + WALL_WIDTH) 
        {
            frog.feet.x = LEFT_WALL_X + WALL_WIDTH;
            frog.velocity.x *= -1;
        };

        if (frog.feet.x + frog.feet.width > RIGHT_WALL_X) 
        {
            frog.feet.x = RIGHT_WALL_X - frog.feet.width;
            frog.velocity.x *= -1;
        };

        update_frog(&frog, dt);
        update_aim(&frog, dt);

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        for (int i = 0; i < platforms_size; i++)
        {
            DrawRectangleRec(platforms[i], DARKGRAY);
        }

        draw_frog(&frog);
        draw_aim(&frog);

        DrawRectangleLines(
            frog.feet.x,
            frog.feet.y,
            frog.feet.width,
            frog.feet.height,
            RED
        );

        draw_walls();

        EndDrawing();
    }

    UnloadTexture(frog.texture);

    CloseWindow();

    return 0;
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

void update_aim(Frog *frog, float dt)
{
    if (IsKeyDown(KEY_LEFT))
    {
        frog->aim_angle -= frog->aim_speed * dt;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        frog->aim_angle += frog->aim_speed * dt;
    }

    if (frog->aim_angle < -AIM_ANGLE_CAP)
    {   
        frog->aim_angle = -AIM_ANGLE_CAP;
    }

    if (frog->aim_angle > AIM_ANGLE_CAP)
    {
        frog->aim_angle = AIM_ANGLE_CAP;
    }
}

void draw_aim(Frog *frog)
{
    Vector2 start = {
        frog->position.x + FROG_WIDTH / 2,
        frog->position.y + FROG_HEIGHT / 2
    };

    Vector2 end = {
        start.x + sinf(frog->aim_angle * DEG2RAD) * AIM_SIZE,
        start.y - cosf(frog->aim_angle * DEG2RAD) * AIM_SIZE
    };

    DrawLineEx(
        start,
        end,
        AIM_THICKNESS,
        RED
    );
}