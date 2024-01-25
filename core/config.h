#include <bits/stdc++.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL2_gfx.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>

#define WIDTH 480
#define HEIGHT 720
#define BASE_Y 650 // The line that will be used to check game over
#define START_Y 150 // The line that lowest ball is there when the level is started
#define MAX_BALLS 10 // max balls in row
#define BALL_RADIUS 10 

struct Ball {
    int color;
    bool is_falling = false;
    float x = 0, y = 0;
};

vector<vector<Ball>> data;