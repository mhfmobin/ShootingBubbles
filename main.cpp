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
    menu_img = IMG_LoadTexture(renderer, "../images/menu.png");
    modes_img = IMG_LoadTexture(renderer, "../images/modes.png");
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
    login_img = IMG_LoadTexture(renderer, "../images/login.png");
    devil_img = IMG_LoadTexture(renderer, "../images/devil.png");
    beak_img = IMG_LoadTexture(renderer, "../images/beak.png");
    pause_b_img = IMG_LoadTexture(renderer, "../images/pause-B.png");
    resume_b_img = IMG_LoadTexture(renderer, "../images/resume-B.png");
    setting_b_img = IMG_LoadTexture(renderer, "../images/setting-B.png");
    pop_img = IMG_LoadTexture(renderer, "../images/pop.png");




    //load sounds
    //menu1_sd = Mix_LoadWAV("../sounds/menu1.wav");
    btn_sd = Mix_LoadWAV("../sounds/button.wav");
    shoot_sd = Mix_LoadWAV("../sounds/shoot.wav");
    menu1_sd = Mix_LoadMUS("../sounds/menu1.mp3");
    game_over_sd = Mix_LoadWAV("../sounds/game-over.wav");
    win_sd = Mix_LoadWAV("../sounds/win.wav");
    story = Mix_LoadWAV("../sounds/story.wav");
    pop_sd = Mix_LoadWAV("../sounds/pop.wav");




    TTF_Init();
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
    SDL_RenderPresent(renderer);



    TTF_Font* font = TTF_OpenFont("../comicbd.ttf", 24);

    SDL_StartTextInput();

    char inputText[100] = "";
    SDL_Color textColor = {0, 47, 145, 255};
    SDL_Surface* inputSurface = NULL;
    SDL_Texture* inputTexture = NULL;
    SDL_Event e2;

    PlayMusic(story,100,0,1);
    while (login) {

        DrawWithoutPresent(renderer,login_img,login_rect,0,0,WIDTH,HEIGHT);
        stringRGBA(renderer,280,220,"please Press Enter",255,255,255,255);
        while (SDL_PollEvent(&e2) != 0) {

            if (e2.type == SDL_QUIT) {
                login = false;
            } else if (e2.type == SDL_TEXTINPUT) {
                strcat(inputText, e2.text.text);
                SDL_FreeSurface(inputSurface);
                SDL_DestroyTexture(inputTexture);
                inputSurface = TTF_RenderText_Solid(font, inputText, textColor);
                inputTexture = SDL_CreateTextureFromSurface(renderer, inputSurface);
            } else if (e2.type == SDL_KEYDOWN) {
                if (e2.key.keysym.sym == SDLK_RETURN && strlen(inputText) > 0) {
                    name = inputText;
                    inputText[strlen(inputText) - 1] = '\0';
                    SDL_FreeSurface(inputSurface);
                    SDL_DestroyTexture(inputTexture);
                    inputSurface = TTF_RenderText_Solid(font, inputText, textColor);
                    inputTexture = SDL_CreateTextureFromSurface(renderer, inputSurface);
                    login = false;
                    run=true;
                }
            }
        }

        if (inputSurface != NULL && inputTexture != NULL) {
            SDL_Rect inputRect = {45, 155, inputSurface->w, inputSurface->h};
            SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(inputTexture);
    SDL_FreeSurface(inputSurface);
    TTF_CloseFont(font);
    SDL_StopTextInput();
    TTF_Quit();

    Mix_VolumeMusic(30*vol);
    Mix_PlayMusic(menu1_sd,-1);

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

        if((menu_show) && (mouse_x>364)&&(mouse_x<438)&&(mouse_y>620)&&(mouse_y<692) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            run=false;
            break;
        }
        if((menu_show) && (mouse_x>48)&&(mouse_x<423)&&(mouse_y>130)&&(mouse_y<230) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            modes=true;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            Modes(renderer);
        }
        if((menu_show) && (mouse_x>237)&&(mouse_x<413)&&(mouse_y>250)&&(mouse_y<330) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type = 0;
            setting=true;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            Setting(renderer);
        }
        if((menu_show) && (mouse_x>50)&&(mouse_x<228)&&(mouse_y>250)&&(mouse_y<330) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
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
        while(show_level_1 && !is_paused){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,1);
        }
        while(show_level_2 && !is_paused){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,2);
        }
        while(show_level_3 && !is_paused){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,3);
        }
        while(show_level_4 && !is_paused){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,4);
        }
        while(show_level_5 && !is_paused){
            //Mix_VolumeMusic(0);
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,5);
        }
        while(show_level_random && !is_paused){
            SDL_SetRenderDrawColor(renderer,0,0,0,225);
            ShowLevel(renderer,6);
        }
        while(show_timer_level && !is_paused){
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

        if (is_paused){
            DrawWithoutPresent(renderer,resume_b_img,resume_b_rect,420,650-50-10-50-10,45,50);
            DrawWithoutPresent(renderer,setting_b_img,setting_b_rect,420,650-50-10,45,50);
            SDL_PollEvent(e);
            if((mouse_x>420)&&(mouse_x<420+45)&&(mouse_y>650-50-10-50-10)&&(mouse_y<650-50-10-50-10+50) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
                e->type = 0;
                PlayMusic(btn_sd,25,0,btn_sd_c);
                is_paused=false;
            }
            if((mouse_x>420)&&(mouse_x<420+45)&&(mouse_y>650-50-10)&&(mouse_y<650-50-10+50) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
                e->type = 0;
                PlayMusic(btn_sd,25,0,btn_sd_c);
                is_paused=false;
                setting=true;
            }
            if( e -> type == SDL_QUIT){
                e->type = 0;
                is_paused=false;
                show_level_1=false;
                show_level_2=false;
                show_level_3=false;
                show_level_4=false;
                show_level_5=false;
                show_level_random=false;
                show_timer_level=false;
                levels=true;
            }
            SDL_RenderPresent(renderer);
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


