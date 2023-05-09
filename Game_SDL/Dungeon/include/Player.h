#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "CommonFunc.h"
#include "Object.h"
#include "Bullet.h"


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
        void handleInputAction(SDL_Event events, SDL_Renderer* screen,Mix_Chunk* chunk,Mix_Chunk* chunk2,Mix_Chunk* chunk3,Mix_Chunk* chunk4);
        void setClip();
        void Doplayer(Map& map_data);
        void checkMap(Map& map_data);
        void setMapXY(const int map_x_,const int map_y_ ){
            map_x = map_x_;
            map_y=map_y_;
        }
        void centerPlayerOnMap(Map& map_data);
        void updateImage(SDL_Renderer* des);
        SDL_Rect getRectFrame();

        float getXPos(){return x_pos;}
        float getYPos(){return y_pos;}
        void setBullet(std::vector<Bullet*> list){p_bullet_list = list;}
        std::vector<Bullet*> getBullets(){return p_bullet_list;}
        void handleBullet(SDL_Renderer* des);
        void removeBullet(const int& idx);
        void setComeBack(const int& time){come_back_time=time;};
        int getNumberBullet(){return number_bullet;};
        int getNumberBulletLeft(){return number_bullet_left;};
        void reload(Mix_Chunk* sound);

        void setNumberbullet(int num){number_bullet = num;};
        bool getMusic(){return muteMusic;};
        bool getMuteEffect(){return muteEffect;};

        int getHp(){return hp;};
        void reduceHp(){hp--;};

    private:
        std::vector<Bullet*> p_bullet_list;
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
        int number_bullet;
        int number_bullet_left;
        bool muteMusic ;
        bool muteEffect ;

        int hp;
        Mix_Chunk* fall;

        int come_back_time =0;
        bool meetBoss;
};

#endif // PLAYER_H
