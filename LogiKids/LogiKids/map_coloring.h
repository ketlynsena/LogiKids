#pragma once

#include "game_texture.h"
#include "game.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

#define N_REGIOES_BH 9

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
    Cor cor = BRANCO;
};

class Map_Coloring
{
public:
	Map_Coloring();
    void addRegion(Nome name, int xpos, int ypos, const char* texturePath);
	~Map_Coloring();
    void render();

private:
	GameTexture* background;
    GameTexture* bh;
	GameTexture* help;
	GameTexture* reset;
	GameTexture* map;
    Regiao regioes[N_REGIOES_BH];
    SDL_Color azul = { 0, 158, 161 };
    SDL_Color roxo = { 96, 62, 149 };
    SDL_Color amarelo = { 250, 195, 43 };
    SDL_Color rosa = { 215, 38, 93 };
    SDL_Color branco = { 255, 255, 255 };

};

