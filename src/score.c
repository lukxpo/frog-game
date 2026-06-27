#include "score.h"

ScoreManager load_score_manager(void)
{
    ScoreManager score_manager = {
        .score = 0,
        .score_to_add = 0,
        .score_to_add_alpha = 255.0f,
        .score_to_add_speed = SCORE_TO_ADD_TEXT_SPEED,
        .score_to_add_position = (Vector2) {0, 0},
        .alpha_fade_speed = 255.0f,
        .scored = false,
        .scored_timer = 1.0f,
        .score_sound = LoadSound("assets/score.wav")
    };

    return score_manager;
}

void unload_score_manager(ScoreManager *score_manager)
{
    UnloadSound(score_manager->score_sound);
}

void update_score(ScoreManager *score_manager, Vector2 frog_position, float dt)
{
    if (score_manager->scored)
    {
        score_manager->score_to_add_position.y -= score_manager->score_to_add_speed * dt;
        score_manager->score_to_add_alpha -= score_manager->alpha_fade_speed * dt;
        if (score_manager->score_to_add_alpha < 0.0f) 
        {
            score_manager->score_to_add_alpha = 255.0f;
            score_manager->scored = false;
        }
    }
}

void draw_score(const ScoreManager *score_manager)
{
    if (score_manager->scored)
    {
        const char *text = TextFormat("+%dm", score_manager->score_to_add);

        Color textColor = Fade(DARKGREEN, score_manager->score_to_add_alpha / 255.0f);

        DrawTextEx(
            GetFontDefault(),
            text,
            score_manager->score_to_add_position,
            SCORE_TO_ADD_TEXT_SIZE,
            0,
            textColor
        );
    }

    DrawText(
        TextFormat("Ascent: %dm", score_manager->score),
        SCORE_X,
        SCORE_Y,
        SCORE_SIZE,
        DARKGREEN
    );
}
