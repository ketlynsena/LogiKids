#include "map_coloring.h"

Map_Coloring::Map_Coloring()
{
	background = new GameTexture("assets/map_coloring/colorindo_bh.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 550, true, false);
	bh = new GameTexture("assets/map_coloring/bh.png", 420, 124, false, false);

    addRegion(VENDA_NOVA, 501, 128, "assets/map_coloring/venda_nova.png");
    addRegion(NORTE,      572, 154, "assets/map_coloring/norte.png");
    addRegion(PAMPULHA,   484, 201, "assets/map_coloring/pampulha.png");
    addRegion(NORDESTE,   584, 190, "assets/map_coloring/nordeste.png");
    addRegion(NOROESTE,   475, 283, "assets/map_coloring/noroeste.png");
    addRegion(LESTE,      602, 281, "assets/map_coloring/leste.png");
    addRegion(OESTE,      497, 339, "assets/map_coloring/oeste.png");
    addRegion(CENTRO_SUL, 568, 333, "assets/map_coloring/centro_sul.png");
    addRegion(BARREIRO,   429, 396, "assets/map_coloring/barreiro.png");

    regioes[VENDA_NOVA].mapa->setColor(azul);
    regioes[NORTE].mapa->setColor(roxo);
    regioes[PAMPULHA].mapa->setColor(amarelo);
    regioes[NORDESTE].mapa->setColor(rosa);
    regioes[NORTE].mapa->resetColor();
}

void Map_Coloring::addRegion(Nome name, int xpos, int ypos, const char* texturePath)
{
    regioes[name].cor = BRANCO;
    regioes[name].nome = name;
    regioes[name].mapa = new GameTexture(texturePath, xpos, ypos, false, false); 
}

Map_Coloring::~Map_Coloring()
{
}

void Map_Coloring::render()
{
    background->render();
    bh->render();
    help->render();
    reset->render();

    for (int i = 0; i < N_REGIOES_BH; i++)
        regioes[i].mapa->render();
}
