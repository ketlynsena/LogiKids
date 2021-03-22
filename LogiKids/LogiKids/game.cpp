#include "game.h"

N_Queens* nrainhas;
Map_Coloring* colorindo_bh;
Hanoi_Tower* bolo_hanoi;
Knapsack* mochila;
BalanceScale* balanca;
TravelingSalesman* mineiro_viajante;

SDL_Renderer* Game::renderer    = nullptr;
TTF_Font*     Game::consolas       = nullptr;
SDL_Cursor*   Game::cursor      = nullptr;
SDL_Cursor*   Game::cursor_hand = nullptr;

Game::Game()  {}
Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);// | SDL_WINDOW_BORDERLESS);

        if (window)
            std::cout << "Window created" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }

        isRunning = true;

        //Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
            isRunning = false;
        }
    }
    consolas = TTF_OpenFont("assets/fonts/consola.ttf", 30);
    if (consolas == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        isRunning = false;
    }
    
    
    //SDL_Color textColor = { 255, 255, 255 };
    //SDL_Texture* textTexture;
    //textTexture = TextureManager::loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor);
    

    SDL_Surface* cursorSurface = IMG_Load("assets/cursors/seta.png");
    SDL_Surface* handSurface   = IMG_Load("assets/cursors/mao.png");

    if (!cursorSurface || !handSurface) {
        isRunning = false;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    cursor_hand = SDL_CreateColorCursor(handSurface, 0, 0);

    if (!cursor || !cursor_hand) {
        isRunning = false;
    }

    SDL_SetCursor(cursor);

    SDL_Surface* icon = IMG_Load("assets/puzzle_icon.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    tela_principal  = new GameTexture("assets/tela_principal.png", 0, 0, false, false);
    modo_historia   = new GameTexture("assets/modo_historia.png", 0, 0, false, false);
    selecao_nivel   = new GameTexture("assets/selecao_nivel.png", 0, 0, false, false);
    botao_x         = new GameTexture("assets/buttons/x", 740, 20, true, false);
    botao_play      = new GameTexture("assets/buttons/play", 740, 550, true, false);

    level_marker[0] = new GameTexture("assets/buttons/level_marker_yellow", 249, 509, true, false);
    level_marker[1] = new GameTexture("assets/buttons/level_marker_pink", 373, 504, true, false);
    level_marker[2] = new GameTexture("assets/buttons/level_marker_blue", 368, 425, true, false);
    level_marker[3] = new GameTexture("assets/buttons/level_marker_yellow", 488, 447, true, false);
    level_marker[4] = new GameTexture("assets/buttons/level_marker_pink", 614, 472, true, false);
    level_marker[5] = new GameTexture("assets/buttons/level_marker_blue", 687, 401, true, false);

    nrainhas         = new N_Queens();
    colorindo_bh     = new Map_Coloring();
    bolo_hanoi       = new Hanoi_Tower();
    mochila          = new Knapsack();
    balanca          = new BalanceScale();
    mineiro_viajante = new TravelingSalesman();

    parabens        = new GameTexture("assets/parabens.png", 210, 150, false, false);
    botao_continuar = new GameTexture("assets/buttons/play", 380, 376, true, false);
    overlay         = new GameTexture("assets/overlay.png", 0, 0, false, false);

}

void Game::handleMenuEvents(SDL_Event* event) {
    if (event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN) {
        state = GAME_LEVELS;//STORY;
    }
}

void Game::handleStoryEvents(SDL_Event* event) {
    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
    if (botao_play->handleEvent(event)) {
        state = GAME_LEVELS;
    }
}

void Game::handleNQueensEvents(SDL_Event* event) {
    if (botao_x->handleEvent(event)) {
        nrainhas->resetLevel();
        state = GAME_LEVELS;
    }
    if (nrainhas->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            nrainhas->resetLevel();
            state = GAME_LEVELS;
        }
    }
    nrainhas->handleEvent(event);
}

void Game::handleLevelEvents(SDL_Event* event)
{
    if (level_marker[0]->handleEvent(event))
    {
        state = GAME_QUEENS;
    }

    if (level_marker[1]->handleEvent(event))
    {
        state = GAME_MAP_COLORING;
    }

    if (level_marker[2]->handleEvent(event))
    {
        state = GAME_HANOI;
    }

    if (level_marker[3]->handleEvent(event))
    {
        state = GAME_KNAPSACK;
    }

    if (level_marker[4]->handleEvent(event))
    {
        state = GAME_SCALE;
    }

    if (level_marker[5]->handleEvent(event))
    {
        state = GAME_TSP;
    }

    if (botao_x->handleEvent(event)) {
        state = GAME_MENU;
    }
}

void Game::handleMapColoringEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        colorindo_bh->resetMap();
        state = GAME_LEVELS;
    }

    if (colorindo_bh->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            colorindo_bh->resetMap();
            state = GAME_LEVELS;
        }
    }

    colorindo_bh->handleEvent(event);
}

void Game::handleHanoiEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        bolo_hanoi->resetLevel();
        state = GAME_LEVELS;
    }

    if (bolo_hanoi->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            bolo_hanoi->resetLevel();
            state = GAME_LEVELS;
        }
    }
    else {
        bolo_hanoi->handleEvent(event);
    }
}

void Game::handleKnapsackEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        mochila->resetLevel();
        state = GAME_LEVELS;
    }
    if (mochila->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            mochila->resetLevel();
            state = GAME_LEVELS;
        }
    }
    else {
        mochila->handleEvent(event);
    }
    
}

void Game::handleScaleEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        balanca->resetLevel();
        state = GAME_LEVELS;
    }

    if (balanca->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            balanca->resetLevel();
            state = GAME_LEVELS;
        }
    }
    else {
        balanca->handleEvent(event);
    }
}

void Game::handleTSPEvents(SDL_Event* event)
{
    if (botao_x->handleEvent(event)) {
        mineiro_viajante->resetLevel();
        state = GAME_LEVELS;
    }
    if (mineiro_viajante->gameWon())
    {
        if (botao_continuar->handleEvent(event)) {
            mineiro_viajante->resetLevel();
            state = GAME_LEVELS;
        }
    }
    else {
        mineiro_viajante->handleEvent(event);
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT) {
        isRunning = false;
    }
    else {
        switch (state) {
        case GAME_MENU:
            handleMenuEvents(&event);
            break;

        case GAME_STORY:
            handleStoryEvents(&event);
            break;

        case GAME_LEVELS:
            handleLevelEvents(&event);
            break;

        case GAME_QUEENS:
            handleNQueensEvents(&event);
            break;

        case GAME_MAP_COLORING:
            handleMapColoringEvents(&event);
            break;

        case GAME_HANOI:
            handleHanoiEvents(&event);
            break;

        case GAME_KNAPSACK:
            handleKnapsackEvents(&event);
            break;

        case GAME_SCALE:
            handleScaleEvents(&event);
            break;
        case GAME_TSP:
            handleTSPEvents(&event);

        default:
            break;
        }
    }
}

void Game::update()
{
    switch (state) {
    case GAME_QUEENS:
        nrainhas->update();
        break;
    case GAME_HANOI:
        bolo_hanoi->update();
        break;
    case GAME_KNAPSACK:
        mochila->update();
        break;
    case GAME_SCALE:
        balanca->update();
        break;
    case GAME_TSP:
        mineiro_viajante->update();
    default:
        break;
    }  
}

void Game::render()
{
    SDL_RenderClear(renderer);
    switch (state)
    {
    case GAME_MENU:
        tela_principal->render();
        break;

    case GAME_STORY:
        modo_historia->render();
        botao_play   ->render();
        botao_x      ->render();
        break;

    case GAME_LEVELS:
        selecao_nivel->render();
        botao_x      ->render();
        for (int i = 0; i < N_LEVELS; i++)
        {
            if(level_marker[i])
                level_marker[i]->render();
        }
        break;

    case GAME_QUEENS:
        nrainhas->render();        
        if (nrainhas->gameWon()) {
            overlay ->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_MAP_COLORING:
        colorindo_bh->render();
        if (colorindo_bh->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_HANOI:
        bolo_hanoi->render();
        if (bolo_hanoi->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_KNAPSACK:
        mochila->render();
        if (mochila->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    case GAME_SCALE:
        balanca->render();
        if (balanca->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;
    case GAME_TSP:
        mineiro_viajante->render();
        if (mineiro_viajante->gameWon()) {
            overlay->render();
            parabens->render();
            botao_continuar->render();
        }
        botao_x->render();
        break;

    default:
        break;
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    TTF_CloseFont(consolas);
    consolas = NULL;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeCursor(cursor);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
