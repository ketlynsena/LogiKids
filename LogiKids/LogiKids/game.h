#pragma once
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>

#include "game_texture.h"
#include "text_texture.h"
#include "timer.h"
#include "nqueens.h"
#include "map_coloring.h"
#include "hanoi_tower.h"
#include "knapsack.h"
#include "balance_scale.h"
#include "traveling_salesman.h"

#define N_LEVELS 6

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_STORY,
    GAME_LEVELS,
    GAME_QUEENS,
    GAME_MAP_COLORING,
    GAME_HANOI,
    GAME_KNAPSACK,
    GAME_TSP,
    GAME_SCALE,
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
    void handleEvents(MEvent event);
    void render();
    void update();
    void clean();
    bool running() { return isRunning; }
    void handleMenuEvents(MEvent* event);//SDL_Event* event);
    void handleStoryEvents(MEvent* event); //(SDL_Event* event);
    void handleNQueensEvents(MEvent* event);//(SDL_Event* event);
    void handleLevelEvents(MEvent* event); //(SDL_Event* event);
    void handleMapColoringEvents(MEvent* event);//(SDL_Event* event);
    void handleHanoiEvents(MEvent* event); //(SDL_Event* event);
    void handleKnapsackEvents(MEvent* event); //(SDL_Event* event);
    void handleScaleEvents(MEvent* event); //(SDL_Event* event);
    void handleTSPEvents(MEvent* event); //(SDL_Event* event);
    static void renderGameScore();
    MEvent pollEvent();

    static TextTexture* pontuacao;
    static TextTexture* tempo;
    static SDL_Renderer* renderer;
    static GameTexture* cerebro;
    static GameTexture* ampulheta;
   //static TTF_Font* gFont;
    static SDL_Cursor* cursor;
    static SDL_Cursor* cursor_hand;
    static TTF_Font* consolas;
    static Timer* timer;
    GameState state = GAME_MENU;

//private:
    bool isRunning;
    SDL_Window* window;
    GameTexture* tela_principal;
    GameTexture* modo_historia;
    GameTexture* selecao_nivel;
    GameTexture* parabens;
    GameTexture* overlay;
    SDL_Color branco = { 255, 255, 255 };
    //Buttons objects
    GameTexture* botao_x;
    GameTexture* botao_play;
    GameTexture* botao_continuar;
    GameTexture* level_marker[N_LEVELS];
    
    int pontos = 0;
    std::string timeText;
 
};

#endif // GAME_H_INCLUDED
