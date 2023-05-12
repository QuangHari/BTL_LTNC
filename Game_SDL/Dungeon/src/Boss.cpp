#include "Boss.h"

Boss::Boss()
{
    //ctor
    direction = TURNLEFT;
    skillCD =BOSSCD;
    skillCur = 1;
    numberBullet =NUMBERBULLETMAX;
    step = STEPATTACK;
    onWalk = false;
    timeAnimation = ANIMATION-1;
    hp = HPBOSS;
}

Boss::~Boss()
{
    //dtor
}
bool Boss::loadImg(std::string path,SDL_Renderer* screen){
    bool ret = Object::loadImg(path,screen);
    if (ret ){
        width_frame = rect.w/8;
        height_frame = rect.h;
    }
    return ret;
}
void Boss::setAnimation(){
    if (timeAnimation)
    currentClip =&frame_clip[timeAnimation/2];
    timeAnimation --;
    if (timeAnimation<=0){
        timeAnimation = ANIMATION-1;
    }
}
void Boss::setClip(){
    if (width_frame >0 && height_frame >0){
        for (int i =0;i<8;i++){
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }

    }
}

void Boss::show(SDL_Renderer* des){
    if (come_back_time == 0){
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;
        frame++;
        if (frame >= 4){
            frame =0;
        }
        //setAnimation();
        currentClip =&frame_clip[frame];
        SDL_Rect renderQuad = {rect.x,rect.y,width_frame,rect.h};
        SDL_RenderCopy(des,p_object,currentClip,&renderQuad);


    }
}

void Boss::initBullet(Bullet* p_bullet,SDL_Renderer* screen){

    rect.x = x_pos - map_x;
    rect.y = y_pos - map_y;

    if(bullet_list.size()!= 0){
        dir_bullet = bullet_list.at(0)->getDir();

    }else {
        dir_bullet = direction;
    }
    if (p_bullet!=NULL){
        p_bullet->setBulletType(Bullet::BULLETBOSS);
        p_bullet->loadImgBullet(screen);
        p_bullet->setMove(true);
        p_bullet->setDir(direction);
        if (p_bullet->getDir() == 1){
        p_bullet->setRect(this->rect.x +20,this->rect.y+height_frame*0.4);
        }else {
            p_bullet->setRect(this->rect.x +width_frame-20,this->rect.y+height_frame*0.4);
        }

        p_bullet->setDir(dir_bullet);
        bullet_list.push_back(p_bullet);


    }
}
void Boss::makeBulelt(SDL_Renderer* screen,const int& x_limit,const int&y_limit){

    for (int i=0;i<bullet_list.size();i++){
        Bullet* p_bullet = bullet_list.at(i);
        if (p_bullet != NULL){

            if (p_bullet->getMove()){
                int bullet_distance = rect.x -p_bullet->getRect().x;
                //if (bullet_distance < 1000&& bullet_distance >-1000){

                    p_bullet->handleMove(x_limit,y_limit);
                    p_bullet->render(screen);
                //}

            }else {
                bullet_list.erase(bullet_list.begin()+ i);
                p_bullet = NULL;
            }

        }
    }
}

void Boss::useSKill1(SDL_Renderer* des){

    if (numberBullet >0){
        numberBullet--;
        Bullet* p_bullet = new Bullet();
        initBullet(p_bullet,des);

    }else if (numberBullet == 0){
        skillCur = 2;
        skillCD = BOSSCD;
    }

}


void Boss::useSkill2(const int& x_player){
    numberBullet =NUMBERBULLETMAX;
    if (onWalk ==false ){
        x_player_cur = x_player;
        x_current = rect.x;
        onWalk = true;
    }

    if (step > 0){

        if(x_current >x_player_cur){
            x_pos -= (500/STEPATTACK);

        }else if (x_current <x_player_cur){
            x_pos += (500/STEPATTACK);
        }

        step --;
    }else if (step <=0){

        skillCur =3;
        skillCD = BOSSCD;
    }

}

void Boss::useSkill3(){
    step = STEPATTACK;
    onWalk = false;

    skillCD = BOSSCD;
}

void Boss::attack(const int& x_player,SDL_Renderer* des){

    if (skillCD <= 0){
        switch (skillCur){
        case SKILL1:
            useSKill1(des);

            break;
        case SKILL2:
            useSkill2(x_player);

            break;
        case SKILL3:
            useSkill3();
            skillCur =1;
            break;
        }



    }else {
        if (skillCD>0){
            skillCD --;
        }
    }

}
void Boss::turnAround(const int& x_pos,SDL_Renderer* des){
    if(rect.x>x_pos){
        if(direction ==TURNRIGHT){
            direction = TURNLEFT;
            loadImg("img//bossleft.png",des);
            setClip();


        }

    }else {
        if(direction ==TURNLEFT){
            direction = TURNRIGHT;
            loadImg("img//bossright.png",des);
            setClip();


        }
    }
}



