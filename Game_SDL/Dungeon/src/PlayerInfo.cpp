#include "PlayerInfo.h"

PlayerInfo::PlayerInfo()
{
    number = 0;
}

PlayerInfo::~PlayerInfo()
{

}

void PlayerInfo::addPos(const int& xp){
    pos_list.push_back(xp);
}
void PlayerInfo::init(SDL_Renderer* screen){
    loadImg("img//_hp.png",screen);
    number = 3;
    if (pos_list.size() >0){
        pos_list.clear();
    }

    addPos(20);
    addPos(60);
    addPos(100);

}

void PlayerInfo::show(SDL_Renderer* screen){
    for (int i=0;i<pos_list.size();i++){
        rect.x = pos_list.at(i);
        rect.y = 0;
        render(screen);

    }

}
void PlayerInfo::decrease(){
    number--;
    pos_list.pop_back();

}
void PlayerInfo::initCrease(){
    number++;
    int last_pos = pos_list.back();
    last_pos +=40;
    pos_list.push_back(last_pos);

}

PlayerBullet::PlayerBullet(){
    x_pos = 0;
    y_pos = 0;
}

PlayerBullet::~PlayerBullet(){

}
void PlayerBullet::init(SDL_Renderer* screen){
    bool ret = loadImg("img//bullet.png",screen);


}

void PlayerBullet::show(SDL_Renderer* screen){
    rect.x = x_pos;
    rect.y= y_pos;
    render(screen);
}


