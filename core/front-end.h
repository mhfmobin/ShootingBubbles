#ifndef BOUNCINGBALLS_FRONT_END_H
#define BOUNCINGBALLS_FRONT_END_H

//menu and other thing
void DrawMenu(SDL_Renderer* renderer);
void Draw(SDL_Renderer* renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h);
void DrawWithoutPresent(SDL_Renderer* renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h);
void Modes(SDL_Renderer* renderer);
void Levels(SDL_Renderer* renderer);
void Setting(SDL_Renderer* renderer);
void PlayMusic(Mix_Chunk* music,int volume,int repeat,bool can_play);
double Distance(double x1,double y1,double x2,double y2);
string CountDown(int s);
//game
void ShowBalls(SDL_Renderer* renderer);
void DrawABall(SDL_Renderer* renderer,double x,double y,int color);
void ShowCannon(SDL_Renderer* renderer,double mouseX, double mouseY);
double MouseAngle(double mouseX, double mouseY);
void ShowLevel(SDL_Renderer* renderer,int level_id);
void DrawShootLine(SDL_Renderer* renderer, double mouseX, double mouseY);
void ShowWin(SDL_Renderer* renderer);
void ShowGameOver(SDL_Renderer* renderer);
void ShowRanking(SDL_Renderer* renderer);



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
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, m_img, NULL, &img_rect);
    SDL_RenderPresent(renderer);
}
void DrawWithoutPresent(SDL_Renderer* renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h)
{
    img_rect.x = x;
    img_rect.y = y;
    img_rect.w = w;
    img_rect.h = h;
    //SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, m_img, NULL, &img_rect);
}
void Modes(SDL_Renderer* renderer){

    shooting_laser = 0;
    bomb_count = 2;
    laser_count = 2;
    show_win = 0;
    show_game_over = 0;
    score = 0;
    shoot = true;
    shooting = false;
    shooting_laser = false;
    is_paused= false;
    is_timer_on = false;
    show_win=false;
    show_game_over=false;
    added_y = 0;
    saved = 0;

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
    if((mouse_x>100)&&(mouse_x<370)&&(mouse_y>150)&&(mouse_y<240) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        levels=true;
        modes=false;
    }
    if((mouse_x>100)&&(mouse_x<370)&&(mouse_y>268)&&(mouse_y<350) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        modes=false;
        generateRandomGame(10,1);
        show_timer_level=true;
        timer_level=true;
        is_timer_on=true;
        start_time = time();
    }
    if((mouse_x>100)&&(mouse_x<370)&&(mouse_y>400)&&(mouse_y<480) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        modes=false;
        generateRandomGame(10,1);
        show_level_random=true;
    }
    if((mouse_x>100)&&(mouse_x<370)&&(mouse_y>530)&&(mouse_y<610) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        modes=false;
        generateRandomGame(100);
        st = time() % 100;
        show_level_infinity=true;
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
    if((mouse_x>110)&&(mouse_x<380)&&(mouse_y>130)&&(mouse_y<220) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(1);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_1=true;
    }
    if((mouse_x>110)&&(mouse_x<380)&&(mouse_y>250)&&(mouse_y<335) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(2);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_2=true;
    }
    if((mouse_x>110)&&(mouse_x<380)&&(mouse_y>360)&&(mouse_y<450) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(3);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_3=true;
    }
    if((mouse_x>110)&&(mouse_x<380)&&(mouse_y>485)&&(mouse_y<570) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(4);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_4=true;
    }
    if((mouse_x>110)&&(mouse_x<380)&&(mouse_y>610)&&(mouse_y<700) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        data = {};
        loadLevel(5);
        added_y=0;
        levels = false;
        menu_show = false;
        SDL_RenderClear(renderer);
        show_level_5=true;
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
    if((mouse_x>224)&&(mouse_x<274)&&(mouse_y>157)&&(mouse_y<222) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        music_play=false;
        Mix_VolumeMusic(0);
    }
    if((mouse_x>311+10)&&(mouse_x<393+10)&&(mouse_y>155)&&(mouse_y<224) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        music_play=true;
        Mix_VolumeMusic(25);
    }
    if((mouse_x>211+10)&&(mouse_x<262+10)&&(mouse_y>352)&&(mouse_y<419) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        sound_play=false;
    }
    if((mouse_x>323+10)&&(mouse_x<395+10)&&(mouse_y>352)&&(mouse_y<419) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        sound_play=true;
    }
    if((mouse_x>48+10)&&(mouse_x<90+10)&&(mouse_y>260)&&(mouse_y<305) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1/4;
    }
    if((mouse_x>125+10)&&(mouse_x<170+10)&&(mouse_y>260)&&(mouse_y<305) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1/2;
    }
    if((mouse_x>205+10)&&(mouse_x<245+10)&&(mouse_y>260)&&(mouse_y<305) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1;
    }
    if((mouse_x>280+10)&&(mouse_x<320+10)&&(mouse_y>260)&&(mouse_y<305) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=2;
    }
    if((mouse_x>355+10)&&(mouse_x<395+10)&&(mouse_y>260)&&(mouse_y<305) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=3;
    }
    if((mouse_x>48+10)&&(mouse_x<90+10)&&(mouse_y>450)&&(mouse_y<490) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1/4;
    }
    if((mouse_x>125+10)&&(mouse_x<170+10)&&(mouse_y>450)&&(mouse_y<490) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1/2;
    }
    if((mouse_x>205+10)&&(mouse_x<245+10)&&(mouse_y>450)&&(mouse_y<490) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=1;
    }
    if((mouse_x>280+10)&&(mouse_x<320+10)&&(mouse_y>450)&&(mouse_y<490) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=2;
    }
    if((mouse_x>355+10)&&(mouse_x<395+10)&&(mouse_y>450)&&(mouse_y<490) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        e ->type = 0 ;
        PlayMusic(btn_sd,25,0,btn_sd_c);
        vol=3;
    }
}

void PlayMusic(Mix_Chunk* music,int volume,int repeat,bool can_play){
    if(can_play){
        Mix_VolumeChunk(music, volume*vol);
        Mix_PlayChannel(-1, music, repeat);
    }
    else{
        Mix_VolumeChunk(music, 0);
        Mix_PlayChannel(-1, music, repeat);
    }
}

//GAME

void ShowBalls(SDL_Renderer* renderer){
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (data[i][j].color){
                DrawABall(renderer,data[i][j].x,data[i][j].y + added_y,data[i][j].color);
                DrawWithoutPresent(renderer,beak_img,beak_rect,data[i][j].x-12,data[i][j].y-2 + added_y,24,24);
            }
        }

    }

    for (int i = 0; i < fallings.size(); i++) {
        srand(time(NULL));

        DrawABall(renderer,fallings[i].x,fallings[i].y,fallings[i].color);
        // DrawWithoutPresent(renderer,beak_img,beak_rect,fallings[i].x-12,fallings[i].y-2,24,24);
        
        fallings[i].y += 5 + rand() % 12;
        if(fallings[i].y >= BASE_Y) {
            fallings.erase(fallings.begin() + i);
        }
    }
    

}

void DrawABall(SDL_Renderer* renderer,double x,double y,int color){
    switch (color) {
        case 2:
            DrawWithoutPresent(renderer,red_ball_img,red_ball_rect,x-24,y-24,48,48);
            break;
        case 3:
            DrawWithoutPresent(renderer,yellow_ball_img,yellow_ball_rect,x-24,y-24,48,48);
            break;
        case 5:
            DrawWithoutPresent(renderer,green_ball_img,green_ball_rect,x-24,y-24,48,48);
            break;
        case 7:
            DrawWithoutPresent(renderer,blue_ball_img,blue_ball_rect,x-24,y-24,48,48);
            break;
        case 11:
            DrawWithoutPresent(renderer,purple_ball_img,purple_ball_rect,x-24,y-24,48,48);
            break;
        case 13:
            DrawWithoutPresent(renderer,black_ball_img,black_ball_rect,x-24,y-24,48,48);
            break;
        case 17:
            DrawWithoutPresent(renderer,bomb_img,bomb_rect,x-24,y-24,48,48);
            break;
        case 19:
            DrawWithoutPresent(renderer,laser_img,laser_rect,x-24,y-24,48,48);
            break;
    }
}
void ShowLevel(SDL_Renderer* renderer,int level_id){
    SDL_RenderClear(renderer);
    if(SDL_PollEvent(e)) {
        if (e->type == SDL_QUIT) {
            run = false;
            show_level_1 = false;
            show_level_2 = false;
            show_level_3 = false;
            show_level_4 = false;
            show_level_5 = false;
            show_level_random = false;
        }
        if ((e->key.keysym.sym == SDLK_ESCAPE && e->type == SDL_KEYDOWN)) {
            e->type = 0;
            run = false;
            show_level_1 = false;
            show_level_2 = false;
            show_level_3 = false;
            show_level_4 = false;
            show_level_5 = false;
            show_level_random = false;
        }
        if((e->key.keysym.sym == SDLK_SPACE && e ->type == SDL_KEYDOWN)){
            swap(c1,c2);
        }
        if((mouse_x>420)&&(mouse_x<420+45)&&(mouse_y>650)&&(mouse_y<650+50) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e ->type = 0 ;
            PlayMusic(btn_sd,25,0,btn_sd_c);
            is_paused=true;
        }
        if((e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
            e->type=0;
            PlayMusic(shoot_sd,70,0,sound_play);
            shooting=true;
            SDL_GetMouseState(&mouse_x,&mouse_y);
            swap(c1,c2);
            c2 = cannonBall();
            dx = ((float)mouse_x-(WIDTH/2))/200;
            dy = ((float)mouse_y-(BASE_Y+80))/200;
        }
        if((e->key.keysym.sym == SDLK_b && e ->type == SDL_KEYDOWN)){
            c2=17;
        }
        if((e->key.keysym.sym == SDLK_l && e ->type == SDL_KEYDOWN)){
            shooting_laser=true;
            c2=19;
        }


    }

    switch (level_id) {
        case 1:
            DrawWithoutPresent(renderer,l_desert_img,l_desert_rect,0,0,WIDTH,HEIGHT);
            //PlayMusic(l_desert_sd,100,-1,1);
            break;
        case 2:
            DrawWithoutPresent(renderer,l_volcano_img,l_volcano_rect,0,0,WIDTH,HEIGHT);
            break;
        case 3:
            DrawWithoutPresent(renderer,l_poison_img,l_poison_rect,0,0,WIDTH,HEIGHT);
            break;
        case 4:
            DrawWithoutPresent(renderer,l_shadow_img,l_shadow_rect,0,0,WIDTH,HEIGHT);
            break;
        case 5:
            DrawWithoutPresent(renderer,l_final_img,l_final_rect,0,0,WIDTH,HEIGHT);
            break;
        case 6:
            DrawWithoutPresent(renderer,l_final_img,l_final_rect,0,0,WIDTH,HEIGHT);
            break;
        case 7:
            DrawWithoutPresent(renderer,l_timer_img,l_timer_rect,0,0,WIDTH,HEIGHT);
            break;

    }

    ShowBalls(renderer);
    added_y += Vy;
    DrawWithoutPresent(renderer,bottom_img,bottom_rect,0,BASE_Y+25,WIDTH,100);
    SDL_GetMouseState(&mouse_x,&mouse_y);
    // double angle = 180-( MouseAngle( mouse_x, mouse_y ) * 180 / M_PI );
    if(shoot){
        c1=cannonBall();
        c2=cannonBall();
        shoot=false;
    }

    switch (c2) {
        case 2:
            DrawWithoutPresent(renderer,red_ball_img,red_ball_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 3:
            DrawWithoutPresent(renderer,yellow_ball_img,yellow_ball_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 5:
            DrawWithoutPresent(renderer,green_ball_img,green_ball_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 7:
            DrawWithoutPresent(renderer,blue_ball_img,blue_ball_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 11:
            DrawWithoutPresent(renderer,purple_ball_img,purple_ball_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 17:
            DrawWithoutPresent(renderer,bomb_img,bomb_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
        case 19:
            DrawWithoutPresent(renderer,laser_img,laser_rect,WIDTH/2-24,BASE_Y+80-24,48,48);
            break;
    }
    switch (c1) {
        case 2:
            DrawWithoutPresent(renderer,red_ball_img,red_ball_rect,150,BASE_Y+100-24,36,36);
            break;
        case 3:
            DrawWithoutPresent(renderer,yellow_ball_img,yellow_ball_rect,150,BASE_Y+100-24,36,36);
            break;
        case 5:
            DrawWithoutPresent(renderer,green_ball_img,green_ball_rect,150,BASE_Y+100-24,36,36);
            break;
        case 7:
            DrawWithoutPresent(renderer,blue_ball_img,blue_ball_rect,150,BASE_Y+100-24,36,36);
            break;
        case 11:
            DrawWithoutPresent(renderer,purple_ball_img,purple_ball_rect,150,BASE_Y+100-24,36,36);
            break;
        case 17:
            DrawWithoutPresent(renderer,bomb_img,bomb_rect,150,BASE_Y+100-24,36,36);
            break;
        case 19:
            DrawWithoutPresent(renderer,laser_img,laser_rect,150,BASE_Y+100-24,36,36);
            break;
    }
    shooted_ball.color = c1;
    if(shooting){
        if (shooting_laser) {
            laserEffect();
            shooted_laser.x+=dx;
            shooted_laser.y+=dy;
            DrawABall(renderer,shooted_laser.x,shooted_laser.y,shooted_laser.color);
        } else {
            if(shooted_ball.x>=WIDTH){
                while (shooted_ball.x>=WIDTH) {
                    shooted_ball.x-=2;
                }
                dx=-dx;
                PlayMusic(wall_sd,70,0,sound_play);
                cout<<"rast";
            } else if (shooted_ball.x<=0) {
                dx=-dx;
                PlayMusic(wall_sd,70,0,sound_play);
                cout<<"chap";
                while (shooted_ball.x<=0) {
                    shooted_ball.x+=2;
                }
            }


            shooted_ball.x+=dx;
            shooted_ball.y+=dy;
            DrawABall(renderer,shooted_ball.x,shooted_ball.y,shooted_ball.color);
            shooting = !ballCollision();
        }
        
    } else {
        shooted_ball = {0, 0, 0,  WIDTH/2, BASE_Y+80};
    }
    DrawShootLine(renderer,mouse_x,mouse_y);
    DrawWithoutPresent(renderer,devil_img,devil_rect,WIDTH/2-24,BASE_Y+80-24 ,48,48);
    ShowCannon(renderer,mouse_x,mouse_y);
    stringRGBA(renderer,20,720-30, name.c_str(),255,255,255,255);
    stringRGBA(renderer,20,720-20,("Score = "+to_string(score)).c_str(),255,255,255,255);
    if(timer_level){
        tim = CountDown(75);
        stringRGBA(renderer,480-155,720-30, tim.c_str(),255,255,255,255);
        if(tim == "time = 00:00") timer_level=false;
    }
    DrawWithoutPresent(renderer,devil_img,devil_rect,150,BASE_Y+100-24 ,36,36);
    DrawWithoutPresent(renderer,pause_b_img,pause_b_rect,420,650,45,50);
    if(show_level_infinity){
        int tmp_time = time()%100;
        if(tmp_time == st) generateRandomGame(100,0);
    }
    if(isGameOver()){
        if (!saved) {
            saveScore();
            saved = true;
        }
        PlayMusic(game_over_sd,25,0,sound_play);
        data = {};
        show_level_1=false;
        show_level_2=false;
        show_level_3=false;
        show_level_4=false;
        show_level_5=false;
        show_level_random=false;
        show_timer_level=false;
        show_game_over=true;
    } else if(isWinner()){
        if (!saved) {
            saveScore();
            saved = true;
        }
        PlayMusic(win_sd,50,0,sound_play);
        data.clear();
        show_level_1=false;
        show_level_2=false;
        show_level_3=false;
        show_level_4=false;
        show_level_5=false;
        show_level_random=false;
        show_timer_level=false;
        show_win=true;
    }
    SDL_RenderPresent(renderer);
    //SDL_Delay(0.1);
}

void ShowCannon(SDL_Renderer* renderer,double mouseX, double mouseY){

    double angle = 180-( MouseAngle( mouseX, mouseY ) * 180 / M_PI );
    SDL_RenderCopyEx(renderer, cannon_img, NULL, &cannon_rect, angle, &center_cannon, SDL_FLIP_NONE);
}
double MouseAngle(double mouseX, double mouseY){
    if (mouseX >= (WIDTH/2 - 3) && mouseX <= (WIDTH/2 + 3))
        return M_PI;
    double t= atan((mouseY-(BASE_Y+50))/(mouseX-WIDTH/2));
    if (mouseX-WIDTH/2>0) {
        t = M_PI / 2 - t;
    } else if (mouseX-WIDTH/2<0) {
        t = -M_PI / 2 - t;
    }

    return t;
}

void DrawShootLine(SDL_Renderer* renderer, double mouseX, double mouseY) {
    float dx1 = mouseX - xl;
    float dy1 = mouseY - yl;
    float slope;
    float x2,y2;

    if (abs(dx1) <= 3) {
        aalineRGBA(renderer,xl,yl,xl,0,142,55,200,255);
        return;
    }
    slope=dy1/dx1;
    // else if(dx1==0) aalineRGBA(renderer,xl,yl,xl,0,142,55,200,255);
    if (slope<0) {
        x2 = WIDTH;
        y2 = slope*(WIDTH-xl)+yl;
        if(y2<0){
            y2 = 0;
            x2 = -yl/slope + xl;
        }
        aalineRGBA(renderer,xl,yl,x2,y2,142,55,200,255);
        x2 = -WIDTH;
        y2 = -slope*(-WIDTH-WIDTH)+slope*(WIDTH-xl)+yl;
        if(y2<0){
            y2=0;
            x2= WIDTH + (WIDTH-xl) + yl/slope;
        }
        aalineRGBA(renderer,WIDTH,slope*(WIDTH-xl)+yl,x2,y2,142,55,200,255);
    } else if (slope>0) {
        x2 = 0;
        y2 = slope*(0-xl)+yl;
        if(y2<0){
            y2 = 0;
            x2 = -yl/slope + xl;;
        }
        aalineRGBA(renderer,xl,yl,0,slope*(0-xl)+yl,142,55,200,255);
        x2 = WIDTH;
        y2 = -slope*(WIDTH-0)+slope*(0-xl)+yl;
        if(y2<0){
            y2 = 0;
            x2 = yl/slope - xl;
        }
        aalineRGBA(renderer,0,slope*(0-xl)+yl,x2,y2,142,55,200,255);
    }

}

void ShowWin(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mouse_x = e->button.x;
    mouse_y = e->button.y;
    Draw(renderer,win_img,win_rect,0,0,WIDTH,HEIGHT);

    stringRGBA(renderer,60,20,("Score = "+to_string(score)).c_str(),255,255,255,255);

    if( e -> type == SDL_QUIT){
        show_win=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        show_win=false;
    }
    if((mouse_x>180)&&(mouse_x<270)&&(mouse_y>545)&&(mouse_y<635) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        levels=true;
        show_win=false;
    }
}
void ShowGameOver(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mouse_x = e->button.x;
    mouse_y = e->button.y;
    Draw(renderer,go_img,win_rect,0,0,WIDTH,HEIGHT);


    if( e -> type == SDL_QUIT){
        show_game_over=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        show_game_over=false;
    }
    if((mouse_x>190)&&(mouse_x<280)&&(mouse_y>545)&&(mouse_y<635) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        PlayMusic(btn_sd,25,0,btn_sd_c);
        modes=true;
        show_game_over=false;
    }
}
double Distance(double x1,double y1,double x2,double y2){
    double d=0;
    d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return d;
}

string CountDown(int s) {
    auto now_s = time();
    auto end_s = start_time + s;
    auto remaining_s = end_s - now_s;
    auto minutes = remaining_s / 60;
    auto seconds = remaining_s % 60;
    ostringstream oss;
    oss << setw(2) << setfill('0') << minutes << ":"<< setw(2) << setfill('0') << seconds;
    return "time = "+oss.str();
}


void ShowPoping(double x,double y){
    PlayMusic(pop_sd,50,0,sound_play);
    Draw(renderer,pop_img,pop_rect,x-24,y-24,48,48);
    SDL_Delay(10);
}

void ShowFalling(double x,double y,int color){
    double px=x,py=y;
    while (py<=BASE_Y){
        py+=10;
        DrawABall(renderer,px,py,color);
        SDL_RenderPresent(renderer);
    }
}
void ShowRanking(SDL_Renderer* renderer){
    SDL_PollEvent(e);
    if( e -> type == SDL_QUIT){
        ranking_show=false;
    }
    if((e->key.keysym.sym == SDLK_ESCAPE && e ->type == SDL_KEYDOWN) )
    {
        e ->type = 0 ;
        ranking_show = false;
    }
    Draw(renderer,ranking_img,ranking_rect,0,0,WIDTH,HEIGHT);
    scores.clear();
    scores = sortedScores();
    int i = 0;
    for (const auto& s : scores) {
        i++;
        string a= to_string(i)+"- "+s.first+" : "+ to_string(s.second);
        stringRGBA(renderer,20,30+i*15, a.c_str(),255,255,255,255);
    }
}



#endif //BOUNCINGBALLS_FRONT_END_H
