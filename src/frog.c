#include "frog.h"


Frog create_frog(Vector2 spawn_pos)
{
    Frog frog = {
        .position = spawn_pos,
        .velocity = {0, 0},
        .texture = LoadTexture("assets/frog-poses.png"),
        .frame_width = FROG_WIDTH,
        .frame_height = FROG_HEIGHT,
        .current_frame = 0,
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

        if (frog->velocity.y > 0)
        {
            frog->current_frame = GOING_DOWN;
        }
    }

    // ----------------------------- charge -----------------------------
    else
    {
        if (IsKeyPressed(KEY_SPACE) && !frog->is_charging) 
        {
            frog->is_charging = true;
            frog->current_frame = CHARGING;
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
            frog->current_frame = GOING_UP;
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
    Rectangle source_rect = {
        frog->current_frame * frog->frame_width,
        0,
        frog->frame_width,
        frog->frame_height
    };

    Rectangle dest_rect = {
        frog->position.x,
        frog->position.y,
        frog->frame_width,
        frog->frame_height
    };

    DrawTexturePro(
        frog->texture,
        source_rect,
        dest_rect,
        (Vector2){0, 0},
        0.0f,
        WHITE
    );
}

