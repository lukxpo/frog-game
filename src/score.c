#include "score.h"

ScoreManager load_score_manager(void)
{
    ScoreManager score_manager = {
        .score = 0,
        .scored = false,
        .score_sound = LoadSound("assets/score.wav")
    };

    return score_manager;
}

void unload_score_manager(ScoreManager *score_manager)
{
    UnloadSound(score_manager->score_sound);
}

void draw_score(int score)
{
    DrawText(
        TextFormat("Score: %d", score),
        SCORE_X,
        SCORE_Y,
        SCORE_SIZE,
        DARKGREEN
    );
}
