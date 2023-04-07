#ifndef MAP_H
#define MAP_H

#include "CommonFunc.h"
#include "Object.h"

#define MAX_TILE 20

class TileMap : public Object
{
    public:
        TileMap(){;};
        ~TileMap(){;};
};
class GameMap {
    public:
        GameMap(){;};
        ~GameMap(){;};
        void loadMap(char* name);
        void loadTiles(SDL_Renderer* screen);
        void drawMap(SDL_Renderer* screen, float player_x_pos);
        void drawMap(SDL_Renderer* screen);
        Map getMap(){return game_map;};
        void setMap(Map& map_data){game_map = map_data;};
    private:
        Map game_map;
        TileMap tile_map[MAX_TILE];

};

#endif // MAP_H
