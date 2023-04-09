#include "CommonFunc.h"
#include "Object.h"
#include "Map.h"
#include "Player.h"
#include "ImpTimer.h"
#include "Enemy.h"

using namespace std;

Object g_background;

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
    IMG_Quit();
    SDL_Quit();

}
vector<Enemy*> makeEnemyList(){
    vector<Enemy*> list_enemies;
    Enemy* enemy = new Enemy[20];
    for (int i=0;i<20;i++){
        Enemy* p_enemy =(enemy+i);
        if (p_enemy != NULL){
            p_enemy->loadImg("img//zombie_dynamic_left.png",g_screen);
            p_enemy->setClip();
            p_enemy->setXPos(700+i*1000);
            p_enemy->setYPos(250);

            list_enemies.push_back(p_enemy);
        }
    }
    return list_enemies;
}
int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    bool ret = initData();
    if (ret == false ){
        return -1;
    }
    if (loadBackGround() ==false){
        return -1;
    }

    GameMap game_map1;
    game_map1.loadMap("map/map01.dat");
    game_map1.loadTiles(g_screen);


    Player p_player;
    p_player.loadImg("img//soldier_right.png",g_screen);
    p_player.setClip();
    vector<Enemy*> list_enemies = makeEnemyList();

    bool quit =false ;
    while (!quit){

        fps_timer.start();
        while (SDL_PollEvent(&g_event) != 0){
            if (g_event.type == SDL_QUIT){
                quit = true;
            }
            p_player.handleInputAction(g_event,g_screen);

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
        for (int i=0;i<list_enemies.size();i++){
            Enemy* p_enemy = list_enemies.at(i);
            if (p_enemy != NULL){
                p_enemy->setMapXY(map_data.start_x,map_data.start_y);
                p_enemy->doEnemy(map_data);
                p_enemy->show(g_screen);
            }

        }

        SDL_RenderPresent(g_screen);
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
