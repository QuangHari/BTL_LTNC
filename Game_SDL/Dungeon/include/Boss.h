#ifndef BOSS_H
#define BOSS_H

#include "CommonFunc.h"
#include "Object.h"
#include "Enemy.h"
#include "Bullet.h"

#define ENEMY_GRAVITY 0.1
#define BOSSCD 100
#define NUMBERBULLETMAX 30
#define STEPATTACK 20

class Boss : public Enemy
{
    public:
        Boss();
        ~Boss();

        enum DIRECTION {
            TURNRIGHT = 0,
            TURNLEFT = 1,
        };
        enum BOSSSKILL {
            SKILL1 = 1,
            SKILL2 = 2,
            SKILL3 = 3,
            SKILL4 = 4,
            SKILL5 = 5,
        };

        bool loadImg(std::string path,SDL_Renderer* screen);
        void setClip();
        void show(SDL_Renderer* des);
        void initBullet(Bullet* p_bullet,SDL_Renderer* screen);
        void makeBulelt(SDL_Renderer* screen,const int& x_limit,const int& y_limit);

       std::vector<Bullet*> getBulletList(){return bullet_list;};
       void setBulletList(const std::vector<Bullet*> bullets){bullet_list = bullets;};
       void attack(const int& x_player,SDL_Renderer* des);
       void useSKill1(SDL_Renderer* des);
       void useSkill2(const int& x_player);
       void useSkill3();
       void turnAround(const int& x_player,SDL_Renderer* des);


    private:
        std::vector<Bullet*> bullet_list;
        int direction;
        int skillCur;
        int skillCD;
        int dir_bullet;
        int  numberBullet;
        int step;
        float x_current;
        float x_player_cur;
        bool onWalk;
        bool usingSkill3;




};

#endif // BOSS_H
