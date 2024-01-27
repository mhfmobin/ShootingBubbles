#ifndef BOUNCINGBALLS_FRONT_END_H
#define BOUNCINGBALLS_FRONT_END_H

//menu and other thing
void DrawMenu(SDL_Renderer* renderer);
void Draw(SDL_Renderer* renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h);
void Modes(SDL_Renderer* renderer);
void Levels(SDL_Renderer* renderer);
void Setting(SDL_Renderer* renderer);
void PlayMusic(Mix_Chunk* music,int volume,int repeat,bool can_play);
//game
int ColorPickerR(int color);
int ColorPickerG(int color);
int ColorPickerB(int color);
void ShowBalls(SDL_Renderer* renderer);
void DrawABall(SDL_Renderer* renderer,int x,int y,int color);
void ShowCanon(SDL_Renderer* renderer);
void ShowLevel(SDL_Renderer* renderer,int level_id);



//_______________________functions______________________________

void DrawMenu(SDL_Renderer* renderer){
    Draw(renderer,menu_img,menu_rect,0,0,WIDTH,HEIGHT);
}

void Draw(SDL_Renderer* renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h)
{
    img_rect.x = x;
    img_rect.y = y;
    img_rect.w = w;
    img_rect.h = h;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, m_img, NULL, &img_rect);
    SDL_RenderPresent(renderer);
}

void Modes(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mouse_x = e->button.x;
    mouse_y = e->button.y;
    Draw(renderer,modes_img,modes_rect,0,0,WIDTH,HEIGHT);
    if( e -> type == SDL_QUIT){
        modes=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        modes = false;
    }
    if((mouse_x>160)&&(mouse_x<313)&&(mouse_y>180)&&(mouse_y<223) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        levels=true;
        modes=false;
        PlayMusic(btn_sd,25,0,btn_sd_c);
    }
}

void Levels(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mouse_x = e->button.x;
    mouse_y = e->button.y;
    Draw(renderer,levels_img,levels_rect,0,0,WIDTH,HEIGHT);
    if( e -> type == SDL_QUIT){
        levels=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        levels = false;
    }
    if((mouse_x>24)&&(mouse_x<205)&&(mouse_y>252)&&(mouse_y<297) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(1);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_1=true;
    }
}

void Setting(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mouse_x = e->button.x;
    mouse_y = e->button.y;
    Draw(renderer,setting_img,setting_rect,0,0,WIDTH,HEIGHT);
    if( e -> type == SDL_QUIT){
        setting=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        setting = false;
    }
    if((mouse_x>24)&&(mouse_x<205)&&(mouse_y>252)&&(mouse_y<297) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
    }
}

void PlayMusic(Mix_Chunk* music,int volume,int repeat,bool can_play){
    if(can_play){
        Mix_VolumeChunk(music, volume);
        Mix_PlayChannel(-1, music, repeat);
    }
}

//GAME
int ColorPickerR(int color){
    int Rc;
    if(color==2) Rc=255;//red
    else if(color==3) Rc = 255;//yellow
    else if(color==5) Rc = 18;//green
    else if(color==7) Rc = 0;//blue
    else if(color==11) Rc = 171;//purple
    else if(color==13) Rc = 0;//black
    return Rc;
}
int ColorPickerG(int color){
    int Gc;
    if(color==2) Gc=14;//red
    else if(color==3) Gc = 231;//yellow
    else if(color==5) Gc = 240;//green
    else if(color==7) Gc = 189;//blue
    else if(color==11) Gc = 69;//purple
    else if(color==13) Gc = 0;//black
    return Gc;
}
int ColorPickerB(int color){
    int Bc;
    if(color==2) Bc=14;//red
    else if(color==3) Bc = 0;//yellow
    else if(color==5) Bc = 0;//green
    else if(color==7) Bc = 255;//blue
    else if(color==11) Bc = 255;//purple
    else if(color==13) Bc = 0;//black
    return Bc;
}

void ShowBalls(SDL_Renderer* renderer){
    for (int i = 0; i < data.size(); i++) {
        int limit = (i%2) ? MAX_BALLS - 1 : MAX_BALLS ;
        for (int j = 0; j < limit; ++j) {
            DrawABall(renderer,data[i][j].x,data[i][j].y + added_y,data[i][j].color);
        }
    }

}

void DrawABall(SDL_Renderer* renderer,int x,int y,int color){
    int Rc = ColorPickerR(color);
    int Gc = ColorPickerG(color);
    int Bc = ColorPickerB(color);
    filledCircleRGBA(renderer, x, y, R, Rc,Gc,Bc,255);
}
void ShowLevel(SDL_Renderer* renderer,int level_id){
    SDL_RenderClear(renderer);
    SDL_PollEvent(e);
    if( e -> type == SDL_QUIT){
        run=false;
        show_level_1=false;
        show_level_2=false;
        show_level_3=false;
        show_level_4=false;
        show_level_5=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        show_level_1=false;
        show_level_2=false;
        show_level_3=false;
        show_level_4=false;
        show_level_5=false;
    }

    ShowBalls(renderer);
    added_y += Vy;
    lineRGBA(renderer,0,BASE_Y,WIDTH,BASE_Y,185,0,0,255);
    SDL_RenderPresent(renderer);
    //SDL_Delay(0);
}

#endif //BOUNCINGBALLS_FRONT_END_H
