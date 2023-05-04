#ifndef TEXTOBJ_H
#define TEXTOBJ_H

#include "CommonFunc.h"
#include "Object.h"
class TextObj
{
    public:
        TextObj();
        ~TextObj();

        enum TextColor{
            RED = 0,
            WHITE = 1,
            BLACK =2,
        };

        bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
        bool loadFromRenderTextBlend(TTF_Font* font, SDL_Renderer* screen);
        void free();
        void setColor(Uint8 red,Uint8 green, Uint8 blue);
        void setColor(int type);

        void renderText(SDL_Renderer* screen,int xp,int yp,SDL_Rect* clip = NULL,
                        double angle = 0.0,SDL_Point* center = NULL,SDL_RendererFlip flip = SDL_FLIP_NONE);


        int getWidth() const {return width;}
        int getHeight() const {return height;}

        void setText(const std::string& text ){str = text;}
        std::string getText() const {return str;};
    private:
        std::string str;
        SDL_Color text_color;
        SDL_Texture* texture;
        int width;
        int height;
};

#endif // TEXTOBJ_H
