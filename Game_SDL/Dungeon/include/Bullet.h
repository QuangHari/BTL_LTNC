#ifndef BULLET_H
#define BULLET_H

#include "CommonFunc.h"
#include "Object.h"
#include <cmath>
class Bullet : public Object
{
    public:
        Bullet();
        ~Bullet();
        enum DIRECTION {
            DIR_RIGHT = 0,
            DIR_LEFT = 1,
            DIR_UP = 2,
            DIR_UP_RIGHT = 3,
            DIR_UP_LEFT = 4,
            DIR_DOWN = 5,
            DIR_DOWN_LEFT =6,
            DIR_DOWN_RIGHT = 7,

        };

        enum BULLETTYPE{
            BULLETGUN = 1,
            BULLETBOSS = 2,
        };

        void setXVal(const int& xVal){x_val = xVal;}
        void setYVal(const int& yVal){y_val = yVal;}
        void setMove(const bool& move){is_move =move;}
        bool getMove(){return is_move;}
        void handleMove(const int& x_border,const int& y_border);
        void setDir(const unsigned int& dir){direction =dir;};
        int getDir(){return direction;};
        void setBulletType(const unsigned int& bullettype){bullet_type = bullettype;};

        void loadImgBullet(SDL_Renderer * des);


    private:
        int x_val;
        int y_val;
        bool is_move;
        unsigned int direction;
        unsigned int bullet_type;
        float sin1 = 0;
        float tmp = rect.y;


};

#endif // BULLET_H
