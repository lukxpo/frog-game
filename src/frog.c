#include "frog.h"


Frog create_frog(Vector2 spawn_pos)
{
    Frog frog = {
        .position = spawn_pos,
        .velocity = {0, 0},
        .texture = LoadTexture("assets/frog-idle.png"),
        .frame_width = 64,
        .frame_height = 64,
        .current_frame = 0,
        .frame = {
            .x = 0,
            .y = 0,
            .width = FROG_WIDTH,
            .height = FROG_HEIGHT
        },
        .feet = {
            spawn_pos.x + FEET_OFFSET_X,
            spawn_pos.y + FEET_OFFSET_Y,
            FEET_WIDTH,
            FEET_HEIGHT
        },
        .aim_angle = 0.0f,
        .aim_speed = 180.0f,
        .jump_power = 0.0f,
        .is_jumping = true,
        .is_charging = false
    };

    return frog;
}


void update_frog(Frog *frog, float dt)
{
    // ----------------------------- fall -----------------------------
    if (frog->is_jumping)
    {
        frog->velocity.y += GRAVITY * dt;

        frog->position.x += frog->velocity.x * dt;
        frog->position.y += frog->velocity.y * dt;

        frog->feet.x = frog->position.x + FEET_OFFSET_X;
        frog->feet.y = frog->position.y + FEET_OFFSET_Y;
    }

    // ----------------------------- charge -----------------------------
    else
    {
        if (IsKeyPressed(KEY_SPACE) && !frog->is_charging) 
        {
            frog->is_charging = true;
        }
    }

    // ----------------------------- jump -----------------------------
    if (frog->is_charging)
    {
        if (IsKeyReleased(KEY_SPACE))
        {
            float radians = frog->aim_angle * DEG2RAD;

            frog->is_jumping = true;
            frog->is_charging = false;
            frog->velocity.x = sinf(radians) * frog->jump_power;
            frog->velocity.y = -cosf(radians) * frog->jump_power;
            frog->jump_power = 0.0f;
        }

        frog->jump_power += 400 * dt;
        if (frog->jump_power > JUMP_POWER_CAP)
        {
            frog->jump_power = JUMP_POWER_CAP;
        }
    }
}

void draw_frog(const Frog *frog) 
{
    // ----------------------------- draw frog -----------------------------
    DrawTextureRec(
        frog->texture,
        frog->frame,
        frog->position,
        WHITE
    );
}