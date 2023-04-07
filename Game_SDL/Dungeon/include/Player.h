#ifndef PLAYER_H
#define PLAYER_H

#include "CommonFunc.h"
#include "Object.h"



class Player :public Object
{

    public:
        Player();
        ~Player();

        enum walkType {
            WALK_NONE =0,
            WALK_RIGHT = 1,
            WALK_LEFT = 2,
        };
        bool loadImg(std ::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void handleInputAction(SDL_Event events, SDL_Renderer* screen);
        void setClip();
        void Doplayer(Map& map_data);
        void checkMap(Map& map_data);
        void setMapXY(const int map_x_,const int map_y_ ){
            map_x = map_x_;
            map_y=map_y_;
        }
        void centerPlayerOnMap(Map& map_data);
        void updateImage(SDL_Renderer* des);

        float getXPos(){return x_pos;}
    private:
        float x_val;
        float y_val;

        float x_pos;
        float y_pos;
        int width_frame;
        int height_frame;

        SDL_Rect frame_clip[8];
        Input input_type;
        int frame;
        int status;
        bool on_ground;
        int map_x;
        int map_y;

        int come_back_time =0;
};

#endif // PLAYER_H
