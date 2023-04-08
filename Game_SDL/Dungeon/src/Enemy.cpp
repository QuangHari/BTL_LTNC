#include "Enemy.h"

Enemy::Enemy()
{
    width_frame =0;
    height_frame =0;
    x_val =0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    on_ground =0;
    come_back_time =0;
    frame = 0;
}

Enemy::~Enemy()
{

}

bool Enemy::loadImg(std::string path,SDL_Renderer* screen){
    bool ret = Object::loadImg(path,screen);
    if (ret ){
        width_frame = rect.w/FRAME_ENEMY;
        height_frame = rect.h;
    }
    return ret;
}

void Enemy::setClip(){
    if (width_frame >0 && height_frame >0){
        for (int i =0;i<8;i++){
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }

    }
}

void Enemy::show(SDL_Renderer* des){
    if (come_back_time == 0){
        rect.x = x_pos - map_x;
        rect.y = y_pos - map_y;
        frame++;
        if (frame >= 8){
            frame =0;
        }

        SDL_Rect* currentClip =&frame_clip[frame];
        SDL_Rect renderQuad = {rect.x,rect.y,width_frame,rect.h};
        SDL_RenderCopy(des,p_object,currentClip,&renderQuad);
    }
}
void Enemy::doEnemy(Map& gMap){
    if (come_back_time ==0){
        x_val =0;
        y_val += ENEMY_GRAVITY;
        if (y_val >=ENEMY_MAX_SPEED){
            y_val = ENEMY_MAX_SPEED;
        }
        checkMap(gMap);

    }else if (come_back_time >0){
        come_back_time --;
        if (come_back_time == 0){
            x_val=0;
            y_val = 0;
            if (x_pos >256){
                x_pos -= 256;
            }else {
                x_pos =0;
            }
            y_pos =0;
            come_back_time = 0;
        }
    }
}

void Enemy::checkMap(Map& map_data){
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    int height_min = height_frame <TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame -1)/TILE_SIZE;

    y1 = (y_pos )/TILE_SIZE;
    y1 = (y_pos  + height_min -1 )/TILE_SIZE;

    if (x1 >=0 && x2 <MAX_MAP_X && y1>=0 && y2 <MAX_MAP_Y){
        if (x_val>0){
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2]!= BLANK_TILE){
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame +1;
                x_val =0;

            }
        }else if (x_val < 0){
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1]!= BLANK_TILE){
                x_pos = (x1+1)*TILE_SIZE;
                x_val =0;
            }
        }
    }



    int width_min = width_frame <TILE_SIZE ? width_frame : TILE_SIZE;
    x1 =(x_pos)/TILE_SIZE;
    x2 = (x_pos +width_min)/TILE_SIZE;

    y1 = (y_pos +y_val)/TILE_SIZE;
    y2 = (y_pos +y_val + height_frame -1)/TILE_SIZE;
    if (x1 >=0 && x2 <MAX_MAP_X && y1 >= 0 && y2<MAX_MAP_Y){
        if (y_val >0){
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2]!= BLANK_TILE){
                y_pos = (y2)*TILE_SIZE;
                y_pos -= (height_frame+1);
                y_val = 0;
            }
            on_ground = true;

        }else if (y_val < 0 ){
            if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2]!= BLANK_TILE){
                y_pos = (y1+1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }


    x_pos +=x_val;
    y_pos += y_val;
    if (x_pos <0){
        x_pos =0;
    }else if (x_pos +width_frame >map_data.max_x){
        x_pos = map_data.max_x -width_frame -1;
    }
    if (y_pos >map_data.max_y){
        come_back_time = 60;


    }
}
