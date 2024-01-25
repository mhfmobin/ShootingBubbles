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

    //starting
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(0);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_Window* window = SDL_CreateWindow("Bouncing Ball",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    // load images 
    modes_img = IMG_LoadTexture(renderer, "../images/modes.png");
    menu_img = IMG_LoadTexture(renderer, "../images/menu-back.png");
    levels_img = IMG_LoadTexture(renderer, "../images/levels.png");
    setting_img = IMG_LoadTexture(renderer, "../images/setting.png");
    // load sounds
    menu1_sd = Mix_LoadWAV("../sounds/menu1.wav");
    btn_sd = Mix_LoadWAV("../sounds/button.wav");


    PlayMusic(menu1_sd,25,-1,menu_sd);


    e->type = 0;
    SDL_PollEvent(e);

    bool map_bool=false;
    while (true) {
        SDL_PollEvent(e);
        SDL_ShowCursor(SDL_ENABLE);
        mouse_x = e->button.x;
        mouse_y = e->button.y;
        DrawMenu(renderer);

        if( e -> type == SDL_QUIT){
            break;
        }

        if((mouse_x>12)&&(mouse_x<85)&&(mouse_y>12)&&(mouse_y<85) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            break;
        }
        if((mouse_x>294)&&(mouse_x<470)&&(mouse_y>36)&&(mouse_y<88) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            modes=true;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            Modes(renderer);
        }
        if((mouse_x>292)&&(mouse_x<470)&&(mouse_y>145)&&(mouse_y<188) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
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

//        map_menu = 0;
//        setting = 0;
//
//        if((mouse_x>70)&&(mouse_x<235)&&(mouse_y>580)&&(mouse_y<800) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
//        {
//            e ->type = 0 ;
//            exite = 1;
//        }
//
//        if((mouse_x>540)&&(mouse_x<740)&&(mouse_y>400)&&(mouse_y<505) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
//        {
//            map_menu = 1;
//            draw(renderer, BG_img, BG_rect, 0, 0, 1280, 800);
//            draw(renderer, map1wood_img, map1wood_rect, 300, 150, 250, 200);
//            draw(renderer, map2wood_img, map2wood_rect, 730, 150, 250, 200);
//            draw(renderer, map3wood_img, map3wood_rect, 300, 450, 250, 200);
//            draw(renderer, map4wood_img, map4wood_rect, 730, 450, 250, 200);
//            SDL_RenderPresent(renderer);
//        }
//
//        if((mouse_x>1045)&&(mouse_x<1210)&&(mouse_y>580)&&(mouse_y<800) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
//        {
//            setting = 1;
//            menu(renderer);
//            draw(renderer, settingwood_img, settingwood_rect, 1045, 450, 150, 150);
//            draw(renderer, settingwood_img, settingwood_rect, 900, 450, 150, 150);
//            draw(renderer, settingwood_img, settingwood_rect, 900, 570, 150, 165);
//            draw(renderer, music_img, music_rect, 1085, 490, 70, 70);
//            draw(renderer, sound_img, sound_rect, 945, 490, 70, 70);
//            draw(renderer, help_img, help_rect, 935, 610, 85, 80);
//            SDL_RenderPresent(renderer);
//        }
//        while(map_menu)
//        {
//            menu_map(renderer);
//            exite = 0;
//        }
//
//        while(setting)
//        {
//            setting_menu(renderer, backgroundsound);
//        }

//        if(exite == 1)
//            break;
////               move_ball(renderer, m_img,canon , img_rect, toop);

        e->type = 0;
    }



    SDL_DestroyTexture(menu_img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();


    return 0;
}
