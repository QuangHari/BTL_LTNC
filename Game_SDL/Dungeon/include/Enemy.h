#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "Object.h"

#define FRAME_ENEMY 8
#define ENEMY_MAX_SPEED 10
#define ENEMY_GRAVITY 0.8

class Enemy:public Object
{
    public:
        Enemy();
        ~Enemy();

        void setXVal(const float& xVal){x_val = xVal;}
        void setYVal(const float& yVal){y_val = yVal;}
        void setXPos(const float& xPos){x_pos = xPos;}
        void setYPos(const float& yPos){y_pos = yPos;}
        float getXPos(){return x_pos;}
        float getYPos(){return y_pos;};
        void setMapXY(const int& mapX,const int& mapY){map_x=mapX; map_y = mapY;};

        void setClip();
        bool loadImg(std::string path,SDL_Renderer* screen);
        void show(SDL_Renderer* des);
        int getWidthFrame() const {return width_frame;}
        int getHeightFrame() const {return height_frame;}
        void doEnemy(Map& gMap);
        void checkMap(Map& gMap);


    private:

        int map_x;
        int map_y;
        float x_val;
        float y_val;
        float x_pos;
        float y_pos;
        bool on_ground;
        int come_back_time;
        SDL_Rect frame_clip[FRAME_ENEMY];
        int width_frame;
        int height_frame;
        int frame;
};

#endif // ENEMY_H
