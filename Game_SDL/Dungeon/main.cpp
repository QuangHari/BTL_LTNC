#include "CommonFunc.h"
#include "Object.h"
#include "Map.h"
#include "Player.h"
#include "ImpTimer.h"
#include "Enemy.h"
#include "Explosion.h"
#include "TextObj.h"
#include "PlayerInfo.h"
using namespace std;

Object g_background;

TTF_Font* font= NULL;

bool initData(){
    bool check = true;
    int ret =SDL_Init(SDL_INIT_VIDEO);
    if (ret <0){
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_window = SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL){
        check = false;
    }else {
        g_screen = SDL_CreateRenderer(g_window,-1,SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL){
            check = false;
        }else {
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR ,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            int imgFlag = IMG_INIT_PNG;
            if (!IMG_Init(imgFlag) && imgFlag){
                check = false;
            }
        }
        if (TTF_Init() ==-1){
            check =false;
        }
        font = TTF_OpenFont("font//dlxfont_.ttf",15);
        if (font == NULL){
            check = false;
        }
        if (Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1){
            check = false;
        }
        music = Mix_LoadMUS("sound//Rival.wav");
        if (music == NULL){
            check = false;
        }
        explosion_sound = Mix_LoadWAV("sound//explosion.wav");
        if (explosion_sound == NULL){
            check = false;
        }
        shot_sound = Mix_LoadWAV("sound//shoot.wav");
        if (shot_sound == NULL){
            check = false;
        }
        empty_sound = Mix_LoadWAV("sound//emptygun.wav");
        if (empty_sound == NULL){
            check = false;
        }
        reload_sound = Mix_LoadWAV("sound//reload.wav");
        if (reload_sound == NULL){
            check = false;
        }
        fall_sound = Mix_LoadWAV("sound//hit.wav");
        if (reload_sound == NULL){
            check = false;
        }


    }
    return check;

}
bool loadBackGround(){
    bool ret = g_background.loadImg("img//background.png",g_screen);
    if (ret == false){
        return false;
    }
    return true;
}
void close (){
    g_background.free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

}
vector<Enemy*> makeEnemyList(){
    vector<Enemy*> list_enemies;
    Enemy* dynamic_enemy =new Enemy[26];
    for (int i=0;i<26;i++){
        Enemy* p_enemy =(dynamic_enemy +i);
        if (p_enemy !=NULL){
            p_enemy->loadImg("img//zombie_dynamic_left.png",g_screen);
            p_enemy->setClip();
            p_enemy->setTypeMove(Enemy::MOVE_IN_SPACE);
            p_enemy->setXPos(500 + i*900);
            p_enemy->setYPos(200);
            int pos_1 = p_enemy->getXPos() -60;
            int pos_2 = p_enemy->getXPos() +60;
            p_enemy->setAnimation(pos_1,pos_2);
            p_enemy->setInputLeft(1);
            list_enemies.push_back(p_enemy);

        }
    }

    Enemy* enemy = new Enemy[24];
    for (int i=0;i<24;i++){
        Enemy* p_enemy =(enemy+i);
        if (p_enemy != NULL){
            p_enemy->loadImg("img//zombo_static.png",g_screen);
            p_enemy->setClip();
            p_enemy->setXPos(700+i*1000);
            p_enemy->setYPos(250);
            p_enemy->setTypeMove(Enemy ::STATIC_ENEMY);
            p_enemy->setInputLeft(0);
            list_enemies.push_back(p_enemy);
        }
    }
    return list_enemies;
}
int main(int argc, char* argv[])
{

    bool quit =false ;
    ImpTimer fps_timer;
    bool ret = initData();

    if (ret == false ){
        return -1;
    }
    int ret_menu = SDLCommonFunc::ShowMenu(g_screen,font);
    if (ret_menu == 1) {
        quit = true;
    }
    if (loadBackGround() ==false){
        return -1;
    }
again_label:
    Mix_PlayMusic(music,-1);


    GameMap game_map1;
    game_map1.loadMap("map/map01.dat");
    game_map1.loadTiles(g_screen);
    int frame =0;
    int frameDead = 0;
    int x_pos;
    int y_pos;
    int x_dead;
    int y_dead;


    Player p_player;
    p_player.loadImg("img//soldier_right.png",g_screen);
    p_player.setClip();

    PlayerInfo player_info;
    player_info.init(g_screen);

    PlayerBullet player_bullet;
    player_bullet.init(g_screen);
    player_bullet.setPos(SCREEN_WIDTH*0.4-100,5);


    vector<Enemy*> list_enemies = makeEnemyList();

    Explosion explosion;
    bool tRet = explosion.loadImg("img//explosion.png",g_screen);
    if (!tRet){return -1;}
    explosion.setClip();
    Explosion explosionDead;
    bool tRetD = explosionDead.loadImg("img//explosion.png",g_screen);
    if (!tRetD){return -1;}
    explosionDead.setClip();


    int hp =3;


    TextObj time_game;
    time_game.setColor(TextObj::WHITE);

    TextObj bullet_text;
    bullet_text.setColor(TextObj::WHITE);


    TextObj score_text;
    score_text.setColor(TextObj::WHITE);
    UINT score_val = 0;
    bool isdead = false;


    while (!quit){


        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0){
            if (g_event.type == SDL_QUIT){
                quit = true;
            }
            p_player.handleInputAction(g_event,g_screen,shot_sound,empty_sound,reload_sound,fall_sound);


        }
        if (p_player.getHp()<player_info.getPosListSize()){
               player_info.decrease();
            }
        if (p_player.getMusic() == true){
            Mix_PauseMusic();
        }else {
            Mix_ResumeMusic();
        }

        loadBackGround();
        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.render(g_screen,NULL);
        Map map_data = game_map1.getMap();

        p_player.handleBullet(g_screen);
        p_player.setMapXY(map_data.start_x,map_data.start_y);
        p_player.Doplayer(map_data);
        p_player.Show(g_screen);

        game_map1.setMap(map_data);
        game_map1.drawMap(g_screen );

        player_info.show(g_screen);
        player_bullet.show(g_screen);


        int frame_explosion_width =explosion.getFrameWidth();
        int frame_explosion_height = explosion.getFrameHeight();
        int frame_dead_width = explosion.getFrameWidth();
        int frame_dead_height=explosion.getFrameHeight();
        for (int i=0;i<list_enemies.size();i++){
            Enemy* p_enemy = list_enemies.at(i);
            if (p_enemy != NULL){

                p_enemy->setMapXY(map_data.start_x,map_data.start_y);
                p_enemy->impMoveType(g_screen);

                p_enemy->doEnemy(map_data);
                p_enemy->show(g_screen);

                SDL_Rect rectPlayer =p_player.getRectFrame();
                SDL_Rect rectEnemy =p_enemy->getRectFrame();
                bool bCol1 =SDLCommonFunc::CheckCollision1(rectPlayer,rectEnemy);

                if (bCol1){
                    p_player.reduceHp() ;
                    if(p_player.getHp()>0){
                        if (!p_player.getMuteEffect()){
                            Mix_PlayChannel(-1,explosion_sound,0);
                        }

                        player_info.decrease();
                        player_info.render(g_screen);
                        x_dead = p_player.getRect().x - frame_explosion_width*0.5;
                        y_dead = p_player.getRect().y - frame_explosion_height*0.5;
                        frameDead ++;
                        p_player.setRect(0,0);
                        p_player.setComeBack(60);
                        continue;
                    }
                    //if (p_player.getHp()<=0){
                        //isdead = true;
                        //if (MessageBox(NULL, "GAME OVER!","Info", MB_OK | MB_ICONSTOP) == IDOK){
                            //p_enemy->free();
                            //close();
                            //SDL_Quit();
                            //return 0;
                        //}
                    //}
                }

            }
        }
        if (p_player.getHp()<=0){
            isdead = true;
        }
        if (frameDead >0 && frameDead <12){
            explosionDead.setFrame(frameDead);
            explosionDead.setRect(x_dead,y_dead);
            explosionDead.show(g_screen);
            frameDead ++;
        }
        if (frameDead >=12){
            frameDead = 0;
        }

        vector<Bullet*> bullet_list = p_player.getBullets();
        for (int i=0;i<bullet_list.size();i++){
            Bullet* p_bullet =bullet_list.at(i);
            if (p_bullet != NULL){
                for (int j=0;j < list_enemies.size();j++){
                    Enemy* enemy = list_enemies.at(j);
                    if (enemy != NULL){
                        SDL_Rect eRect;
                        eRect.x = enemy->getRect().x;
                        eRect.y = enemy->getRect().y;
                        eRect.w = enemy->getWidthFrame();
                        eRect.h = enemy->getHeightFrame();

                        SDL_Rect bRect = p_bullet->getRect();

                        bool bCol =SDLCommonFunc::CheckCollision1(bRect,eRect);
                        if (bCol){
                            if (!p_player.getMuteEffect()){
                                Mix_PlayChannel(-1,explosion_sound,0);
                            }
                            frame ++;
                            score_val +=100;
                            //for (int ex = 0;ex<8;ex++){
                            x_pos = p_bullet->getRect().x - frame_explosion_width*0.5;
                            y_pos = p_bullet->getRect().y - frame_explosion_height*0.5;
                            //}
                            p_player.removeBullet(i);
                            enemy->free();
                            list_enemies.erase(list_enemies.begin()+ j);
                            break;
                        }
                    }
                }

            }
        }
        if (frame >0 && frame <12){
            explosion.setFrame(frame);
            explosion.setRect(x_pos,y_pos);
            explosion.show(g_screen);
            frame ++;
        }
        if (frame >=12){
            frame = 0;
        }

        std::string str_time ="Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        if (val_time<=0){
            /*if (MessageBox(NULL, "GAME OVER!","Info", MB_OK | MB_ICONSTOP) == IDOK){
                quit = true;
                break;

            }*/
            isdead = true;
        }else {
            std::string str_val =std::to_string(val_time);
            str_time += str_val;
            time_game.setText(str_time);
            time_game.loadFromRenderText(font,g_screen);
            time_game.renderText(g_screen,SCREEN_WIDTH-200,15);

        }

        std::string str_score =std::to_string(score_val);
        std::string strScore("Score: ");
        strScore += str_score;
        score_text.setText(strScore);
        score_text.loadFromRenderText(font,g_screen);
        score_text.renderText(g_screen,SCREEN_WIDTH*0.6-50,15);

        std::string str_Bullet = std::to_string(p_player.getNumberBullet());
        std::string strBullet("");
        strBullet += str_Bullet;
        strBullet += "/";
        strBullet += std::to_string(p_player.getNumberBulletLeft());
        score_text.setText(strBullet);
        score_text.loadFromRenderText(font,g_screen);
        score_text.renderText(g_screen,SCREEN_WIDTH*0.4-50,15);


        SDL_RenderPresent(g_screen);

        if (isdead == true){

            int deadmenu = SDLCommonFunc::showDeadMenu(g_screen,font);
            if (deadmenu == 1){
                quit = true;
                continue;
            }else if (deadmenu ==2){
                quit = false;
                goto again_label;
            }

        }
        int real_time =fps_timer.getTick();
        int time_one_frame = 1000/FRAME_PER_SECOND;
        int real_fps =1000/real_time;
        cout << real_fps<<endl;
        if (real_time <time_one_frame){
            int delay = time_one_frame - real_time;
            if (delay >0){
                SDL_Delay(delay);
            }
        }
    }
    close();
    return 0;
}
