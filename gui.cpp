#include <gui.hpp>

Window::Window(int w, int h, int tile_size, int velocity) : w(w), h(h), tile_size(tile_size), velocity(velocity) {
    if(SDL_Init(SDL_INIT_VIDEO) >= 0) {
        window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (window != NULL) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer != NULL) {
                textures["BRICK"] = IMG_LoadTexture(renderer, "brik.png");
                textures["BACKGROUND"] = IMG_LoadTexture(renderer, "bg.png");
                textures["SNAKE"] = IMG_LoadTexture(renderer, "snak.png");
                textures["DEATH_SCREEN"] = IMG_LoadTexture(renderer, "u_ded.png");
                is_fullscreen = true;
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                timer = clock();
            }
        }
    }
}

Window::~Window() {
    SDL_Quit();
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}

void Window::render(Map& map, Snake& snake) {
    SDL_Rect rectangle = {0, 0, 1000, 1000};
    SDL_RenderCopy(renderer, textures["BACKGROUND"], NULL, &rectangle);
    SDL_Rect texture_rect;

    double angle;
    for (int i = 0; i < snake.getSize(); i++) {
        switch (snake.getDirection(i)) {
        case UP:
            angle = 270;
            break;
        case DOWN:
            angle = 90;
            break;
        case LEFT:
            angle = 180;
            break;
        case RIGHT:
            angle = 0;
            break;
        default:
            break;
        }
        rectangle = {tile_size * snake.getXFromIndex(i), tile_size * snake.getYFromIndex(i), tile_size, tile_size};


        if (i == snake.getSize() - 1) {
            texture_rect = {200 - (clock() - timer)/4, 0, 50, 50};
        } else if (i == snake.getSize() - 2) {
            texture_rect = {150 - (clock() - timer)/4, 0, 50, 50};
        } else if (i == 1) {
            texture_rect = {100 - (clock() - timer)/4, 0, 50, 50};
        } else if (i == 0) {
            texture_rect = {50 - (clock() - timer)/4, 0, 50, 50};
        } else {
            if (snake.getXFromIndex(i - 1) == snake.getXFromIndex(i + 1) || snake.getYFromIndex(i - 1) == snake.getYFromIndex(i + 1)) {
                texture_rect = {100, 0, 50, 50};
            } else {
                texture_rect = {250, 0, 50, 50};
                if ((snake.getDirection(i - 1) == RIGHT && snake.getDirection(i + 1) == DOWN) || (snake.getDirection(i - 1) == UP && snake.getDirection(i + 1) == LEFT)) {
                    angle = 0;
                } else if ((snake.getDirection(i - 1) == RIGHT && snake.getDirection(i + 1) == UP) || (snake.getDirection(i - 1) == DOWN && snake.getDirection(i + 1) == LEFT)) {
                    angle = 90;
                } else if ((snake.getDirection(i - 1) == DOWN && snake.getDirection(i + 1) == RIGHT) || (snake.getDirection(i - 1) == LEFT && snake.getDirection(i + 1) == UP)) {
                    angle = 180;
                } else {
                    angle = 270;
                }
            }
        }
        
        SDL_RenderCopyEx(renderer, textures["SNAKE"], &texture_rect, &rectangle, angle, NULL, SDL_FLIP_NONE);
        if (clock() - timer >= 200) {
            timer = clock();
        }
    }

    for (int i = 0; i < map.getHeight(); i++) {
        for (int j = 0; j < map.getWidth(); j++) {
            rectangle = {i * tile_size, j * tile_size, tile_size, tile_size};
            if (map.getTile(i, j) == APPLE) {
                texture_rect = {300, 0, 50, 50};
                SDL_RenderCopy(renderer, textures["SNAKE"], &texture_rect, &rectangle);
            } else if (map.getTile(i, j) == WALL) {
                texture_rect = {350, 0, 50, 50};
                SDL_RenderCopy(renderer, textures["SNAKE"], &texture_rect, &rectangle);
            }
        }
    }


    SDL_RenderPresent(renderer);
}

void Window::listen(Direction& direction) {
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            Window::~Window();
        } else if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                w = event.window.data1;
                h = event.window.data2;
                SDL_RenderPresent(renderer);
            }
        } else {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                direction = UP;
                break;
            case SDLK_DOWN:
                direction = DOWN;
                break;
            case SDLK_RIGHT:
                direction = RIGHT;
                break;
            case SDLK_LEFT:
                direction = LEFT;
                break;
            case SDLK_F11:
                if (is_fullscreen == false) {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    is_fullscreen = true;
                } else {
                    SDL_SetWindowFullscreen(window, SDL_FALSE);
                    is_fullscreen = false;
                }
            default:
                break;
            }
        }
    }
}

void Window::deathScreen() {
    SDL_RenderCopy(renderer, textures["DEATH_SCREEN"], NULL, NULL);
    SDL_RenderPresent(renderer);
}