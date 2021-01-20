#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_STORY,
    GAME_LEVELS,
    GAME_WIN,
    GAME_LOSE,
    GAME_PAUSE,
    GAME_ATTRIBUTES
};

class Game {

public:
    Game();
    ~Game();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void render();
    void update();
    void clean();
    bool running(){return isRunning;}

    static SDL_Renderer* renderer;
    GameState state = GAME_LEVELS;

private:
    bool isRunning;
    SDL_Window* window;

};

#endif // GAME_H_INCLUDED
