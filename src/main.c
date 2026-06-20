#include <raylib.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define FROG_WIDTH  64
#define FROG_HEIGHT 64

#define FEET_OFFSET_X 22
#define FEET_OFFSET_Y 36
#define FEET_WIDTH    22
#define FEET_HEIGHT    5

#define AIM_THICKNESS 1
#define AIM_SIZE      20
#define AIM_ANGLE_CAP 90.0f

#define WALL_WIDTH   20
#define LEFT_WALL_X  SCREEN_WIDTH / 4
#define RIGHT_WALL_X SCREEN_WIDTH - LEFT_WALL_X - WALL_WIDTH

#define PLATFORM_WIDTH  50
#define PLATFORM_HEIGHT 5

#define JUMP_POWER_CAP 300.0f
#define GRAVITY 200.0f

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
    Rectangle frame;
    Rectangle feet;
    bool is_jumping;
    bool is_charging;
} Frog;

void draw_walls(void);

int main(void)
{
    InitWindow(800, 600, "frog");
    
    float jump_power = 0.0f;
    float aim_angle = 0.0f;
    float aim_speed = 180.0f;

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
        .feet = {
            frog.position.x + FEET_OFFSET_X,
            frog.position.y + FEET_OFFSET_Y,
            FEET_WIDTH,
            FEET_HEIGHT
        },
        .is_jumping = true,
        .is_charging = false
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
            frog.velocity.y += GRAVITY * dt;

            frog.position.x += frog.velocity.x * dt;
            frog.position.y += frog.velocity.y * dt;

            frog.feet.x = frog.position.x + FEET_OFFSET_X;
            frog.feet.y = frog.position.y + FEET_OFFSET_Y;
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
                float radians = aim_angle * DEG2RAD;

                frog.is_jumping = true;
                frog.is_charging = false;
                frog.velocity.x = sinf(radians) * jump_power;
                frog.velocity.y = -cosf(radians) * jump_power;
                jump_power = 0.0f;
            }

            jump_power += 400 * dt;
            if (jump_power > JUMP_POWER_CAP)
            {
                jump_power = JUMP_POWER_CAP;
            }
        }

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

        if (IsKeyDown(KEY_LEFT))
        {
            aim_angle -= aim_speed * dt;
        }

        if (IsKeyDown(KEY_RIGHT))
        {
            aim_angle += aim_speed * dt;
        }

        if (aim_angle < -AIM_ANGLE_CAP)
        {   
            aim_angle = -AIM_ANGLE_CAP;
        }

        if (aim_angle > AIM_ANGLE_CAP)
        {
            aim_angle = AIM_ANGLE_CAP;
        }

        Vector2 start = {
            frog.position.x + FROG_WIDTH / 2,
            frog.position.y + FROG_HEIGHT / 2
        };

        Vector2 end = {
            start.x + sinf(aim_angle * DEG2RAD) * AIM_SIZE,
            start.y - cosf(aim_angle * DEG2RAD) * AIM_SIZE
        };

        BeginDrawing();

        DrawFPS(10, 10);
        
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

        DrawLineEx(
            start,
            end,
            AIM_THICKNESS,
            RED
        );

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

    printf("Exited game loop\n");

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