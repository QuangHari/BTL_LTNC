#ifndef EXPLOSION_H
#define EXPLOSION_H
#include"CommonFunc.h"
#include"Object.h"
#include<iostream>

class Explosion : public Object{
    public:
        Explosion();
        virtual ~Explosion();
        void setClip();
        void setFrame(const int& fr){frame = fr;}
        bool loadImg(std::string path,SDL_Renderer* screen);
        void show(SDL_Renderer* screen);
        int getFrameWidth()const {return frameWidth;}
        int getFrameHeight() const {return frameHeight;}

    private:
        int frameWidth;
        int frameHeight;

        unsigned int frame;
        SDL_Rect frame_clip[12];
};

#endif // EXPLOSION_H
