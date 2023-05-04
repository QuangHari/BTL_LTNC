#include "Bullet.h"

Bullet::Bullet()
{
    x_val = 0;
    y_val =0;
    is_move =false;
}

Bullet::~Bullet()
{

}

void Bullet::handleMove(const int& x_border,const int& y_border){
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
