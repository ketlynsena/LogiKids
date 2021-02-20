#include "map_coloring.h"

Map_Coloring::Map_Coloring()
{
	background = new GameTexture("assets/map_coloring/colorindo_bh.png", 0, 0, false, false);
	help = new GameTexture("assets/buttons/help", 740, 540, true, false);
	reset = new GameTexture("assets/buttons/reset", 15, 550, true, false);
    bh_outline = new GameTexture("assets/map_coloring/bh_outline.png", 419, 122, false, false);

    balde[AZUL]           = new GameTexture("assets/map_coloring/balde_azul", 30, 425, true, false);
    //balde_virado[AZUL]    = new GameTexture("assets/map_coloring/balde_azul_2", 30, 425, false, false);

    balde[ROXO]           = new GameTexture("assets/map_coloring/balde_roxo", 122, 425, true, false);
    //balde_virado[ROXO]    = new GameTexture("assets/map_coloring/balde_roxo_2", 122, 425, false, false);

    balde[AMARELO]        = new GameTexture("assets/map_coloring/balde_amarelo", 214, 425, true, false);
    //balde_virado[AMARELO] = new GameTexture("assets/map_coloring/balde_amarelo_2", 214, 425, false, false);

    balde[ROSA]           = new GameTexture("assets/map_coloring/balde_rosa", 306, 425, true, false);
    //balde_virado[ROSA]    = new GameTexture("assets/map_coloring/balde_rosa_2", 306, 425, false, false);

    addRegion(VENDA_NOVA, 496, 124, "assets/map_coloring/venda_nova.png");
    addRegion(NORTE,      567, 124, "assets/map_coloring/norte.png");
    addRegion(PAMPULHA,   479, 197, "assets/map_coloring/pampulha.png");
    addRegion(NORDESTE,   579, 179, "assets/map_coloring/nordeste.png");
    addRegion(NOROESTE,   470, 277, "assets/map_coloring/noroeste.png");
    addRegion(LESTE,      597, 274, "assets/map_coloring/leste.png");
    addRegion(OESTE,      477, 335, "assets/map_coloring/oeste.png");
    addRegion(CENTRO_SUL, 559, 328, "assets/map_coloring/centro_sul.png");
    addRegion(BARREIRO,   420, 392, "assets/map_coloring/barreiro.png");

}

Map_Coloring::~Map_Coloring()
{
}

void Map_Coloring::addRegion(Nome name, int xpos, int ypos, const char* texturePath)
{
    regioes[name].nome_cor = BRANCO;
    regioes[name].cor = { 204, 204, 204};//255, 255, 255 };
    regioes[name].nome = name;
    regioes[name].mapa = new GameTexture(texturePath, xpos, ypos, false, false);
}

void Map_Coloring::resetMap()
{
    for (int i = 0; i < N_REGIOES_BH; i++)
    {
        regioes[i].mapa->setColor(branco);
        regioes[i].cor = { 204, 204, 204};//255, 255, 255 };
        regioes[i].nome_cor = BRANCO;
    } 

    gameWin = false;
}

bool Map_Coloring::checkWin()
{
    int coloredRegions = 0;
    for (int i = 0; i < N_REGIOES_BH; i++)
    {
        if (regioes[i].nome_cor != BRANCO)
        {
            coloredRegions++;
        }
        else // If any region is not colored, then the game is not complete yet 
        {
            return false;
        }
    }
    // If all regions are colored and they don't repeat at borders
    if (coloredRegions == N_REGIOES_BH && isSafe())
        return true;
    else
        return false;
}

// Check if coloring is safe (no repeting colors between two edges)
bool Map_Coloring::isSafe()
{
    for (int v = 0; v < N_REGIOES_BH; v++) // For each vertex
    {
        // For each adjacent node
        for (int n = v+1; n < N_REGIOES_BH; n++)
        {
            if (v != n) // if is not node
            {
                if (mapa_bh[v][n] == true && regioes[v].nome_cor != BRANCO && regioes[n].nome_cor != BRANCO) // 
                {
                    //printf("v:%d n:%d cor_v:%d cor_n:%d\n", v, n, regioes[v].nome_cor, regioes[n].nome_cor);
                    if (regioes[v].nome_cor == regioes[n].nome_cor) {
                        return false;
                   }
                }
            }

        }
    }
    return true;
}

void Map_Coloring::handleEvent(SDL_Event* e)
{
    if (!checkWin()) {
        help->handleEvent(e);

        for (int i = 0; i < N_REGIOES_BH; i++)
            handleRegionEvent(e, &regioes[i]);
        
        for (int i = 0; i < N_CORES; i++)
            handleBucketEvent(e, balde[i], cores[i]);

        if (reset->handleEvent(e))
            resetMap();
    }
    else {
        gameWin = true;
    }
}

bool Map_Coloring::gameWon()
{
    return gameWin;
}

void Map_Coloring::handleBucketEvent(SDL_Event* e, GameTexture* bucket, Cor color)
{
    bucket->handleEvent(e);
    if (bucket->isPressed()) {
        printf("Click no balde\n");
        currentColor = color;
        printf("Current color: %d\n", currentColor);
    }
}

void Map_Coloring::handleRegionEvent(SDL_Event* e, Regiao* regiao)
{
    regiao->mapa->handleEvent(e);

    // If region is pressed, sets the color
    if (regiao->mapa->isPressed()) {
        printf("Click na regiao\n");
        setRegionColor(regiao);
        //if (isSafe())
        //    printf("Move was safe.\n");
        //else
        //    printf("Move was not safe.\n");
    }
    // Highlights current color on the region
    // the mouse hovers
    if (regiao->mapa->isWithinBoundaries())
    {
        SDL_Color currentColorRGB = getColorFromName(currentColor);
        regiao->mapa->setColor(currentColorRGB);
    }        
    else
        setToCurrentColor(regiao); 
}

void Map_Coloring::setToCurrentColor(Regiao* regiao)
{
    regiao->mapa->setColor(regiao->cor);
}

SDL_Color Map_Coloring::getColorFromName(Cor color)
{
    SDL_Color color_rgb = { 0,0,0 };

    switch (color)
    {
    case AZUL:
        color_rgb.r = azul.r;
        color_rgb.g = azul.g;
        color_rgb.b = azul.b;
        break;
    case ROXO:
        color_rgb.r = roxo.r;
        color_rgb.g = roxo.g;
        color_rgb.b = roxo.b;
        break;
    case AMARELO:
        color_rgb.r = amarelo.r;
        color_rgb.g = amarelo.g;
        color_rgb.b = amarelo.b;
        break;
    case ROSA:
        color_rgb.r = rosa.r;
        color_rgb.g = rosa.g;
        color_rgb.b = rosa.b;
        break;
    case BRANCO:
        color_rgb.r = branco.r;
        color_rgb.g = branco.g;
        color_rgb.b = branco.b;
        break;
    default:
        break;
    }
    return color_rgb;
}

void Map_Coloring::setRegionColor(Regiao* regiao)
{
    SDL_Color color = getColorFromName(currentColor);
    regiao->cor.r = color.r;
    regiao->cor.g = color.g;
    regiao->cor.b = color.b;
    regiao->mapa->setColor(regiao->cor);
    regiao->nome_cor = currentColor;
}

void Map_Coloring::render()
{
    background->render();
    help->render();
    reset->render();

    for (int i = 0; i < N_REGIOES_BH; i++)
        regioes[i].mapa->render();

    bh_outline->render();

    for (int i = 0; i < N_CORES; i++)
        balde[i]->render();
}
