#ifndef OBJECT_H
#define OBJECT_H

#include "CommonFunc.h"


class Object
{
    public:
        Object();
        ~Object();
        void setRect(const int& x,const int& y ){
            rect.x = x;
            rect.y = y;
        }
        SDL_Rect getRect() const {
            return rect;
        }
        SDL_Texture* getObject() const {
            return p_object;
        }
        virtual bool loadImg(std::string path,SDL_Renderer* screen);
        void render(SDL_Renderer* des,const SDL_Rect* clip =NULL);
        void free();

    protected:
        SDL_Texture* p_object;
        SDL_Rect rect;



};

#endif // OBJECT_H
