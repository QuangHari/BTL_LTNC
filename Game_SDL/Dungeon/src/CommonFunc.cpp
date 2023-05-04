#include "CommonFunc.h"
#include <iostream>


bool SDLCommonFunc::CheckCollision1(const SDL_Rect& object1, const SDL_Rect& object2) {
    int tw = object1.w;
    int th = object1.h;
    int rw = object2.w;
    int rh = object2.h;

    int tx = object1.x;
    int ty= object1.y;
    int rx= object2.x;
    int ry = object2.y;
    rw += object2.x;
    rh += object2.y;

    tw += object1.x;
    th += object1.y;
    return (( rw >tx) &&
            ( rh >ty) &&
            ( tw >rx) &&
            ( th >ry));

}

int SDLCommonFunc::ShowMenu(SDL_Renderer* des, TTF_Font* font){

    int time =0;

    SDL_Event event;
    Object background;

    bool ret = background.loadImg("img//menugame.png",des);
    if (ret == false){
        return 1 ;
    }
    while(1){
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)){
            switch (event.type){

            case SDL_QUIT:
                background.free();

                return 1;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    background.free();

                    return 1;

                }
                if (event.key.keysym.sym == SDLK_RETURN){
                    background.free();

                    return 2;

                }
                break;
            }
        }

        background.render(des,NULL);
        renderBlinkingText(des,font,"Press Enter To Start!",300,400,500);
        SDL_RenderPresent(des);
        if (1000 / 40 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 40 - (SDL_GetTicks() - time));



    }

    return 0;
}
int SDLCommonFunc::showDeadMenu(SDL_Renderer* des, TTF_Font* font){
    int time =0;
    Mix_PauseMusic();
    SDL_Event event;
    Object background;

    bool ret = background.loadImg("img//menugamedead.png",des);
    if (ret == false){
        return 1 ;
    }
    while(1){
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)){
            switch (event.type){

            case SDL_QUIT:
                background.free();

                return 1;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    background.free();

                    return 1;

                }
                if (event.key.keysym.sym == SDLK_RETURN){
                    background.free();

                    return 2;

                }
                break;
            }
        }

        background.render(des,NULL);
        SDL_RenderPresent(des);
        if (1000 / 40 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 40 - (SDL_GetTicks() - time));



    }

    return 0;
}


void SDLCommonFunc::renderBlinkingText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, Uint32 blinkInterval) {
    Uint32 currentTicks = SDL_GetTicks();
    int a= (currentTicks / blinkInterval) % 3;
    //int alpha;

    int alpha = (currentTicks / blinkInterval) % 2 == 0 ? 200 : 50;

    SDL_Color color = { 255, 255, 255, alpha };
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect dstRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
}



