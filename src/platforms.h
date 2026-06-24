#pragma once

#include <raylib.h>
#include "config.h"
#include "frog.h"

void load_initial_platforms(Rectangle platforms[]);
void draw_platforms(Rectangle platforms[]);
void check_platforms_collision(Frog *frog, Rectangle platforms[]);