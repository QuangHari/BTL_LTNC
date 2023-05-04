#ifndef BOSS_H
#define BOSS_H

#include "CommonFunc.h"
#include "Object.h"
#include "Enemy.h"
class Boss : public Enemy
{
    public:
        Boss();
        ~Boss();

        bool loadImg(std::string path,SDL_Renderer* screen);
        void setClip();
        void show(SDL_Renderer* des);

    private:


};

#endif // BOSS_H
