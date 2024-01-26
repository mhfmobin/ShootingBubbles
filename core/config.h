#ifndef BOUNCINGBALLS_CONFIG_H
#define BOUNCINGBALLS_CONFIG_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

/*****************************************************
                    Definitions
*****************************************************/

#define WIDTH 480
#define HEIGHT 720
#define BASE_Y 650 // The line that will be used to check game over
#define START_Y 150 // The line that lowest ball is there when the level is started
#define MAX_BALLS 10 // max balls in row
#define R 24 // ball radius

/*****************************************************
                    Structures
*****************************************************/

struct Ball {
    int color;
    bool is_falling = false;
    float x = 0, y = 0;
};

/*****************************************************
                    Global Variable
*****************************************************/

vector<vector<Ball>> data;
SDL_Event* e = new SDL_Event();
int mouse_x, mouse_y;
bool modes = false;
bool levels = false;
bool menu_sd = true;
bool setting = false;
bool btn_sd_c = true;
bool is_timer_on = false;
bool menu_show = true;
bool show_level_1=false;
int timer = 1000000000;
float yv = 0; // velocity in Y axis
float added_y = 0;
map<string, int> settings;
vector<int> times = {60,60,60,60,60};
vector<int> colors = {2,3,5,7,11,13};
// 2 -> red
// 3 -> yellow
// 5 -> green
// 7 -> blue
// 11 -> purple
// 13 -> black

/*****************************************************
                    File Handlers
*****************************************************/

// ====================== Images =======================

SDL_Texture* menu_img = NULL;
SDL_Rect menu_rect;
SDL_Texture* l_poison_img = NULL;
SDL_Rect l_poison_rect;
SDL_Texture* l_volcano_img = NULL;
SDL_Rect l_volcano_rect;
SDL_Texture* l_desert_img = NULL;
SDL_Rect l_desert_rect;
SDL_Texture* l_shadow_img = NULL;
SDL_Rect l_shadow_rect;
SDL_Texture* l_final_img = NULL;
SDL_Rect l_final_rect;
SDL_Texture* l_timer_img = NULL;
SDL_Rect l_timer_rect;
SDL_Texture* levels_img = NULL;
SDL_Rect levels_rect;
SDL_Texture* modes_img = NULL;
SDL_Rect modes_rect;
SDL_Texture* setting_img = NULL;
SDL_Rect setting_rect;

// ====================== Sounds =======================

Mix_Chunk* menu1_sd;
Mix_Chunk* menu2_sd;
Mix_Chunk* menu3_sd;
Mix_Chunk* btn_sd;
Mix_Chunk* shoot_sd;
Mix_Chunk* pop_sd;
Mix_Chunk* explosion_sd;
Mix_Chunk* timer_sd;
Mix_Chunk* l_poison_sd;
Mix_Chunk* l_shadow_sd;
Mix_Chunk* l_volcano_sd;
Mix_Chunk* l_final_sd;
Mix_Chunk* l_desert_sd;
Mix_Chunk* l_timer_sd;
Mix_Chunk* game_over_sd;
Mix_Chunk* win_sd;


#endif //BOUNCINGBALLS_CONFIG_H
