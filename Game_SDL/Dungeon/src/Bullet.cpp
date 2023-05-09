#include "Bullet.h"


#define FREQUENCY  10
#define AMPLITUDE  100
#define SINESPEED 15
Bullet::Bullet()
{
    x_val = 0;
    y_val =0;
    is_move =false;
    bullet_type = BULLETGUN;
}

Bullet::~Bullet()
{

}
void Bullet::loadImgBullet(SDL_Renderer* des){
    if (bullet_type == BULLETGUN){


    }else if (bullet_type == BULLETBOSS){
        loadImg("img//_bullet.png",des);

    }
}
void Bullet::handleMove(const int& x_border,const int& y_border){
    if (bullet_type == BULLETGUN){
        switch (direction){
        case DIR_RIGHT:
            rect.x +=x_val;
            if (rect.x >x_border){
                is_move = false;
            }
            break;
        case DIR_LEFT:
            rect.x -= x_val;
            if(rect.x <0){
                is_move =false;
            }
            break;
        case DIR_UP:
            rect.y -= y_val;
            if (rect.y <0){
                is_move = false;
            }
            break;
        case DIR_UP_LEFT:
            rect.x -= x_val;
            if(rect.x <0){
                is_move =false;
            }
            rect.y -= y_val;
            if (rect.y <0){
                is_move = false;
            }
            break;
        case DIR_UP_RIGHT:
            rect.x +=x_val;
            if (rect.x >x_border){
                is_move = false;
            }
            rect.y -= y_val;
            if (rect.y <0){
                is_move = false;
            }
            break;
        case DIR_DOWN:
            rect.y += y_val;
            if (rect.y >y_border){
                is_move = false;
            }
            break;
        case DIR_DOWN_RIGHT:
            rect.x +=x_val;
            if (rect.x >x_border){
                is_move = false;
            }
            rect.y += y_val;
            if (rect.y <0){
                is_move = false;
            }
            break;
        case DIR_DOWN_LEFT:
            rect.x -=x_val;
            if (rect.x <0){
                is_move = false;
            }
            rect.y += y_val;
            if (rect.y <0){
                is_move = false;
            }
            break;
        }
    }

    if (bullet_type == BULLETBOSS){
        if (direction == DIR_RIGHT){
            x_val = SINESPEED;

            sin1 = sin1 + M_PI/180;

            rect.y -= y_val;
            y_val = AMPLITUDE*sin(FREQUENCY*sin1);

            rect.x += x_val;

            rect.y += y_val;
            if (rect.x <0 || rect.x >x_border || rect.y <0 && rect.y > y_border){
                is_move =false;
            }
        }else if (direction == DIR_LEFT){
            x_val = SINESPEED;

            sin1 = sin1 + M_PI/180;

            rect.y -= y_val;
            y_val = AMPLITUDE*sin(FREQUENCY*sin1);

            rect.x -= x_val;

            rect.y += y_val;
            if (rect.x <0 || rect.x >x_border || rect.y <0 && rect.y > y_border){
                is_move =false;
            }
        }



    }



}

