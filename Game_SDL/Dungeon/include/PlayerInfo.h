#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "CommonFunc.h"
#include "Object.h"
class PlayerInfo :public Object
{
    public:
        PlayerInfo();
        ~PlayerInfo();

        void setNum(const int& num){number = num;}
        void addPos(const int& xPos);
        void show(SDL_Renderer* screen);
        void init(SDL_Renderer* screen);
        int getPosListSize(){return pos_list.size();};

        void initCrease();
        void decrease();


    private:
        int number;
        std::vector<int> pos_list;
};

class PlayerBullet : public Object{
public :
    PlayerBullet();
    ~PlayerBullet();

    void init(SDL_Renderer* screen);
    void show(SDL_Renderer* screen);
    void setPos(const int&x, const int& y ){x_pos = x,y_pos= y;}
private :
    int x_pos;
    int y_pos;
};

#endif // PLAYERINFO_H
