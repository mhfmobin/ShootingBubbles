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
#define BASE_Y 600 // The line that will be used to check game over
#define START_Y 150 // The line that lowest ball is there when the level is started
#define MAX_BALLS 10 // max balls in row
#define R 24 // ball radius

/*****************************************************
                    Structures
*****************************************************/

struct Ball {
    int color;
    bool is_falling = false, falling_tmp = false;
    float x = 0, y = 0;
};

/*****************************************************
                    Global Variable
*****************************************************/

vector<vector<Ball>> data;
vector<Ball> fallings;
Ball shooted_ball = {0, 0, 0,  WIDTH/2, BASE_Y+80};
Ball shooted_laser = {19, 0, 0,  WIDTH/2, BASE_Y+80};
int xl=WIDTH/2;
int yl=BASE_Y+75;
int score = 0;
int st = 0;
time_t start_time;
string name="";
string tim;
SDL_Event* e = new SDL_Event();
int mouse_x, mouse_y;
int c1,c2;
int level_row_count = 100;
int bomb_count = 2, laser_count = 2;
double dx=0,dy=0;
double shoot_angle;
bool shoot = true;
bool shooting = false;
bool shooting_laser = false;
bool is_paused= false;
bool run=true;
bool login=true;
bool modes = false;
bool levels = false;
bool menu_sd_c = true;
bool shoot_sd_c = true;
bool btn_sd_c = true;
bool setting = false;
bool is_timer_on = false;
bool menu_show = true;
bool ranking_show=false;
bool show_level_1=false;
bool show_level_2=false;
bool show_level_3=false;
bool show_level_4=false;
bool show_level_5=false;
bool show_level_random=false;
bool timer_level=false;
bool show_timer_level;
bool show_win=false;
bool show_game_over=false;
bool music_play=true;
bool sound_play=true;
bool game_over_viewed = false;
bool win_viewed = false;
double vol=1;
SDL_Point center_cannon;
SDL_Renderer* renderer;
int timer = 1000000000;
float Vy = 0.05; // velocity in Y axis
float added_y = 0;
map<string, int> settings;
unordered_map<string, int> scores;
vector<int> times = {60,60,60,60,60};
vector<int> colors = {2,3,5,7,11,13};
// 2 -> red
// 3 -> yellow
// 5 -> green
// 7 -> blue
// 11 -> purple
// 13 -> black
// 17 -> bomb
// 19 -> laser

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
SDL_Texture* cannon_img = NULL;
SDL_Rect cannon_rect;
SDL_Texture* red_ball_img = NULL;
SDL_Rect red_ball_rect;
SDL_Texture* yellow_ball_img = NULL;
SDL_Rect yellow_ball_rect;
SDL_Texture* green_ball_img = NULL;
SDL_Rect green_ball_rect;
SDL_Texture* blue_ball_img = NULL;
SDL_Rect blue_ball_rect;
SDL_Texture* purple_ball_img = NULL;
SDL_Rect purple_ball_rect;
SDL_Texture* black_ball_img = NULL;
SDL_Rect black_ball_rect;
SDL_Texture* bottom_img = NULL;
SDL_Rect bottom_rect;
SDL_Texture* go_img = NULL;
SDL_Rect go_rect;
SDL_Texture* win_img = NULL;
SDL_Rect win_rect;
SDL_Texture* login_img = NULL;
SDL_Rect login_rect;
SDL_Texture* devil_img = NULL;
SDL_Rect devil_rect;
SDL_Texture* beak_img = NULL;
SDL_Rect beak_rect;
SDL_Texture* pause_b_img = NULL;
SDL_Rect pause_b_rect;
SDL_Texture* setting_b_img = NULL;
SDL_Rect setting_b_rect;
SDL_Texture* resume_b_img = NULL;
SDL_Rect resume_b_rect;
SDL_Texture* pop_img = NULL;
SDL_Rect pop_rect;
SDL_Texture* ranking_img = NULL;
SDL_Rect ranking_rect;

// ====================== Sounds =======================

//Mix_Chunk* menu1_sd;
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
Mix_Chunk* story;
Mix_Chunk* wall_sd;
Mix_Music *test = NULL;
Mix_Music *menu1_sd = NULL;


// ====================== Initialize =======================

void Initialize() {
    center_cannon.x = 45;
    center_cannon.y = 80;
    cannon_rect.x=WIDTH/2-90/2;
    cannon_rect.y=BASE_Y;
    cannon_rect.w=90;
    cannon_rect.h=100;

}


#endif //BOUNCINGBALLS_CONFIG_H