#include "Explosion.h"

Explosion::Explosion()
{
    frameHeight = 0;
    frameWidth = 0;
    frame =0;
}

Explosion::~Explosion()
{
    //dtor
}
bool Explosion::loadImg(std::string path,SDL_Renderer* screen ){
    bool ret =Object::loadImg(path,screen);
    if (ret ){
        frameHeight = rect.h;
        frameWidth = rect.w/12;
    }
    return ret;
}

void Explosion::setClip(){
    if (frameWidth > 0 && frameHeight >0){
        for (int i =0;i<12;i++){
            frame_clip[i].x = i*frameWidth;
            frame_clip[i].y = 0;
            frame_clip[i].w = frameWidth;
            frame_clip[i].h = frameHeight;
        }

    }
}

void Explosion::show(SDL_Renderer* screen ){
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect render_quad = {rect.x,rect.y,frameWidth,frameHeight};
    if (current_clip!= NULL){
        render_quad.w = current_clip->w;
        render_quad.h = current_clip->h;
    }
    SDL_RenderCopy(screen,p_object,current_clip,&render_quad);

}
