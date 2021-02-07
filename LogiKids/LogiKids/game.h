#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_STORY,
    GAME_LEVELS,
    GAME_QUEENS,
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
    bool running() { return isRunning; }
    void handleMenuEvents(SDL_Event* event);
    void handleStoryEvents(SDL_Event* event);
    void handleNQueensEvents(SDL_Event* event);

    static SDL_Renderer* renderer;
    GameState state = GAME_MENU;

private:
    bool isRunning;
    SDL_Window* window;

};

#endif // GAME_H_INCLUDED
