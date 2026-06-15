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
    Rectangle feetBox;
    bool isJumping;
} Frog;

void draw_walls(void);

int main(void)
{
    InitWindow(800, 600, "frog");

    float gravity = 300;

    Frog frog = {
        .position = {SCREEN_WIDTH / 2 - FROG_WIDTH / 2, 100},
        .velocity = {0, 0},
        .texture = LoadTexture("assets/frog-idle.png"),
        .frame = {
            .x = 0,
            .y = 0,
            .width = FROG_WIDTH,
            .height = FROG_HEIGHT
        },
        .isJumping = true
    };

    Rectangle frogFeet = {
        frog.position.x + FEET_OFFSET_X,
        frog.position.y + FEET_OFFSET_Y,
        FEET_WIDTH,
        FEET_HEIGHT
    };

    Rectangle platform = {
        SCREEN_WIDTH / 2 - PLATFORM_WIDTH / 2,
        500,
        PLATFORM_WIDTH,
        PLATFORM_HEIGHT
    };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (frog.isJumping)
        {
            frog.velocity.y += gravity * dt;
            frog.position.y += frog.velocity.y * dt;
            frogFeet.y = frog.position.y + FEET_OFFSET_Y;
        }

        if (CheckCollisionRecs(frogFeet, platform))
        {
            frog.isJumping = false;
            frog.velocity.y = 0;
            frogFeet.y = platform.y - FEET_HEIGHT;
            frog.position.y = frogFeet.y - FEET_OFFSET_Y;
        }

        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        DrawRectangleRec(platform, DARKBLUE);

        DrawTextureRec(
            frog.texture,
            frog.frame,
            frog.position,
            WHITE
        );

        DrawRectangleLines(
            frogFeet.x,
            frogFeet.y,
            frogFeet.width,
            frogFeet.height,
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
        DARKBLUE
    );

    DrawRectangle(
        RIGHT_WALL_X,
        0,
        WALL_WIDTH,
        SCREEN_HEIGHT,
        DARKBLUE
    );
}