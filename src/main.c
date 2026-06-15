#include <raylib.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define FROG_WIDTH  64
#define FROG_HEIGHT 64

#define FEET_OFFSET_X 22
#define FEET_OFFSET_Y 36
#define FEET_WIDTH    22
#define FEET_HEIGHT    5

#define WALL_WIDTH   20
#define LEFT_WALL_X  SCREEN_WIDTH / 4
#define RIGHT_WALL_X SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH

#define PLATFORM_WIDTH  40
#define PLATFORM_HEIGHT 5

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Rectangle frame;
    bool is_jumping;
    bool is_charging;
} Frog;

void draw_walls(void);

int main(void)
{
    InitWindow(800, 600, "frog");

    const float gravity = 300.0;
    
    float jump_power = 0.0;

    Frog frog = {
        .position = {SCREEN_WIDTH / 2 - FROG_WIDTH / 2, 300},
        .velocity = {0, 0},
        .texture = LoadTexture("assets/frog-idle.png"),
        .frame = {
            .x = 0,
            .y = 0,
            .width = FROG_WIDTH,
            .height = FROG_HEIGHT
        },
        .is_jumping = true,
        .is_charging = false
    };

    Rectangle frog_feet = {
        frog.position.x + FEET_OFFSET_X,
        frog.position.y + FEET_OFFSET_Y,
        FEET_WIDTH,
        FEET_HEIGHT
    };

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

        if (frog.is_jumping)
        {
            frog.velocity.y += gravity * dt;
            frog.position.y += frog.velocity.y * dt;
            frog_feet.y = frog.position.y + FEET_OFFSET_Y;
        }
        else
        {
            if (IsKeyPressed(KEY_SPACE) && !frog.is_charging) 
            {
                frog.is_charging = true;
            }
        }

        if (frog.is_charging)
        {
            if (IsKeyReleased(KEY_SPACE))
            {
                frog.is_jumping = true;
                frog.is_charging = false;
                frog.velocity.y -= jump_power;
                jump_power = 0.0;
            }

            jump_power += 400 * dt;
        }

        for (int i = 0; i < platforms_size; i++)
        {
            if (CheckCollisionRecs(frog_feet, platforms[i]) && frog.velocity.y > 0)
            {
                frog.is_jumping = false;
                frog.velocity.y = 0;
                frog_feet.y = platforms[i].y - FEET_HEIGHT;
                frog.position.y = frog_feet.y - FEET_OFFSET_Y;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < platforms_size; i++)
        {
            DrawRectangleRec(platforms[i], DARKGRAY);
        }

        DrawTextureRec(
            frog.texture,
            frog.frame,
            frog.position,
            WHITE
        );

        DrawRectangleLines(
            frog_feet.x,
            frog_feet.y,
            frog_feet.width,
            frog_feet.height,
            RED
        );

        draw_walls();

        EndDrawing();
    }

    UnloadTexture(frog.texture);

    CloseWindow();

    return 0;
}

void draw_walls(void) {
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