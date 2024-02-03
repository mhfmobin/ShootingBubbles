/*
    Project: Bouncing Balls
    Authors: MH Farahmand ツ, AS Anghaei
    Date: January, 2024
    Description: Bouncing Balls game written in C++
                 Sharif University of Technology EE Basic Programming Final Project

    License: MIT License
*/

#include "core/config.h"
#include "core/back-end.h"
#include "core/front-end.h"


int main(int argc, char* argv[]) {
    loadSettings();
    Initialize();
    //starting
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_Window* window = SDL_CreateWindow("Bouncing Ball",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    //load images
    menu_img = IMG_LoadTexture(renderer, "../images/menu-back.png");
    modes_img = IMG_LoadTexture(renderer, "../images/modes.png");
    menu_img = IMG_LoadTexture(renderer, "../images/menu-back.png");
    levels_img = IMG_LoadTexture(renderer, "../images/levels.png");
    setting_img = IMG_LoadTexture(renderer, "../images/setting.png");
    l_desert_img = IMG_LoadTexture(renderer, "../images/level-desert.png");
    l_volcano_img = IMG_LoadTexture(renderer, "../images/level-volcano.png");
    l_poison_img = IMG_LoadTexture(renderer, "../images/level-poison.png");
    l_shadow_img = IMG_LoadTexture(renderer, "../images/level-shadow.png");
    l_final_img = IMG_LoadTexture(renderer, "../images/level-final.png");
    l_timer_img = IMG_LoadTexture(renderer, "../images/level-time.png");
    cannon_img = IMG_LoadTexture(renderer, "../images/cannon.png");
    red_ball_img = IMG_LoadTexture(renderer, "../images/ball2.png");
    yellow_ball_img = IMG_LoadTexture(renderer, "../images/ball3.png");
    green_ball_img = IMG_LoadTexture(renderer, "../images/ball5.png");
    blue_ball_img = IMG_LoadTexture(renderer, "../images/ball7.png");
    purple_ball_img = IMG_LoadTexture(renderer, "../images/ball11.png");
    black_ball_img = IMG_LoadTexture(renderer, "../images/ball13.png");
    bottom_img = IMG_LoadTexture(renderer, "../images/botrect.png");
    go_img = IMG_LoadTexture(renderer, "../images/game-over.png");
    win_img = IMG_LoadTexture(renderer, "../images/win.png");
    //load sounds
    menu1_sd = Mix_LoadWAV("../sounds/menu1.wav");
    btn_sd = Mix_LoadWAV("../sounds/button.wav");
    shoot_sd = Mix_LoadWAV("../sounds/shoot.wav");
    test = Mix_LoadMUS("../sounds/test.mp3");
    game_over_sd = Mix_LoadWAV("../sounds/game-over.wav");
    win_sd = Mix_LoadWAV("../sounds/win.wav");



    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
    SDL_RenderPresent(renderer);

    Mix_VolumeMusic(10*vol);
    Mix_PlayMusic(test,-1);

    e->type = 0;
    SDL_PollEvent(e);
    while (run){

        SDL_PollEvent(e);
        SDL_ShowCursor(SDL_ENABLE);
        mouse_x = e->button.x;
        mouse_y = e->button.y;
        if(menu_show) DrawMenu(renderer);

        if( e -> type == SDL_QUIT){
            e->type = 0;
            run=false;
            break;
        }
//        if( e -> type == SDL_TEXTINPUT){
//            e->type = 0;
//            name += e->text.text;
//        }
        if(!music_play){
            menu_sd_c=false;
        }
        if(music_play){
            menu_sd_c=true;
        }
        if(!sound_play){
            btn_sd_c=false;
            shoot_sd_c=false;
        }
        if(sound_play){
            btn_sd_c=true;
            shoot_sd_c= true;
        }

        if((menu_show) && (mouse_x>12)&&(mouse_x<85)&&(mouse_y>12)&&(mouse_y<85) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            run=false;
            break;
        }
        if((menu_show) && (mouse_x>294)&&(mouse_x<470)&&(mouse_y>36)&&(mouse_y<88) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            modes=true;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            Modes(renderer);
        }
        if((menu_show) && (mouse_x>292)&&(mouse_x<470)&&(mouse_y>145)&&(mouse_y<188) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            setting=true;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            Setting(renderer);
        }
        while (modes){
            Modes(renderer);
        }
        while(levels){
            Levels(renderer);
        }
        while(setting){
            Setting(renderer);
        }
        while(show_level_1){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,1);
        }
        while(show_level_2){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,2);
        }
        while(show_level_3){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,3);
        }
        while(show_level_4){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,4);
        }
        while(show_level_5){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,5);
        }
        while(show_level_random){
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,6);
        }
        while(show_timer_level){
            if( e -> type == SDL_QUIT){
                e->type = 0;
                show_timer_level=false;
                break;
            }
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,7);
        }
        while(show_game_over){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowGameOver(renderer);
        }
        while(show_win){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowWin(renderer);
        }

        e->type = 0;
    }


    SDL_DestroyTexture(menu_img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}


