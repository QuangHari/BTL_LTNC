#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "TextObj.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen =NULL;
static SDL_Renderer* g_img_menu =NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 40;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP =32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

static Mix_Music* music;
static Mix_Chunk* explosion_sound;
static Mix_Chunk* shot_sound;
static Mix_Chunk* empty_sound;
static Mix_Chunk* reload_sound;
static Mix_Chunk* fall_sound;



#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct Input {
    int left;
    int right;
    int up;
    int down;
    int jump;
};

typedef struct Map{
    int start_x;
    int start_y;

    int max_x;
    int max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};
namespace SDLCommonFunc{
    bool CheckCollision (const SDL_Rect& obj1,const SDL_Rect& obj2);
    bool CheckCollision1 (const SDL_Rect& obj1,const SDL_Rect& obj2);
    int ShowMenu(SDL_Renderer* des, TTF_Font* font);
    void renderBlinkingText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, Uint32 blinkInterval);
    int showDeadMenu(SDL_Renderer* des, TTF_Font* font);
}



#endif // COMMONFUNC_H
