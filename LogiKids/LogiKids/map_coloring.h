#pragma once

#include "game_texture.h"
#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_REGIOES_BH 9
#define N_CORES 4

enum Nome {
    VENDA_NOVA,
    NORTE,
    PAMPULHA,
    NORDESTE,
    NOROESTE,
    LESTE,
    OESTE,
    CENTRO_SUL,
    BARREIRO
};

enum Cor {
    AZUL,
    ROXO,
    AMARELO, 
    ROSA,
    BRANCO
};

typedef struct Regiao {
    GameTexture* mapa;
    Nome nome;
    Cor nome_cor;
    SDL_Color cor;
};

class Map_Coloring
{
public:
	Map_Coloring();
    void addRegion(Nome name, int xpos, int ypos, const char* texturePath);
    void resetMap();
    void handleEvent(SDL_Event* e);
    void handleRegionEvent(SDL_Event* e, Regiao* regiao);
    void handleBucketEvent(SDL_Event* e, GameTexture* bucket, Cor color);
    void setToCurrentColor(Regiao* regiao);
    void setRegionColor(Regiao* regiao);
    SDL_Color getColorFromName(Cor color);
	~Map_Coloring();
    void render();

private:
	GameTexture* background;
    GameTexture* bh_outline;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* map;
    GameTexture* balde[N_CORES];
    //GameTexture* balde_virado[N_CORES];
    Regiao regioes[N_REGIOES_BH];
    Cor currentColor = BRANCO;
    Cor cores[5] = { AZUL, ROXO, AMARELO, ROSA, BRANCO };
    SDL_Color azul = { 0, 158, 161 };
    SDL_Color roxo = { 96, 62, 149 };
    SDL_Color amarelo = { 250, 195, 43 };
    SDL_Color rosa = { 215, 38, 93 };
    SDL_Color branco = { 204, 204, 204 };
    bool gameWin = false;

};

