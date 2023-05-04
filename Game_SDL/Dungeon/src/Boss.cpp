#include "Boss.h"

Boss::Boss()
{
    //ctor
}

Boss::~Boss()
{
    //dtor
}
bool Boss::loadImg(std::string path,SDL_Renderer* screen){
    bool ret = Object::loadImg(path,screen);
    if (ret ){
        width_frame = rect.w/4;
        height_frame = rect.h;
    }
    return ret;
}

void Boss::setClip(){
    if (width_frame >0 && height_frame >0){
        for (int i =0;i<4;i++){
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

        SDL_Rect* currentClip =&frame_clip[frame];
        SDL_Rect renderQuad = {rect.x,rect.y,width_frame,rect.h};
        SDL_RenderCopy(des,p_object,currentClip,&renderQuad);
    }
}
