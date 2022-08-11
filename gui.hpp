#ifndef _GUI_H_
#define _GUI_H_


#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <string>
#include <map>

#include "game.hpp"


class Window {
    public:

    Window(int w, int h, int tile_size, int velocity);
    ~Window();
    void render(Map& map, Snake& snake);
    void listen(Direction& direction);
    void deathScreen();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    map<string, SDL_Texture*> textures;

    int w;
    int h;
    int tile_size;
    bool is_fullscreen;
    clock_t timer;
    int velocity;
    
};


#endif
